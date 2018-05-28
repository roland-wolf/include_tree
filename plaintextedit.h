#pragma once

#include <QPlainTextEdit>

#include "iselectcu.h"

class PlainTextEdit : public QPlainTextEdit , public ISetText
{
public:
    PlainTextEdit();
    void setText(const QString &text) override;
};

