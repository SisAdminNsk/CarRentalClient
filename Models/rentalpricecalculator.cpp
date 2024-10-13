#include "rentalpricecalculator.h"

RentalPriceCalculator::RentalPriceCalculator(const QDateTime& startOfLease, const QDateTime& endOfLease, double baseCarRentalPricePerDay) :
    startOfLease(startOfLease),
    endOfLease(endOfLease),
    baseCarRentalPricePerDay(baseCarRentalPricePerDay)
{

}

double RentalPriceCalculator::CalculateRentalPrice(){

    int fullRentalDays = startOfLease.daysTo(endOfLease);

    if(startOfLease.time() < endOfLease.time()){
        int partialRentalDays = 1;
        fullRentalDays += partialRentalDays;
    }

    return fullRentalDays * baseCarRentalPricePerDay;
}
