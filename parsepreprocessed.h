#pragma once

#include <QByteArray>
#include <QRegularExpression>
#include <QTextStream>

struct SourceFile
{
    SourceFile() : startLine(0), endLine(0), netLines(0), indirectLines(0) { }
    QString fileName;
    int startLine;  // start of this file in the preprocessed source
    int endLine;
    int netLines;   // all source lines this file directly contributes
    int indirectLines; // LOC caused by includes from this file
    QVector<SourceFile> includes;
};


enum class LineType
{
    Text,
    Goto,
    Return,
    OtherMarker
};

struct LineFragments
{
    LineFragments() : lineType(LineType::Text) {}
    QString header;
    int line;
    LineType lineType;
};

struct SourceFileContribution
{
    SourceFileContribution() : direct(0), indirect(0) {}

    QString fileName;
    int direct;
    int indirect;
};


class ParsePreprocessed
{
public:
    ParsePreprocessed(const QByteArray &input);
    SourceFile sourceFile();

private:

    LineFragments splitLine(const QString &line);
    SourceFile makeSourceFile(const QStringList &lines);

    QByteArray m_input;
    QRegularExpression m_regex;
};

struct HeaderContribution
{
    QString headerName;
    int contributionTotal() const;

    QVector<SourceFileContribution> sourceContributions;
};


struct AllContribution
{
    void add(const QString fileName, const QString headerName, int direct, int indirect);
    void sort();
    QVector<HeaderContribution> contributors;
};


void printRecursive(const SourceFile &sourceFile, int depth, QTextStream  &stream);
AllContribution mostUsed(const QVector<SourceFile> &sourceFiles);
void printMostUsed(const AllContribution &allContribution);
void printTotal(const QVector<SourceFile> &sourceFiles);

template <typename T>
void recursiveRun( const SourceFile &sourceFile, int depth,  T callback, int maxDepth=0)
{
    depth++;
    if( (maxDepth >0) && (depth > maxDepth) ){
        return;
    }
    callback(sourceFile, depth);
    for(const auto &include: sourceFile.includes){
        recursiveRun(include, depth, callback, maxDepth);
    }
}

