#ifndef _GETCREDENTIALS_HPP_
# define _GETCREDENTIALS_HPP_

# include <QtCore>
# include <fstream>

class GetCredentials
{
public:
	GetCredentials();
	~GetCredentials();
	bool 	loaded();
	bool 	saveCredentials(QString, QString, QString);
private:
};

#endif 