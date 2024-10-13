#ifndef RENTALPRICECALCULATOR_H
#define RENTALPRICECALCULATOR_H

#include <QDateTime>

class RentalPriceCalculator
{
public:
    RentalPriceCalculator(const QDateTime& startOfLease, const QDateTime& endOfLease, double baseCarRentalPricePerDay);

    double CalculateRentalPrice();

private:
    QDateTime startOfLease;
    QDateTime endOfLease;

    double baseCarRentalPricePerDay;
};

#endif // RENTALPRICECALCULATOR_H
