#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QVector>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QString>
#include <QTextDocument>
#include <QBrush>
#include <QColor>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0,int flag = 0);

    //~Highlighter();



protected:
    void highlightBlock(const QString &text) override;

private:

    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat keywordFormat_2;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    int flag_c;

};

#endif // HIGHLIGHTER_H
