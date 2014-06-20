#ifndef _SMTP_HPP_
#define _SMTP_HPP_


#define DEBUG true
// #define IP "smtp.gmail.com"
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

class Connexion;

class Smtp : public QWidget
{
Q_OBJECT
public:
	Smtp();
	void 	initSmtp();
	void 	inputLayout();
	void 	initConnexion(QString &, QString &, QString &, Connexion *);
public slots:
	void 	_ready();
	void 	getInput();
	void 	readTcpData();
	void 	sendData(QString input);
private:
	Connexion 		*_callback;
	QString			_username;
	QString			_password;
	QString			_server;
	int 			_step;
	QSslSocket  	*_pSocket;
	QTextEdit	    *_consoleText;
	QWidget 		*_window;
	QGridLayout	 	*_mainLayout;
	QLineEdit		*_lineedit;
};

#endif /* _SMTP_HPP_ */
