#pragma once
 class Cost
{
	int ID;
	int IDOfTrip;
	double Sum;
	QString Description;
public:
	Cost();
	Cost(int newID, int newIDOfTrip, double  newSum, QString newDescription);
	int GetOwnID();
	int GetIDOfTrip();
	double  GetSum();
	QString GetDescription();

};

