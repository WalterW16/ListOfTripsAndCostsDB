#include "stdafx.h"
#include "Trip.h"


Trip::Trip()
	:ID(0), Country(""), City(""), DepartureDate(QDate::currentDate()), ReturnDate(QDate::currentDate())
{
}

Trip::Trip(int newID, QString newCountry, QString newCity, QDate newDepartureDate, QDate newReturnDate)
	:ID(newID), Country(newCountry), City(newCity), DepartureDate(newDepartureDate), ReturnDate(newReturnDate)
{
}

int Trip::GetID()
{
	return ID;
}

QString Trip::GetCountry()
{
	return Country;
}

QString Trip::GetCity()
{
	return City;
}

QDate  Trip::GetDepartureDate()
{
	return DepartureDate;
}

QDate  Trip::GetReturnDate()
{
	return ReturnDate;
}


