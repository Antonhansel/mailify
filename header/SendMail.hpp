#ifndef _SENDMAIL_HPP_
#define _SENDMAIL_HPP_

#include "Console.hpp"
#include <QLabel>

class SendMail : public QWidget
{
 Q_OBJECT
public:
	SendMail(Console *console);
	~SendMail();
	void 	initInputs();
private:
	QLabel 		*_fromLabel;
	QLabel		*_toLabel;
	QLabel		*_subjectLabel;
	QGridLayout *_mainLayout;
	QLineEdit 	*_from;
	QLineEdit 	*_to;
	QLineEdit 	*_subject;
	QTextEdit 	*_text;
	Console 	*_console;
	QWidget 	*_window;
};

#endif /* _SENDMAIL_HPP_ */