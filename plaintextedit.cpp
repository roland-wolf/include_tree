#include "plaintextedit.h"

PlainTextEdit::PlainTextEdit()
{
    QFont font;
    font.setFamily(QStringLiteral("DejaVu Sans Mono"));
    setFont(font);
    setLineWrapMode(LineWrapMode::NoWrap);
}

void PlainTextEdit::setText(const QString &text)
{
    setPlainText(text);
}
