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

#include "BestSocketEver.hpp"

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
	void 	initConnexion(QString &, QString &, QString &, int, std::function<void (std::string)>);
	QString &username();
public slots:
	void 	readTcpData();
private:
	QString			_subject;
	QString			_data;
	QString			_to;
	QString			_from;
	int 			_port;
	bool 			_connected;
	std::function<void (std::string)> 		_callback;
	QString			_username;
	QString			_password;
	QString			_server;
	int 			_step;
	BestSocketEver  _pSocket;
};

#endif /* _SMTP_HPP_ */
