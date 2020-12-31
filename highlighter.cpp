#include <highlighter.h>

Highlighter::Highlighter(QTextDocument *parent, int flag)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    flag_c = flag;
    keywordFormat.setForeground(QBrush(QColor(0,0,128)));
    keywordFormat.setFontWeight(QFont::Bold);
    if(flag_c == 0 || flag_c == 2){
    const QString keywordPatterns[] = {
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bdo\\b"), QStringLiteral("\\bor\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsignals\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bslots\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\bbool\\b"),
        QStringLiteral("\\band\\b"), QStringLiteral("\\bfloat\\b"), QStringLiteral("\\bxor_eq\\b"),
        QStringLiteral("\\band_eq\\b"), QStringLiteral("\\basm\\b"), QStringLiteral("\\bxor\\b"),
        QStringLiteral("\\bor_eq\\b"),QStringLiteral("\\binclude\\b"),
        QStringLiteral("\\bauto\\b"), QStringLiteral("\\bbreak\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    }

    else if(flag_c == 1){
    const QString keywordPatterns[] = {
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bdo\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\benum\\b"),
        QStringLiteral("\\bint\\b"),  QStringLiteral("\\binclude\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bxor_eq\\b"),
        QStringLiteral("\\bshort\\b"),  QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btypedef\\b"), QStringLiteral("\\bbool\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"),
        QStringLiteral("\\band\\b"), QStringLiteral("\\bfloat\\b"),
        QStringLiteral("\\bauto\\b"), QStringLiteral("\\bbreak\\b"),
        QStringLiteral("\\bgoto\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    }

    else if(flag_c == 3){
    const QString keywordPatterns[] = {
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bdo\\b"), QStringLiteral("\\bor\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsignals\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bslots\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\bbool\\b"),
        QStringLiteral("\\band\\b"), QStringLiteral("\\bfloat\\b"), QStringLiteral("\\bxor_eq\\b"),
        QStringLiteral("\\band_eq\\b"), QStringLiteral("\\basm\\b"), QStringLiteral("\\bxor\\b"),
        QStringLiteral("\\bor_eq\\b"),QStringLiteral("\\binclude\\b"),
        QStringLiteral("\\balignas\\b"), QStringLiteral("\\bchar16_t\\b"), QStringLiteral("\\bdecltype\\b"),
        QStringLiteral("\\balignof\\b"), QStringLiteral("\\bnoexcept\\b"), QStringLiteral("\\bnull_ptr\\b"),
        QStringLiteral("\\band\\b"), QStringLiteral("\\bstatic_assert\\b"), QStringLiteral("\\bthread_local\\b"),
        QStringLiteral("\\bauto\\b"), QStringLiteral("\\bbreak\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    }

    else if(flag_c == 4){
    const QString keywordPatterns[] = {
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bdo\\b"), QStringLiteral("\\bor\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsignals\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bslots\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\bbool\\b"),
        QStringLiteral("\\band\\b"), QStringLiteral("\\bfloat\\b"), QStringLiteral("\\bxor_eq\\b"),
        QStringLiteral("\\band_eq\\b"), QStringLiteral("\\basm\\b"), QStringLiteral("\\bxor\\b"),
        QStringLiteral("\\bor_eq\\b"),QStringLiteral("\\binclude\\b"),
        QStringLiteral("\\balignas\\b"), QStringLiteral("\\bchar16_t\\b"), QStringLiteral("\\bdecltype\\b"),
        QStringLiteral("\\balignof\\b"), QStringLiteral("\\bnoexcept\\b"), QStringLiteral("\\bnull_ptr\\b"),
        QStringLiteral("\\band\\b"), QStringLiteral("\\bstatic_assert\\b"), QStringLiteral("\\bthread_local\\b"),
        QStringLiteral("\\bchar8_t\\b"), QStringLiteral("\\brequires\\b"),
        QStringLiteral("\\bconcept\\b"), QStringLiteral("\\bconsteval\\b"), QStringLiteral("\\bconstinit\\b"),
        QStringLiteral("\\bco_await\\b"), QStringLiteral("\\bco_return\\b"), QStringLiteral("\\bco_yield\\b"),
        QStringLiteral("\\bauto\\b"), QStringLiteral("\\bbreak\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    }

    keywordFormat_2.setForeground(QBrush(QColor(128,128,0)));
    keywordFormat_2.setFontWeight(QFont::Bold);
    const QString keywordPatterns_2[] = {
        QStringLiteral("\\bif\\b"), QStringLiteral("\\bclass\\b"), QStringLiteral("\\bconst\\b"),
        QStringLiteral("\\bpublic\\b"), QStringLiteral("\\bprivate\\b"), QStringLiteral("\\btrue\\b"),
        QStringLiteral("\\bfalse\\b"), QStringLiteral("\\bcatch\\b"), QStringLiteral("\\bprotected\\b"),
        QStringLiteral("\\btry\\b"), QStringLiteral("\\bfor\\b"), QStringLiteral("\\bswitch\\b"),
        QStringLiteral("\\bcase\\b")
};
    for (const QString &pattern : keywordPatterns_2) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat_2;
        highlightingRules.append(rule);
    }
    classFormat.setFontWeight(QFont::Bold);
       classFormat.setForeground(QBrush(QColor(128,0,170)));
       rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
       rule.format = classFormat;
       highlightingRules.append(rule);

       quotationFormat.setForeground(QBrush(QColor(0,128,0)));
       rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
       rule.format = quotationFormat;
       highlightingRules.append(rule);

       functionFormat.setFontItalic(true);
       functionFormat.setForeground(Qt::blue);
       rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
       rule.format = functionFormat;
       highlightingRules.append(rule);

       singleLineCommentFormat.setForeground(QBrush(QColor(128,0,0)));
          rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
          rule.format = singleLineCommentFormat;
          highlightingRules.append(rule);

          multiLineCommentFormat.setForeground(QBrush(QColor(128,0,0)));

          commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
          commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
      }
void Highlighter::highlightBlock(const QString &text){
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
           QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
           while (matchIterator.hasNext()) {
               QRegularExpressionMatch match = matchIterator.next();
               setFormat(match.capturedStart(), match.capturedLength(), rule.format);
           }
       }
}
