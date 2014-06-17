#include <QtGui>

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) : 
	QSyntaxHighlighter(parent) {

	HighlightingRule rule;

	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns;
	keywordPatterns << "\\bfunc\\b" << "\\bfor\\b" << "\\bwhile\\b"
		<< "\\bif\\b" << "\\belse\\b" ;
	foreach (const QString &pattern, keywordPatterns) {
		rule.pattern = QRegExp(pattern);
		rule.format = keywordFormat;
		highlightingRules.append(rule);

	}

	functionFormat.setFontItalic(true);
	functionFormat.setForeground(Qt::blue);

	rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
	rule.format = functionFormat;
	highlightingRules.append(rule);

	QTextCharFormat digitsFormat;
	digitsFormat.setForeground(Qt::red);
	rule.pattern = QRegExp("[0-9]+");
	rule.format = digitsFormat;

	highlightingRules.append(rule);


}

void Highlighter::highlightBlock(const QString &text)
{
	foreach (const HighlightingRule &rule, highlightingRules) {
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0) {
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);

		}

	}
}
