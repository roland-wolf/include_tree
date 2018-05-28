#pragma once

#include "iactions.h"
#include "iselectcu.h"
#include "collect.h"
#include "parsepreprocessed.h"


class TreeModel;
class ModelCu;

class Actions : public IActions, public ISelectCu, public ISelectHeader
{
public:
    Actions(TreeModel *treeModel, ModelCu *modelCu, ModelCu *modelHu, ISetText *setText);

    void loadSingleFile(const QString &file) override;
    virtual void loadAllFiles(const QString &directory) override;
    void selectCu(const QString &cu) override;
    void selectHeader(const QString &cu) override;

private:
    TreeModel *m_treeModel;
    ModelCu *m_modelCu;
    ModelCu *m_modelHeaders;
    ISetText *m_setText;

    QVector<SourceFile> m_allFiles;
    AllContribution m_allContribution;
};

