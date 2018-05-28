#pragma once

#include <QString>

struct CompilationUnit
{
QString fileName;
int direct;
int indiret;
};


struct CompilationUnits {
    std::vector<CompilationUnit> compilationUnits;
};
