#pragma once
#include<QString>
class Trip
{
	int ID;
	QString Country;
	QString City;
	QDate DepartureDate;
	QDate ReturnDate;
public:
	Trip();
	Trip(int newID, QString newCountry, QString newCity, QDate newDepartureDate, QDate newReturnDate);
	int GetID();
	QString GetCountry();
	QString GetCity();
	QDate GetDepartureDate();
	QDate GetReturnDate();
};

