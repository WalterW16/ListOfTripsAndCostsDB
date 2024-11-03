#include "stdafx.h"
#include "TableOfCosts.h"



TableOfCosts::TableOfCosts()
{
    model = new QSqlTableModel(nullptr, QSqlDatabase::database());
}

void TableOfCosts::createTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Expenses ("
               "ID INTEGER PRIMARY KEY, "
               "ID_Of_Trip INTEGER, "
               "Sum REAL, "
               "Description TEXT, "
        "FOREIGN KEY (ID_Of_Trip) REFERENCES Trips(ID))");
 
}

void TableOfCosts::initModel(QSqlTableModel* someModel)
{
    model = someModel;
    model->setTable("Expenses");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Of_Trip"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Sum"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Descrtption"));
   
}

bool TableOfCosts::AddCost(Cost& cost)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Expenses (ID, ID_Of_Trip, Sum, Description) "
        "VALUES (:ID, :ID_Of_Trip, :Sum, :Descrtption)");

    query.bindValue(":ID", cost.GetOwnID());
    query.bindValue(":ID_Of_Trip", cost.GetIDOfTrip());
    query.bindValue(":Sum", cost.GetSum());
    query.bindValue(":Descrtption", cost.GetDescription()); 
   
    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to add cost: " + query.lastError().text());
        return false;
    }
    model->select();
    return true;

}

bool TableOfCosts::RemoveCost(int Id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Expenses WHERE ID = :ID");
    query.bindValue(":ID", Id);

    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to remove cost: " + query.lastError().text());
        return false;
    }
    model->select();
    return true;
}



void TableOfCosts::FilterBySum(double minSum, double maxSum)
{
    if (model) { // Перевірка наявності моделі
        model->setFilter(QString("Sum BETWEEN %1 AND %2").arg(minSum).arg(maxSum));
        if (!model->select()) {
            QMessageBox::warning(nullptr, "Error", "Failed to apply filter: " + model->lastError().text());
        }
    }
    else {
        QMessageBox::warning(nullptr, "Error", "Model is not initialized.");
    }
}


void TableOfCosts::FilterByDescription(const QString& filter)
{
    if (model) { // Перевірка наявності моделі
        model->setFilter(QString("Description LIKE '%%1%'").arg(filter));
        if (!model->select()) {
            QMessageBox::warning(nullptr, "Error", "Failed to apply filter: " + model->lastError().text());
        }
    }
    else {
        QMessageBox::warning(nullptr, "Error", "Model is not initialized.");
    }
}

bool TableOfCosts::UpdateView(Cost & cost)
{
    QSqlQuery query;
    query.prepare("UPDATE Expenses SET ID_Of_Trip = :ID_Of_Trip, "
        "Sum = :Sum, Description = :Description "
        "WHERE ID = :ID");

    query.bindValue(":ID", cost.GetOwnID());
    query.bindValue(":ID_Of_Trip", cost.GetIDOfTrip());
    query.bindValue(":Sum", cost.GetSum());
    query.bindValue(":Description", cost.GetDescription());

    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to update cost: " + query.lastError().text());
        return false;
    }

    model->select();  
    return true;
}

bool TableOfCosts::RecordExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Expenses WHERE ID = :ID");
    query.bindValue(":ID", id);

    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to check record existence: " + query.lastError().text());
        return false;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        return true;
    }

    return false;
}

void TableOfCosts::ShowAll()
{
    model->setFilter("");
    model->select();
}



