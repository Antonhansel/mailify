#include "Imap.hpp"

Imap::Imap(MainUI *mainui)
{
	_connected = false;
	_parent = mainui;
    _window = new QWidget;
    if (DEBUG)
        _window->show();
    _window->setFixedSize(500, 500);
    _window->setWindowTitle(tr("Debug IMAP"));
    _consoleText = new QTextEdit(this);
    _consoleText->setFrameStyle(QFrame::Box | QFrame::Sunken);
    _consoleText->setReadOnly(true);
    _consoleText->setStyleSheet("color: green ; background-color: black");
    _lineedit = new QLineEdit(this);
    _mainLayout = new QGridLayout;
    _mainLayout->addWidget(_consoleText, 0, 0);
    _mainLayout->addWidget(_lineedit, 1, 0);
    _window->setLayout(_mainLayout);
    QObject::connect(_lineedit, SIGNAL(returnPressed()),
        this,SLOT(getInput(void)));
}

void Imap::initConnexion(QString &username, QString &password, QString &server, int port, Connexion *callback)
{
    _username = username;
    _password = password;
    _server = server;
    _port = port;
    _callback = callback;
    _step = -1;
    initImap();
}

void  Imap::getInput()
{
    QString      input;

    input = _lineedit->text();
    _lineedit->setText("");
    _consoleText->append(input);
    input += '\n';
    QByteArray    data = input.toUtf8();
    _pSocket->write(data);
}

void Imap::readTcpData()
{
  QString input;
  QByteArray   	data = _pSocket->readAll();
  _consoleText->append(data);
}

void Imap::_ready()
{

}

void  Imap::sendData(QString input)
{
    _consoleText->append(input);
    input += '\n';
    QByteArray    data = input.toUtf8();
    _pSocket->write(data);
}

void Imap::initImap()
{
    _pSocket = new QSslSocket(this);
    connect(_pSocket, SIGNAL(encrypted()), this, SLOT(_ready()));
    connect(_pSocket, SIGNAL(readyRead()), SLOT(readTcpData()));
    _pSocket->connectToHost(_server, _port);
    if (_pSocket->waitForConnected())
        _consoleText->append("Connexion established.");
}

bool Imap::isConnected() const
{
  return (_connected);
}
