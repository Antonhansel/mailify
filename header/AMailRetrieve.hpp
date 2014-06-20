#ifndef A_MAIL_RETRIEVE_HPP
#define A_MAIL_RETRIEVE_HPP

#include <vector>

#include "AMail.hpp"

class AMailRetrieve {
public:
    virtual ~AMailRetrieve() = 0;
    virtual bool connect(QString &user, QString &pass, QString &server, int port) = 0;
    virtual std::vector<AMail *> &getMails() = 0;
};

#endif // A_MAIL_RETRIEVE_HPP
