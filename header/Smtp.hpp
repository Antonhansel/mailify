#ifndef _SMTP_HPP_
#define _SMTP_HPP_

#define DEBUG true
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
	void 	sendData(QString input);
	bool 	isConnected() const;
	void 	setFrom(QString);
	void 	setTo(QString);
	void 	setData(QString);
	void 	setSubject(QString);
	void 	initConnexion(QString &, QString &, QString &, int, Connexion *);
	QString &username();
public slots:
	void 	_ready();
	void 	getInput();
	void 	readTcpData();
private:
	QString			_subject;
	QString			_data;
	QString			_to;
	QString			_from;
	int 			_port;
	bool 			_connected;
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
