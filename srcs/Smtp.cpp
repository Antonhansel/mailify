#include "Smtp.hpp"

Smtp::Smtp(QString username, QString password)
{
  _connected = false;
  _username = username;
  _password = password;
  _step = -1;
  _window = new QWidget;
  if (DEBUG)
 	_window->show();
  _window->setFixedSize(1000, 1000);
  _window->setWindowTitle(tr("Debug Smtp"));
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
  initSmtp();
}

void  Smtp::getInput()
{
  QString      input;

  input = _lineedit->text();
  _lineedit->setText("");
  _consoleText->append(input);
  input += '\n';
  QByteArray    data = input.toUtf8();
  _pSocket->write(data);
}

void  Smtp::sendData(QString input)
{
  _consoleText->append(input);
  input += '\n';
  QByteArray    data = input.toUtf8();
  _pSocket->write(data);
}

void Smtp::initSmtp()
{
  _pSocket = new QSslSocket(this);
  connect(_pSocket, SIGNAL(readyRead()), SLOT(readTcpData()));
  _pSocket->connectToHost(IP, PORT);
  if (_pSocket->waitForConnected())
    _consoleText->append("Connexion established.");
}

bool Smtp::isConnected() const
{
  return (_connected);
}


void  Smtp::setFrom(QString from)
{
  _from = from;
}

void Smtp::setTo(QString to)
{
  _to = to;
}

void  Smtp::setData(QString data)
{
  _data = data;
}

void  Smtp::setSubject(QString subject)
{
  _subject = subject;
}

void Smtp::readTcpData()
{
  QString input;
  QByteArray   	data = _pSocket->readAll();
  _consoleText->append(data);
  if (_connected == true)
  {
    if (data.startsWith("250") || data.startsWith("354")) 
    {
        if (_step == 6)
        {
          input = "RCPT TO: ";
          input += _to;
          sendData(input);
          _step++;
        }
        else if (_step == 7)
        {
          sendData("DATA");
          sleep(1);
          sendData(_subject);
          sendData(_data);
          sendData("\r\n.\r\nquit");
          _step++;
        }
    }
   }
  else if (_step == -1 && data.startsWith("220"))
  {
    sendData("EHLO localhost");
    _step++;
  }
  else if (_step == 0 && data.startsWith("250"))
  {
    sendData("STARTTLS");
    _step++;
  }
  else if (_step == 1 && data.startsWith("220 2.0.0 Ready to start TLS"))
  {
    _pSocket->startClientEncryption();
    usleep(300);
    sendData("EHLO google.fr");
    _step++;
  }
  else if (_step == 2)
  {
    sendData("AUTH LOGIN");
    _step++;
  }
  else if (_step == 3 && data.startsWith("334"))
  {
   sendData(_username);
   _step++;
  }
  else if (_step == 4 && data.startsWith("334"))
  {
    sendData(_password);
    _step++;
  }
  else if (_step == 5 && data.startsWith("235"))
  {
    _step++;
    _connected = true;
    input = "MAIL FROM: ";
    input += _from;
    sendData(input);
  }
}

