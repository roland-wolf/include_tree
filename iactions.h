#pragma once

class QString;

class IActions
{
public:
    virtual void loadSingleFile(const QString &file)=0;
    virtual void loadAllFiles(const QString &directory)=0;
};


