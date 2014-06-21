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

#include "BestSocketEver.hpp"

class Connexion;
class Smtp : public QWidget
{
Q_OBJECT
public:
	Smtp();
	void 	initSmtp();
	void 	inputLayout();
	bool 	isConnected() const;
	void 	sendMail(QString from, QString to, QString subject, QString data, std::function<void (std::string)> callback);
	void 	initConnexion(QString &, QString &, QString &, int, std::function<void (std::string)>);
	QString &username();
private:
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
