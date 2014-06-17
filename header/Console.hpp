#ifndef _CONSOLE_HPP_
#define _CONSOLE_HPP_

#define DEBUG true
#define IP "smtp.gmail.com"
#define PORT 587

# include <QWidget>
# include <QtWidgets/QGridLayout>
# include <QTextEdit>
# include <QtNetwork>
# include <QtCore>
# include <iostream>

class Console : public QWidget
{
Q_OBJECT
public:
	Console();
	void 	initConsole();
public slots:
	void 	readTcpData();
private:
	QTcpSocket  	*_pSocket;
	QTextEdit	    *_consoleText;
	QWidget 		*_window;
	QGridLayout	 	*_mainLayout;
};

#endif /* _CONSOLE_HPP_ */