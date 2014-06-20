#ifndef A_MAIL_HPP
#define A_MAIL_HPP

# include <QString>

class AMail {
public:
    virtual ~AMail() = 0;
    virtual QString &subject() = 0;
    virtual QString &sender() = 0;
    virtual QString &content() = 0;
    virtual void delete() = 0;
};

#endif // A_MAIL_HPP
