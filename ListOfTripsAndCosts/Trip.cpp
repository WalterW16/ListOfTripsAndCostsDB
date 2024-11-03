#include "stdafx.h"
#include "Trip.h"


Trip::Trip()
	:ID(0), Country(""), City(""), DepartureDate(""), ReturnDate("")
{
}

Trip::Trip(int newID, QString newCountry, QString newCity, QString newDepartureDate, QString newReturnDate)
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

QString Trip::GetDepartureDate()
{
	return DepartureDate;
}

QString Trip::GetReturnDate()
{
	return ReturnDate;
}


