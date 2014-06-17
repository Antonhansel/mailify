#include "Console.hpp"

Console::Console()
{
  _window = new QWidget;
  if (DEBUG)
 	_window->show();
  _window->setFixedSize(1000, 1000);
  _window->setWindowTitle(tr("Debug Console"));
  _consoleText = new QTextEdit(this);
  _consoleText->setFrameStyle(QFrame::Box | QFrame::Sunken);
  _consoleText->setReadOnly(true);
  _consoleText->setStyleSheet("color: green ; background-color: black");
  _mainLayout = new QGridLayout;
  _mainLayout->addWidget(_consoleText, 0, 0);
  _window->setLayout(_mainLayout);
  initConsole();
}

void Console::initConsole()
{
  _pSocket = new QTcpSocket(this);
  connect(_pSocket, SIGNAL(readyRead()), SLOT(readTcpData()));
  _pSocket->connectToHost(IP, PORT);
  if (_pSocket->waitForConnected())
    _consoleText->append("Connexion established.");
}

void Console::readTcpData()
{
  QByteArray   	data = _pSocket->readAll();

  _consoleText->append(data);
}