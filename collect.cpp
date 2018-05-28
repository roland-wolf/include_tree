#include <QDebug>
#include <QDirIterator>
#include <QFile>

#include "parsepreprocessed.h"
#include "collect.h"



SourceFile collectFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    ParsePreprocessed parsePreprocessed(bytes);
    SourceFile sourceFile = parsePreprocessed.sourceFile();
    sourceFile.fileName = fileName;
    return sourceFile;
}




QVector<SourceFile> collectDir(const QString &directory)
{
    QStringList fileNames;

    constexpr bool doCount = false;
    constexpr int maxCount = 10;
    int count = 0;


    QDirIterator it(directory, QStringList() << "*.ii" << "*.i");
    while (it.hasNext()) {
        count++;
        if(doCount){
            if(count > maxCount) {
                break;
            }
        }
        fileNames << it.next();
    }


    QVector<SourceFile> sourceFiles;

    count = 0;
    for (const auto &fileName : fileNames) {
        count++;
        qWarning() << count << " of " << fileNames.size();
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QByteArray bytes = file.readAll();
        ParsePreprocessed parsePreprocessed(bytes);
        SourceFile sourceFile = parsePreprocessed.sourceFile();
        sourceFile.fileName = fileName;
        sourceFiles << sourceFile;


    }
    printTotal(sourceFiles);

    return sourceFiles;
    /*
    */
}

