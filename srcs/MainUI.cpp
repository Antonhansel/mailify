#include "MainUI.hpp"

void		MainUI::foldersLayout()
{
    _folders = new QListWidget(this);
    _folders->setFixedWidth((WIDTH/5));
    _folders->setFrameStyle(QFrame::Box | QFrame::Sunken);
    _folders->setStyleSheet("color: white; background-color: black");
    connect(_folders, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(changedFolders(QListWidgetItem *, QListWidgetItem *)));
}

void    MainUI::changedFolders(QListWidgetItem *current, QListWidgetItem *old)
{
    (void)old;
    _mailRetrieve->switchFolder(_foldersList[current]);
}

void    MainUI::changedItem(QListWidgetItem *current, QListWidgetItem *old)
{
    (void)old;
    _mailPreview->setHtml(_emails[current]->content());
}

void    MainUI::updateFolders()
{
    _mailRetrieve->getFolders([this] (std::vector<std::string> folders){
        QString temp;
    for (std::vector<std::string>::iterator i = folders.begin(); i != folders.end(); ++i)
        {
            temp = (*i).c_str();
            QListWidgetItem *email = new QListWidgetItem(temp, _folders);
            _foldersList[email] = *i;
        }
    });
}

void MainUI::updateMails()
{
    if (_emails.size() < 100)
    {
    _mailRetrieve->getMails([this] (std::vector<AMail *> mails){
    for (std::vector<AMail *>::iterator i = mails.begin(); i != mails.end(); ++i)
        {
            QListWidgetItem *email = new QListWidgetItem((*i)->subject(), _mailListing);
            _emails[email] = *i;
        }
    });
    if (!_connexion->_popChoose->isChecked())
        _getFolders->setVisible(true);
    }
}

void	MainUI::applyLayouts()
{
    _mainLayout->setMenuBar(_menuBar);
    _mainLayout->addWidget(_folders, 1, 0);
    _mainLayout->addWidget(_getFolders, 0, 0);

    _buttonLayout->addWidget(_send, 0, 0);
    _buttonLayout->addWidget(_update, 0, 1);

    _mailLayout->addWidget(_mailPreview, 1, 0);
    _mailLayout->addWidget(_mailListing, 0, 0);
    _mainLayout->addLayout(_buttonLayout, 0, 1);
    _mainLayout->addLayout(_mailLayout, 1, 1);
    _getFolders->setVisible(false);
}

void MainUI::connectSlots()
{
    QObject::connect(_send, SIGNAL(clicked()), this,SLOT(sendMail(void)));
    QObject::connect(_update, SIGNAL(clicked()), this,SLOT(updateMails(void)));
    QObject::connect(_getFolders, SIGNAL(clicked()), this,SLOT(updateFolders(void)));
}

void  MainUI::mailPreviewLayout()
{
    _mailPreview = new QWebView(this);
    // _mailPreview->setFrameStyle(QFrame::Box | QFrame::Sunken);
    // _mailPreview->setReadOnly(true);
    // _mailPreview->setStyleSheet("color: black;");
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

void MainUI::mailListingLayout()
{
    _mailListing = new QListWidget(this);
    _mailListing->setFixedHeight(WIDTH/3);
    _mailListing->setFrameStyle(QFrame::Box | QFrame::Sunken);
    _mailListing->setStyleSheet("color: black;");
    connect(_mailListing, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(changedItem(QListWidgetItem *, QListWidgetItem *)));
}

void	MainUI::initLayouts()
{
    foldersLayout();
    mailListingLayout();
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
    _mailLayout = new QGridLayout;
    _buttonLayout = new QGridLayout;
    setFixedSize(HEIGHT, WIDTH);
    setWindowTitle(tr("Mailify"));
    setVisible(false);
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
    _getFolders = new QPushButton("Get Folders");
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

