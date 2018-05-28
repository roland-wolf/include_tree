#include <QDebug>
#include <QStringList>
#include <QVector>

#include "parsepreprocessed.h"

/*
input line example:
# 16 "/usr/include/boost/property_tree/detail/rapidxml.hpp" 2 3 4
*/

const QString regexString = R"__(^# \d+ "([^"]+)" ?(\d?))__";

ParsePreprocessed::ParsePreprocessed(const QByteArray &input)
    : m_input(input)
    , m_regex(regexString)
{
    m_regex.optimize();
}

SourceFile ParsePreprocessed::sourceFile()
{
    QString preprocessed = QString::fromUtf8(m_input);
    QStringList lines = preprocessed.split(("\n"));
    //qWarning() << "lines: " << lines.size();
    SourceFile sourceFile = makeSourceFile(lines);
    return sourceFile;
}


LineFragments ParsePreprocessed::splitLine(const QString &line)
{
    LineFragments lineFragments;

    QRegularExpressionMatch match = m_regex.match(line);

    if (match.hasMatch()) {

        lineFragments.header = match.captured(1);
        QString foldingIndicator = match.captured(2);
        bool isOk = true;
        const int foldingInt = foldingIndicator.toInt(&isOk);
        if(isOk){
            if(foldingInt == 1){
                lineFragments.lineType = LineType::Goto;
            }else if(foldingInt == 2){
                lineFragments.lineType = LineType::Return;
            }else{
                lineFragments.lineType = LineType::OtherMarker;
            }
        }
    }
    return lineFragments;
}

SourceFile ParsePreprocessed::makeSourceFile(const QStringList &lines)
{
    int lineCount = 0;
    SourceFile sourceFile;
    QVector<SourceFile *> trace;
    trace.push_back(&sourceFile);


    //SourceFile cursor = &sourceFile;
    for(auto const &line : lines ){
        SourceFile &currentSourceFile = *(trace.last());
        LineFragments lineFragments = splitLine(line);
        if(lineFragments.lineType == LineType::Text){
            lineCount++;
            currentSourceFile.netLines++;

            for(int i= 0; i< trace.size() -1; i++ ){
                trace[i]->indirectLines++;
            }
            continue;
        }else if(lineFragments.lineType == LineType::Goto){
            currentSourceFile.includes.push_back(SourceFile{});
            trace.push_back( &(currentSourceFile.includes.last()));
            SourceFile &newSourceFile = *(trace.last());
            newSourceFile.startLine = lineCount;
            newSourceFile.fileName = lineFragments.header;
        }else if(lineFragments.lineType == LineType::Return) {
            currentSourceFile.endLine = lineCount - 1;
            trace.pop_back();
        }else if(lineFragments.lineType == LineType::OtherMarker){
            ; // do nothing
        }
    }
    return sourceFile;
}

/*
void printRecursive(const SourceFile &sourceFile, int depth)
{
    auto callback = [](const SourceFile &sourceFile, int depth ){
        qWarning() << QString("%1").arg(sourceFile.indirectLines, 6)  << QString("%1").arg(sourceFile.netLines, 6) << " " << QString(depth * 4, QChar(' ')) + sourceFile.fileName;
    };
    recursiveRun(sourceFile, 0, callback);
}
*/


void printRecursive(const SourceFile &sourceFile, int depth, QTextStream  &stream)
{
    auto callback = [&stream](const SourceFile &sourceFile, int depth){
        stream << QString("%1").arg(sourceFile.indirectLines, 6)  << QString("%1").arg(sourceFile.netLines, 6) << " " << QString(depth * 4, QChar(' ')) + sourceFile.fileName +"\n";
    };
    recursiveRun(sourceFile, 0, callback);
}



int HeaderContribution::contributionTotal() const
{
    int result=0;
    for(const auto &sourceContribution : sourceContributions){
        result += sourceContribution.direct + sourceContribution.indirect;
    }
    return result;
}




void AllContribution::add(const QString fileName, const QString headerName, int direct, int indirect)
{
    bool found = false;
    for(auto &contributor: contributors){
        if(contributor.headerName == headerName){
            SourceFileContribution sourceFileContribution;
            sourceFileContribution.fileName = fileName;
            sourceFileContribution.direct = direct;
            sourceFileContribution.indirect = indirect;
            contributor.sourceContributions.push_back(sourceFileContribution);
            found = true;
            break;
        }
    }
    if(found == false){
        HeaderContribution headerContribution;
        headerContribution.headerName = headerName;
        SourceFileContribution sourceFileContribution;
        sourceFileContribution.fileName = fileName;
        sourceFileContribution.direct = direct;
        sourceFileContribution.indirect = indirect;
        headerContribution.sourceContributions.push_back(sourceFileContribution);
        contributors.push_back(headerContribution);
    }
}

void AllContribution::sort()
{
    std::sort(contributors.begin(), contributors.end(),
              [](const HeaderContribution &a, HeaderContribution &b){
        return a.contributionTotal() > b.contributionTotal();
    }
    );
}


AllContribution mostUsed(const QVector<SourceFile> &sourceFiles)
{
    AllContribution allContribution;

    //recursive descent through all SourceFile trees, add data to allContribution
    for(const auto &sourceFile : sourceFiles){
        const QString preprocessedName = sourceFile.fileName;
        auto callback = [&allContribution, &preprocessedName](const SourceFile &sourceFile, int depth){
            allContribution.add(preprocessedName, sourceFile.fileName, sourceFile.netLines, sourceFile.indirectLines);
        } ;
        recursiveRun(sourceFile, 0, callback);
    }
    allContribution.sort();
    return allContribution;
}

void printMostUsed(const AllContribution &allContribution)
{
    for(const auto &contributor: allContribution.contributors){
        qWarning() << QString("%1").arg(contributor.contributionTotal() , 6) << contributor.headerName;
    }
}


void printTotal(const QVector<SourceFile> &sourceFiles)
{
    int total = 0;
    for(const auto &sourceFile : sourceFiles){
        total += sourceFile.netLines + sourceFile.indirectLines;
    }
     qWarning() << "total lines: " << total;
}


