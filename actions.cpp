#include <QTextStream>
#include <QDebug>

#include "actions.h"
#include "treemodel.h"
#include "filltreemodel.h"
#include "parsepreprocessed.h"
#include "modelcu.h"

Actions::Actions(TreeModel *treeModel,  ModelCu *modelCu, ModelCu *modelHu, ISetText *setText)
    : m_treeModel(treeModel)
    , m_modelCu(modelCu)
    , m_modelHeaders(modelHu)
    , m_setText(setText)
{
}


void Actions::loadSingleFile(const QString &file)
{
    SourceFile sourceFile = collectFile(file);
    TreeItem *treeItem = fillTreeModel(sourceFile);
    m_treeModel->setTree(treeItem);
    QString collect;
    QTextStream stream(&collect);
    printRecursive(sourceFile, 0, stream);
}


QVector<Line> compilationUnits( QVector<SourceFile> &allFiles )
{
    QVector<Line> lines;
    for(auto const &file : allFiles){
        Line line;
        line.text = file.fileName;
        line.size = file.netLines + file.indirectLines;
        lines.append(line);
    }
    std::sort(lines.begin(), lines.end(), [](const Line &left, const Line &right){return left.size > right.size;} );
    return lines;
}



void Actions::loadAllFiles(const QString &directory)
{
    m_allFiles = collectDir(directory);

    //Compilation Units
    QVector<Line> linesCu = compilationUnits(m_allFiles);
    m_modelCu->setLines(linesCu);

    //Headers

    m_allContribution = mostUsed(m_allFiles);
    //printMostUsed(allContribution);
    QVector<Line> linesHeaders;
    for(const auto &contribution : m_allContribution.contributors){
        Line line;
        line.text = contribution.headerName;
        line.size = contribution.contributionTotal();
        linesHeaders << line;
    }

    //QVector<Line> linesHeaders = headers(m_allFiles);
    m_modelHeaders->setLines(linesHeaders);

    //printTotal(m_allFiles);
}



void Actions::selectCu(const QString &cu)
{
       auto iter = std::find_if(m_allFiles.begin(), m_allFiles.end(),
                                [cu](const SourceFile &sourceFile){return sourceFile.fileName == cu;}
       );
       if(iter == m_allFiles.end()){
           return;
       }
       const auto &src = *iter;
       TreeItem *treeItem = fillTreeModel(src);
       m_treeModel->setTree(treeItem);

       QString collect;
       QTextStream stream(&collect);
       printRecursive(src, 0, stream);
       m_setText->setText(collect);
}

void Actions::selectHeader(const QString &cu)
{
    qWarning() << "clicked on: " << cu;
}


