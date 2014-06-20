#ifndef A_MAIL_RETRIEVE_HPP
#define A_MAIL_RETRIEVE_HPP

#include <vector>

#include "AMail.hpp"

class AMailRetrieve {
public:
    virtual ~AMailRetrieve() = 0;
    virtual void connect(QString &user, QString &pass, QString &server, int port, std::function<void (std::string)>) = 0;
    virtual void &getMails(std::function<void (std::vector<AMail *>)) = 0;
};

#endif // A_MAIL_RETRIEVE_HPP
