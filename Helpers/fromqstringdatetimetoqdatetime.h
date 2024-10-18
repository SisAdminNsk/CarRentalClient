#ifndef FROMQSTRINGDATETIMETOQDATETIME_H
#define FROMQSTRINGDATETIMETOQDATETIME_H

#include <QDateTime>
#include <QString>

class FromQStringDateTimeToQDateTime
{
public:
    FromQStringDateTimeToQDateTime();

    static QDateTime ConvertFromServerDateTime(QString QStringDateTime);
    static QDateTime ConvertLikeISODateWithMs(QString QStringDateTime);
};

#endif // FROMQSTRINGDATETIMETOQDATETIME_H
