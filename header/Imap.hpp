#ifndef _IMAP_HPP_
# define _IMAP_HPP_

//port 993 google
#define DEBUG true

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
class MainUI;
class Imap : public QWidget
{
Q_OBJECT
public:
	Imap(MainUI *);
	void 	initImap();
	void 	inputLayout();
	void 	sendData(QString input);
	bool 	isConnected() const;
	void 	initConnexion(QString &, QString &, QString &, int, Connexion *);
public slots:
	void 	_ready();
	void 	getInput();
	void 	readTcpData();
private:
	MainUI 			*_parent;
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

#endif /* _IMAP_HPP_ */