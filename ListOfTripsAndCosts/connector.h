#pragma once
#include <QSqlError>
#include <QtSql/QSqlDatabase>
static bool CreateConnection() {

    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("TripsAndCosts.db");

    if (!base.open()) {
        QMessageBox::critical(nullptr, "Database Error", base.lastError().text());
        return false;
    }
    return true;
}