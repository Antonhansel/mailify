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
# include <QLineEdit>

class Console : public QWidget
{
Q_OBJECT
public:
	Console();
	void 	initConsole();
	void 	inputLayout();
public slots:
	void 	getInput();
	void 	readTcpData();
private:
	QTcpSocket  	*_pSocket;
	QTextEdit	    *_consoleText;
	QWidget 		*_window;
	QGridLayout	 	*_mainLayout;
	QLineEdit		*_lineedit;
};

#endif /* _CONSOLE_HPP_ */