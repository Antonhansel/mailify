#ifndef _SENDMAIL_HPP_
#define _SENDMAIL_HPP_

#include "Smtp.hpp"
#include <QLabel>
#include <QPushButton>
#include <iostream>
#include "Connexion.hpp"

class SendMail : public QWidget
{
 Q_OBJECT
public slots:
	void 	sendMessage();
public:
	SendMail(QWidget *);
	~SendMail();
	void 	initInputs();
private:
	QWidget 	*_parent;
	QPushButton	*_send;
	QLabel 		*_fromLabel;
	QLabel		*_toLabel;
	QLabel		*_subjectLabel;
	QGridLayout *_mainLayout;
	QLineEdit 	*_from;
	QLineEdit 	*_to;
	QLineEdit 	*_subject;
	QTextEdit 	*_text;
	Smtp 		*_console;
	QWidget 	*_window;
};

#endif /* _SENDMAIL_HPP_ */
