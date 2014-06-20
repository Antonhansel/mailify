#include "Connexion.hpp"

void	Connexion::applyLayouts()
{ 
  _mainLayout->addWidget(_address, 0, 1);
  _mainLayout->addWidget(_addressLabel, 0, 0);
  _mainLayout->addWidget(_pass, 1, 1);
  _mainLayout->addWidget(_passLabel, 1, 0);
  _mainLayout->addWidget(_connect, 3, 1);
}

void Connexion::connectSlots()
{
  QObject::connect(_connect, SIGNAL(clicked()), this,SLOT(tryConnect(void)));
}

void  Connexion::tryConnect()
{
  _addressString = _address->text();
  _passString = _pass->text();
  if (_addressString.endsWith("@gmail.com"))
  {
    QByteArray  addr64 = _addressString.toUtf8();
    QByteArray  pass64 = _passString.toUtf8();
    _addressString = addr64.toBase64();
    _passString = pass64.toBase64();
  }
}

void  Connexion::initConnexionStuff()
{
   _address = new QLineEdit(this);
   _addressLabel = new QLabel(this);
   _addressLabel->setText("Address");
   _addressLabel->setFixedWidth(200);
   _pass = new QLineEdit(this);
   _pass->setEchoMode(QLineEdit::Password);
   _passLabel = new QLabel(this);
   _passLabel->setText("pass");
   _connect = new QPushButton(this);
   _connect->setText("Connect!");
}

void	Connexion::initLayouts()
{
  initConnexionStuff();
}

void	Connexion::initUi()
{
  this->_mainLayout = new QGridLayout;
  this->_window->setFixedSize(500, 400);
  this->_window->setWindowTitle(tr("Connexion"));
  this->_window->setStyleSheet("color: #CFD6D7; background-color: #403075");
}

Connexion::Connexion() : QWidget()
{
  _displayAll = true;
  _window = new QWidget;
  initUi();
  initLayouts();
  applyLayouts();
  connectSlots();
  this->_window->setLayout(this->_mainLayout);
  this->_window->show();
}

QString   Connexion::getUsername() const 
{
  return (_addressString);
}

QString Connexion::getPassword() const
{
  return (_passString);
}
