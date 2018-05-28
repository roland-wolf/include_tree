#pragma once

#include <QString>

class ISelectCu
{
public:
    virtual void selectCu(const QString &cu)=0;
};


class ISelectHeader
{
public:
    virtual void selectHeader(const QString &cu)=0;
};


class ISetText
{
public:
    virtual void setText(const QString &text)=0;
};
