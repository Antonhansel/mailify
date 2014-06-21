#ifndef _SENDMAIL_HPP_
#define _SENDMAIL_HPP_

#include "Smtp.hpp"
#include <QLabel>
#include <QPushButton>
#include <iostream>
#include "Connexion.hpp"

class MainUI;

class SendMail : public QWidget
{
 Q_OBJECT
public slots:
	void 	sendMessage();
public:
	SendMail(MainUI *);
	~SendMail();
	void 	initInputs();
	void 	flushMail();
private:
	Smtp 		*_smtp;
	Connexion 	*_connexion;
	MainUI 	*_parent;
	QPushButton	*_send;
	QLabel 		*_fromLabel;
	QLabel		*_toLabel;
	QLabel		*_subjectLabel;
	QLabel		*_errorLabel;
	QGridLayout *_mainLayout;
	QLineEdit 	*_from;
	QLineEdit 	*_to;
	QLineEdit 	*_subject;
	QTextEdit 	*_text;
	Smtp 		*_console;
	QWidget 	*_window;
};

#endif /* _SENDMAIL_HPP_ */
