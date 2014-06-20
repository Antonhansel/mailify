#include "GetCredentials.hpp"

GetCredentials::GetCredentials()
{
}

GetCredentials::~GetCredentials()
{
}

bool 	GetCredentials::loaded()
{
	return (false);
}

bool 	GetCredentials::saveCredentials(QString user, QString pass, QString passMailify)
{
	QString checksum;
	checksum = QString(QCryptographicHash::hash((passMailify.toUtf8()),QCryptographicHash::Md5).toHex());
	pass = pass;
	user = user;
	return (true);
}