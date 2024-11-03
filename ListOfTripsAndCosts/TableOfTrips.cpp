#include "stdafx.h"
#include "TableOfTrips.h"



TableOfTrips::TableOfTrips()
{
    model =new QSqlTableModel(nullptr, QSqlDatabase::database());
}

void TableOfTrips::createTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Trips (ID INTEGER PRIMARY KEY, "
        "Country TEXT, City TEXT, Departure_Date TEXT, Return_Date TEXT)");
    
}

void TableOfTrips::initModel(QSqlTableModel* someModel)
{
    model = someModel;
    model->setTable("Trips");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Country"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("City"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Departure_Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Return_Date"));
}

bool TableOfTrips::AddTrip(Trip& trip)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Trips (ID, Country, City, Departure_Date, Return_Date) "
        "VALUES (:ID, :Country, :City, :Departure_Date, :Return_Date)");

    query.bindValue(":ID", trip.GetID());
    query.bindValue(":Country", trip.GetCountry());
    query.bindValue(":City", trip.GetCity());
    query.bindValue(":Departure_Date", trip.GetDepartureDate());
    query.bindValue(":Return_Date", trip.GetReturnDate());

    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to add trip: " + query.lastError().text());
        return false;
    }
    model->select();
    return true;
}

bool TableOfTrips::RemoveTrip(int Id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Trips WHERE ID = :ID");
    query.bindValue(":ID", Id);
    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to remove trip: " + query.lastError().text());
        return false;
    }
    model->select();
    return true;
}

void TableOfTrips::SortByCountry()
{
    model->setSort(1, Qt::AscendingOrder); 
    model->select();
}

void TableOfTrips::SortByDepartureDate()
{
    model->setSort(3, Qt::AscendingOrder);
    model->select();
}

bool TableOfTrips::UpdateView(Trip& trip)
{
    QSqlQuery query;
    query.prepare("UPDATE Trips SET Country = :Country, City = :City, "
        "Departure_Date = :Departure_Date, Return_Date = :Return_Date "
        "WHERE ID = :ID");

    query.bindValue(":ID", trip.GetID());
    query.bindValue(":Country", trip.GetCountry());
    query.bindValue(":City", trip.GetCity());
    query.bindValue(":Departure_Date", trip.GetDepartureDate());
    query.bindValue(":Return_Date", trip.GetReturnDate());

    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to update trip: " + query.lastError().text());
        return false;
    }
    model->select();
    return true;
}
bool TableOfTrips::RecordExists(int id)
{
    QSqlQuery query;
    query.prepare(QString("SELECT COUNT(*) FROM %1 WHERE ID = :ID").arg("Trips"));
    query.bindValue(":ID", id);

    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to check record existence: " + query.lastError().text());
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}

void TableOfTrips::ShowAll()
{
    model->setFilter("");
    model->select();
}

void TableOfTrips::CancelSorting()
{
    model->setSort(-1, Qt::AscendingOrder); 
    model->select();
}


