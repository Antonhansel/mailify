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
  _mainLayout->addWidget(_time, 0, 0);
  _mainLayout->addWidget(_folders, 1, 0);
  _mainLayout->addWidget(_mailPreview, 1, 1);
  // _mainLayout->addWidget(_input, 1, 1, Qt::AlignLeft);
  // _mainLayout->addWidget(_send, 1, 1, Qt::AlignRight);
}

void  MainUI::timeLayout()
{
  _time = new QLCDNumber;
  _timer = new QTimer;

  _time->setDigitCount(12);
  _time->display(QTime::currentTime().toString(QString("hh:mm:ss")));
  _time->setPalette(Qt::red);
  _timer->start(100);
  _time->setFixedSize((WIDTH/5), (HEIGHT/20));
}

void    MainUI::countTime()
{
  _time->display(QTime::currentTime().toString(QString("hh:mm:ss")));
}

void MainUI::connectSlots()
{
  QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(countTime(void)));
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
  _toggleStatus = _fileMenu->addAction(tr("Change status"));
  _about = _fileMenu->addAction(tr("About"));
  _exitAction = _fileMenu->addAction(tr("E&xit"));
  _menuBar->addMenu(_fileMenu);

  connect(_exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(_toggleStatus, SIGNAL(triggered()), this, SLOT(toggleStatus()));
  connect(_about, SIGNAL(triggered()), this, SLOT(showAbout()));
}

void	MainUI::initLayouts()
{
  foldersLayout();
  mailPreviewLayout();
  menuBar();
  // inputLayout();
  // displayLayout();
  timeLayout();
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
  msgBox.setInformativeText("A simple mail client in C++ using Qt Framework, by ribeau_a\n");
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.exec();
}

MainUI::MainUI() : QWidget()
{
  initUi();
  initLayouts();
  applyLayouts();
  connectSlots();
  setLayout(_mainLayout);
  _console = new Console();
}

