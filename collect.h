#pragma once

#include <QVector>

class SourceFile;

void collect();

SourceFile collectFile(const QString &fileName);
QVector<SourceFile> collectDir(const QString &directory);

