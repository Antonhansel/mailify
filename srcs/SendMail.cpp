#include "SendMail.hpp"

SendMail::SendMail(Console *console)
{
  this->_window = new QWidget;
  this->_window->setFixedSize(1000, 1000);
  this->_window->setWindowTitle(tr("Send a new mail"));
  this->_window->show();
  _console = console;
  this->_mainLayout = new QGridLayout;
  initInputs();
  this->_mainLayout->addWidget(_from, 0, 1);
  this->_mainLayout->addWidget(_fromLabel, 0, 0);
  this->_mainLayout->addWidget(_to, 1, 1);
  this->_mainLayout->addWidget(_toLabel, 1, 0);
  this->_mainLayout->addWidget(_subjectLabel, 2, 0);
  this->_mainLayout->addWidget(_subject, 2, 1);
  this->_mainLayout->addWidget(_text, 3, 1);
  this->_window->setLayout(this->_mainLayout);
}

void SendMail::initInputs()
{
  _from = new QLineEdit(this);
  _fromLabel = new QLabel(this);
  _fromLabel->setText("From: ");
  _fromLabel->setFixedWidth(130);
  _toLabel = new QLabel(this);
  _toLabel->setText("To:");
  _subjectLabel = new QLabel(this);
  _subjectLabel->setText("Subject: ");
  _to = new QLineEdit(this);
  _subject = new QLineEdit(this);
  _text = new QTextEdit(this);
  _text->setFrameStyle(QFrame::Box | QFrame::Sunken);
  _text->setReadOnly(false);
  _text->setStyleSheet("color: green ; background-color: black");
}

SendMail::~SendMail()
{

}