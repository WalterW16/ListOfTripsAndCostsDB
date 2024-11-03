#pragma once
#include"Trip.h"
#include <QTableView>
#include <QMessageBox>
#include <QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>
class TableOfTrips
{
	QSqlTableModel* model;
public:
	TableOfTrips();
	static void createTable();
	void initModel(QSqlTableModel* someModel);
	bool AddTrip( Trip & trip);
	bool RemoveTrip(int Id);
	void SortByCountry();
	void SortByDepartureDate();
	bool UpdateView(Trip& trip);
	bool RecordExists(int id);
	void ShowAll();
	void CancelSorting();
};

