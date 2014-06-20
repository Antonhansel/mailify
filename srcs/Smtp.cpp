#include "Smtp.hpp"
#include "Connexion.hpp"

Smtp::Smtp()
{
  _connected = false;
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
}

void Smtp::initConnexion(QString &username, QString &password, QString &server, int port, std::function<void (std::string)> callback)
{
    _username = username;
    _password = password;
    _server = server;
    _port = port;
    _callback = callback;
    _step = -1;
    initSmtp();
}

void  Smtp::getInput()
{
    _lineedit->setText("");
    sendData(_lineedit->text());
}

void  Smtp::sendData(QString input)
{
    _consoleText->append(input);
    input += '\n';
    _pSocket->write(input.toUtf8());
}

void Smtp::initSmtp()
{
    _pSocket = new QSslSocket(this);
    connect(_pSocket, SIGNAL(encrypted()), this, SLOT(_ready()));
    connect(_pSocket, SIGNAL(readyRead()), SLOT(readTcpData()));
    _pSocket->connectToHost(_server, _port);
    if (_pSocket->waitForConnected())
        _consoleText->append("Connexion established.");
}

void Smtp::_ready()
{

}

bool Smtp::isConnected() const
{
  return (_connected);
}

void  Smtp::setFrom(QString from)
{
  QString tmp;

  _from = from;
  tmp = "MAIL FROM: ";
  tmp += _from;
  printf("From : %s\n", tmp.toUtf8().data());
  sendData(tmp);
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
    if (data.startsWith("250 2.1") || data.startsWith("354"))
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
          _step++;
        }
        else if (_step == 8)
        {
          input = "From: ";
          input += _to;
          sendData(input);
          input = "To: ";
          input += _to;
          sendData(input);
          sendData(_subject);
          sendData(_data);
          sendData("\r\n.\r");
          _step = 6;
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
    if (_username.endsWith("@gmail.com"))
        sendData(_username.toUtf8().toBase64());
    else
        sendData(_username);
   _step++;
  }
  else if (_step == 4 && data.startsWith("334"))
  {
    if (_username.endsWith("@gmail.com"))
        sendData(_password.toUtf8().toBase64());
    else
        sendData(_password);
    _step++;
  }
  else if (_step == 5 && data.startsWith("235"))
  {
    _callback("");
    _step++;
    _connected = true;
  }
  else if (_step == 5 && data.startsWith("535"))
  {
    _callback("Error with login");
  }
}

QString &Smtp::username()
{
  return _username;
}

