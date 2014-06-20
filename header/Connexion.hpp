#ifndef _CONNEXION_HPP_
# define _CONNEXION_HPP_

# include <sstream>
# include <iostream>
# include <QtCore>
# include <QFont>
# include <QPainter>
# include <QDesktopServices>
# include <QtWidgets/QApplication>
# include <QtWidgets/QPushButton>
# include <QtWidgets/QLCDNumber>
# include <QtWidgets/QColorDialog>
# include <QtWidgets/QGridLayout>
# include <QtWidgets/QHBoxLayout>
# include <QtWidgets/QGroupBox>
# include <QtWidgets/QDialog>
# include <QtWidgets/QMenuBar>
# include <QtWidgets/QMenu>
# include <QtWidgets/QAction>
# include <QtWidgets/QLabel>
# include <QtWidgets/QMessageBox>
# include <QLineEdit>
# include <QTextEdit>
# include <QString>
# include <QTime>
# include <QTimer>
# include "Smtp.hpp"
# include "GetCredentials.hpp"

class MainUI;

class	Connexion: public	QWidget
{
  Q_OBJECT
public:
  Connexion(MainUI *);
  QString   getUsername() const;
  QString   getPassword() const;
  void  callbackSmtp(std::string);
public slots:
  void  tryConnect();
private:
  void  connectSlots();
  void  initLayouts();
  void  foldersLayout();
  void  initUi();
  void  applyLayouts();
  void  timeLayout();
  void  initConnexionStuff();
  void 		getIds();
  void initConnexion(QString username, QString password, QString server);
protected:
  int       _sendStep;
  QString   _addressString;
  QString   _passString;
  QString   _serverAddressString;
  QString   _portString;
	bool 		_displayAll;
  QWidget    *_window;
 	MainUI 	 *_parent;
    QLabel       *_addressLabel;
    QLabel       *_portLabel;
    QLabel       *_passLabel;
  	QLabel       *_serverAddressLabel;
    QGridLayout  *_mainLayout;
    QLineEdit    *_address;
    QLineEdit    *_pass;
    QLineEdit    *_serverAddress;
    QLineEdit    *_port;
    QLineEdit    *_passMailify;
    QLabel     *_passMailifyLabel;
    QLabel     *_errorLabel;
  	QPushButton  *_connect;
};

#endif
