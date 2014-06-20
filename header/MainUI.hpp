#ifndef MAIN_UI_HPP_
# define MAIN_UI__HPP_

#define WIDTH 600
#define HEIGHT 800

# include <sstream>
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
# include "SendMail.hpp"
# include "Connexion.hpp"
# include "Imap.hpp"

class	MainUI: public	QWidget
{
  Q_OBJECT
public:
  MainUI();
  Smtp *smtp();
public slots:
  void  countTime();
  void  showAbout() const;
  void  sendMail();
  void  fetchMails();
private:
  void  connectSlots();
  void  initLayouts();
  void  foldersLayout();
  void  initUi();
  void  applyLayouts();
  void  timeLayout();
  void  mailPreviewLayout();
  void  menuBar();
  void  initButtons();
protected:
  Imap        *_imap;
  Connexion   *_connexion;
  Smtp        *_smtp;
  SendMail     *_sendMail;
  QAction	     *_exitAction;
  QAction	     *_toggleStatus;
  QAction	     *_backgroundColor;
  QAction	     *_about;
  QMenuBar	   *_menuBar;
  QMenu		     *_fileMenu;
  QGridLayout	 *_mainLayout;
  QTextEdit	   *_folders;
  QTextEdit	   *_mailPreview;
  QLabel	     *_input;
  QPushButton	 *_send;
  QLCDNumber	 *_time;
  QTimer	     *_timer;
  QTimer	     *_timerec;
  QLineEdit	   *_lineedit;
};

#endif /* MAIN_UI_HPP_ */
