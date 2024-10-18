#include "fromqstringdatetimetoqdatetime.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

FromQStringDateTimeToQDateTime::FromQStringDateTimeToQDateTime() {}


QDateTime FromQStringDateTimeToQDateTime::ConvertFromServerDateTime(QString QStringDateTime){

    QRegularExpression re(QString("(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})"));
    QRegularExpressionMatch match = re.match(QStringDateTime);

    if (match.hasMatch()) {
        int month = match.captured(1).toInt();
        int day = match.captured(2).toInt();
        int year = match.captured(3).toInt();
        int hour = match.captured(4).toInt();
        int minute = match.captured(5).toInt();
        int second = match.captured(6).toInt();

        QDateTime dateTime;
        dateTime.setDate(QDate(year,month,day));
        dateTime.setTime(QTime(hour,minute,second));

        return dateTime;
    }
    else{
        throw std::runtime_error("Can't parse time from QStringTime");
    }
}

QDateTime FromQStringDateTimeToQDateTime::ConvertLikeISODateWithMs(QString QStringDateTime){

    QDateTime dateTime = QDateTime::fromString(QStringDateTime, Qt::ISODateWithMs);

    if(dateTime.isValid()){
        return dateTime;
    }

    throw std::runtime_error("Can't parse time from QStringTime");
}
