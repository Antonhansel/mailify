#ifndef A_MAIL_RETRIEVE_HPP
#define A_MAIL_RETRIEVE_HPP

#include <vector>
#include <QtCore>

#include "AMail.hpp"

class AMailRetrieve : public QObject {
Q_OBJECT
public:
    virtual ~AMailRetrieve() {};
    virtual void initConnexion(QString &user, QString &pass, QString &server, int port, std::function<void (std::string)>) = 0;
    virtual void getMails(std::function<void (std::vector<AMail *>)>) = 0;
	virtual void getFolders(std::function<void (std::vector<std::string>)>) = 0;
};

#endif // A_MAIL_RETRIEVE_HPP
