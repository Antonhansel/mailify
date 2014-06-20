#ifndef _SMTP_HPP_
#define _SMTP_HPP_


#define DEBUG true
#define IP "smtp.gmail.com"
#define PORT 587

# include <unistd.h>
# include <QWidget>
# include <QtWidgets/QGridLayout>
# include <QTextEdit>
# include <QtNetwork>
# include <QSslSocket>
# include <QtCore>
# include <iostream>
# include <QLineEdit>

class Smtp : public QWidget
{
Q_OBJECT
public:
	Smtp(QString, QString);
	void 	initSmtp();
	void 	inputLayout();
public slots:
	void 	getInput();
	void 	readTcpData();
	void 	sendData(QString input);
private:
	QString			_username;
	QString			_password;
	int 			_step;
	QSslSocket  	*_pSocket;
	QTextEdit	    *_consoleText;
	QWidget 		*_window;
	QGridLayout	 	*_mainLayout;
	QLineEdit		*_lineedit;
};

#endif /* _SMTP_HPP_ */