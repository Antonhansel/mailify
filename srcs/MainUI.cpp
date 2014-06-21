#include "MainUI.hpp"

void		MainUI::foldersLayout()
{
  _folders = new QTextEdit(this);
  _folders->setFixedWidth((WIDTH/5));
  _folders->setFrameStyle(QFrame::Box | QFrame::Sunken);
  _folders->setReadOnly(true);
  _folders->setStyleSheet
    ("background : url(.images/folders.png) center; color : white;");
}

void	MainUI::applyLayouts()
{
  _mainLayout->setMenuBar(_menuBar);
  _mainLayout->addWidget(_update, 0, 0);
  _mainLayout->addWidget(_folders, 1, 0);
  _mainLayout->addWidget(_mailPreview, 1, 1);
  _mainLayout->addWidget(_send, 0, 1, Qt::AlignRight);
}

void MainUI::updateMails()
{
  _mailRetrieve->getMails([] (std::vector<AMail *> mails){
      for (std::vector<AMail *>::iterator i = mails.begin(); i != mails.end(); ++i)
      {
         printf("New mail : %s\n", (*i)->subject().toUtf8().data());
          printf("From %s\n", (*i)->sender().toUtf8().data());
          printf("-> %s\n", (*i)->content().toUtf8().data());
      }
  });
}

void MainUI::connectSlots()
{
  QObject::connect(_send, SIGNAL(clicked()), this,SLOT(sendMail(void)));
  QObject::connect(_update, SIGNAL(clicked()), this,SLOT(updateMails(void)));
}

void  MainUI::mailPreviewLayout()
{
  _mailPreview = new QTextEdit(this);
  _mailPreview->setFrameStyle(QFrame::Box | QFrame::Sunken);
  _mailPreview->setReadOnly(true);
  _mailPreview->setStyleSheet
    ("background : url(.images/folders.png) center; color : white;");
}

void  MainUI::menuBar()
{
  _menuBar = new QMenuBar;
  _fileMenu = new QMenu(tr("&File"), this);
  _about = _fileMenu->addAction(tr("About"));
  _exitAction = _fileMenu->addAction(tr("E&xit"));
  _menuBar->addMenu(_fileMenu);

  connect(_exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(_about, SIGNAL(triggered()), this, SLOT(showAbout()));
}

void	MainUI::initLayouts()
{
  foldersLayout();
  mailPreviewLayout();
  menuBar();
  initButtons();
}

void MainUI::sendMail()
{
  _sendMail = new SendMail(this);
}

void	MainUI::initUi()
{
  _mainLayout = new QGridLayout;
  setFixedSize(HEIGHT, WIDTH);
  setWindowTitle(tr("Mailify"));
}

void            MainUI::showAbout() const
{
  QMessageBox msgBox;

  msgBox.setText("- Mailify -");
  msgBox.setInformativeText("A simple mail client in C++ using Qt Framework, by ribeau_a and besson_g\n");
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.exec();
}

void        MainUI::initButtons()
{
  _send = new QPushButton("Write a mail");
  _update = new QPushButton("Update mails");
}

MainUI::MainUI() : QWidget()
{
  initUi();
  initLayouts();
  applyLayouts();
  connectSlots();
  setLayout(_mainLayout);
  _smtp = new Smtp();
  _connexion = new Connexion(this);
}

Smtp *MainUI::smtp()
{
  return _smtp;
}

AMailRetrieve *MainUI::mailRetrieve()
{
  return _mailRetrieve;
}
void MainUI::mailRetrieve(AMailRetrieve *mailRetrive)
{
  _mailRetrieve = mailRetrive;
}

