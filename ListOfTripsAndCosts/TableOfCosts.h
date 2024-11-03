#pragma once
#include"Cost.h"
#include <QTableView>
#include <QMessageBox>
#include <QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>
class TableOfCosts
{
	QSqlTableModel* model;
public:
	TableOfCosts();
	
	static void createTable();
	void initModel(QSqlTableModel* someModel);
	bool AddCost(Cost & cost);
	bool RemoveCost(int Id);
	void FilterBySum(double minSum, double maxSum);
	void FilterByDescription(const QString& filter);
	bool UpdateView(Cost & cost);
	bool RecordExists(int id);
	void ShowAll();
};

