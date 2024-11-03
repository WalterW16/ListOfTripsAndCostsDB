#pragma once
#include<QString>
class Trip
{
	int ID;
	QString Country;
	QString City;
	QString DepartureDate;
	QString ReturnDate;
public:
	Trip();
	Trip(int newID, QString newCountry, QString newCity, QString newDepartureDate, QString newReturnDate);
	int GetID();
	QString GetCountry();
	QString GetCity();
	QString GetDepartureDate();
	QString GetReturnDate();	
};

