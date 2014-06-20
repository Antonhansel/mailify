#include "Connexion.hpp"
#include "MainUI.hpp"

void	Connexion::applyLayouts()
{
    _mainLayout->addWidget(_addressLabel, 0, 0);
    _mainLayout->addWidget(_address, 0, 1);
    _mainLayout->addWidget(_passLabel, 1, 0);
    _mainLayout->addWidget(_pass, 1, 1);
    _mainLayout->addWidget(_serverAddressLabel, 2, 0);
    _mainLayout->addWidget(_serverAddress, 2, 1);
    _mainLayout->addWidget(_errorLabel, 3, 0);
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
    _serverAddressString = _serverAddress->text();
    if (!_addressString.size() || !_passString.size() || !_serverAddressString.size())
    {
        _errorLabel->setText("Fill every field");
        return;
    }
    QByteArray  addr64 = _addressString.toUtf8();
    QByteArray  pass64 = _passString.toUtf8();
    _addressString = addr64.toBase64();
    _passString = pass64.toBase64();
    _parent->smtp()->initConnexion(_addressString, _passString, _serverAddressString, this);
}

void  Connexion::callbackSmtp(std::string error)
{
    if (error.size())
    {
        _errorLabel->setText(error.c_str());
        return;
    }
    this->_window->hide();
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
    _passLabel->setText("Password");
    _serverAddress = new QLineEdit(this);
    _serverAddressLabel = new QLabel(this);
    _serverAddressLabel->setText("Server Address");
    _connect = new QPushButton(this);
    _connect->setText("Connect!");
    _errorLabel = new QLabel(this);
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

Connexion::Connexion(MainUI *parent) : QWidget()
{
    _parent = parent;
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
