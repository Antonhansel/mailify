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

class	Connexion: public	QWidget
{
  Q_OBJECT
public:
  Connexion();
  QString   getUsername() const;
  QString   getPassword() const;
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
protected:
  QString   _addressString;
  QString   _passString;
	bool 		_displayAll;
 	QWidget 	 *_window;
  	QLabel       *_addressLabel;
  	QLabel       *_passLabel;
  	QPushButton  *_connect;
  	QGridLayout	 *_mainLayout;
  	QLineEdit    *_address;
  	QLineEdit    *_pass;
  	QLineEdit 	 *_passMailify;
  	QLabel 		 *_passMailifyLabel;
};

#endif 
