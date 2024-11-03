#include "stdafx.h"
#include "Cost.h"

Cost::Cost()
	: ID(0), IDOfTrip(0), Sum(0.0), Description("")
{
}

Cost::Cost(int newID, int newIDOfTrip, double newSum, QString newDescription)
	: ID(newID), IDOfTrip(newIDOfTrip), Sum(newSum), Description(newDescription)
{
}

int Cost::GetOwnID()
{
	return ID;
}

int Cost::GetIDOfTrip()
{
	return IDOfTrip;
}

double Cost::GetSum()
{
	return Sum;
}

QString Cost::GetDescription()
{
	return Description;
}

