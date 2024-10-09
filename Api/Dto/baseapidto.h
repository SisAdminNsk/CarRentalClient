#ifndef BASEAPIDTO_H
#define BASEAPIDTO_H

#include <QByteArray>

class BaseApiDto
{
public:
    BaseApiDto();
    virtual QByteArray ToByteArray() = 0;
};

#endif // BASEAPIDTO_H
