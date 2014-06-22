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
# include <QRadioButton>
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
  QRadioButton  *_popChoose;
  QRadioButton  *_imapChoose;
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
  void  initConnexion(QString username, QString password, QString server);
protected:
  int       _sendStep;
  bool    _displayAll;
  QWidget    *_window;
  MainUI   *_parent;
  QLabel        *_addressLabel;
  QLineEdit     *_address;
  QString       _addressString;
  QLabel        *_portLabel;
  QLineEdit     *_port;
  QString       _portString;
  QLabel        *_receiveServerAddressLabel;
  QLineEdit     *_receiveServerAddress;
  QString       _receiveServerAddressString;
  QLabel        *_receivePortLabel;
  QLineEdit     *_receivePort;
  QString       _receivePortString;
  QLabel        *_passLabel;
  QLineEdit     *_pass;
  QString       _passString;
  QLabel        *_serverAddressLabel;
  QLineEdit     *_serverAddress;
  QString       _serverAddressString;
  QGridLayout   *_mainLayout;
  QLabel        *_errorLabel;
  QPushButton   *_connect;
};

#endif
