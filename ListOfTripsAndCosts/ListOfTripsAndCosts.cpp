#include "stdafx.h"
#include "ListOfTripsAndCosts.h"

ListOfTripsAndCosts::ListOfTripsAndCosts(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    CreateConnection();
    tableOfTrips.createTable();
  
    TripsModel = new QSqlTableModel(this, QSqlDatabase::database());    
    tableOfTrips.initModel(TripsModel);
    ui.TripTableView->setModel(TripsModel);
    ui.TripTableView->show();

  tableOfCosts.createTable();
    CostsModel = new QSqlTableModel(this, QSqlDatabase::database());
     tableOfCosts.initModel( CostsModel) ;
    ui.CostsTableView->setModel(CostsModel);
    ui.CostsTableView->show();
    ui.CostsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.TripTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.EditDepartureDate->date() = QDate::currentDate();
    ui.EditReturnDate->date() = QDate::currentDate();
    connect(ui.AddTripPushButton, &QPushButton::clicked, this, &ListOfTripsAndCosts::onAddTripButtonClicked);
    connect(ui.UpgrateTripsPushButton, &QPushButton::clicked, this, &ListOfTripsAndCosts::onUpdateTripButtonClicked);
    connect(ui.DeleteTripPushButton, &QPushButton::clicked, this, &ListOfTripsAndCosts::onDeleteTripButtonClicked);
    connect(ui.AddCostPushButton, &QPushButton::clicked, this, &ListOfTripsAndCosts::onAddCostButtonClicked);
    connect(ui.UpgrateCostsPushButton, &QPushButton::clicked, this, &ListOfTripsAndCosts::onUpdateCostButtonClicked);
    connect(ui.DeleteCostPushButton, &QPushButton::clicked, this, &ListOfTripsAndCosts::onDeleteCostButtonClicked);
    connect(ui.SortComboBox, &QComboBox::currentIndexChanged, this, &ListOfTripsAndCosts::ComboBoxSortChanged);
    connect(ui.FilterComboBox, &QComboBox::currentIndexChanged, this, &ListOfTripsAndCosts::ComboBoxFilterChanged);
    connect(ui.ApplyPushButton, &QPushButton::clicked, this, &ListOfTripsAndCosts::onApplyFilterButtonClicked);
    connect(ui.showAllCosts, &QPushButton::clicked, this, &ListOfTripsAndCosts::onShowAllCosts);
    connect(ui.showAllTrips, &QPushButton::clicked, this, &ListOfTripsAndCosts::onShowAllTrips);
    connect(ui.CancelSortBtn, &QPushButton::clicked, this, &ListOfTripsAndCosts::onClearSortButtonClicked);
    ui.minlabel->hide();
    ui.maxlabel->hide();
    ui.MinSum->hide();
    ui.maxSum->hide();
    ui.CancelSortBtn->hide();
    ui.ApplyPushButton->hide();
}


ListOfTripsAndCosts::~ListOfTripsAndCosts()
{}

void ListOfTripsAndCosts::onDeleteCostButtonClicked()
{
    int id = ui.EditCostID->value();
    if (id == 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid cost ID.");
        return;
    }

    if (!tableOfCosts.RecordExists( id)) {
        QMessageBox::warning(this, "Error", "No cost found with the specified ID.");
        return;
    }

    if (tableOfCosts.RemoveCost(id)) {
        QMessageBox::information(this, "Success", "Cost deleted successfully!");
        TripsModel->select();
    }
    else {
        QMessageBox::warning(this, "Error", "Failed to delete the trip.");
    }
    ui.EditCostID->clear();
    ui.EditCTripID->clear();
    ui.EditSum->clear();
    ui.DescriptionText->clear();
}

void ListOfTripsAndCosts::onUpdateCostButtonClicked()
{
    int id = ui.EditCostID->value();
    if (id == 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid cost ID.");
        return;
    }

    if (!tableOfCosts.RecordExists( id)) {
        QMessageBox::warning(this, "Error", "No cost found with the specified ID.");
        return;
    }

    Cost updCost(id, ui.EditCTripID->value(), ui.EditSum->value(), ui.DescriptionText->text());
    if (tableOfCosts.UpdateView(updCost)) {
        QMessageBox::information(this, "Success", "Cost updated successfully!");
        TripsModel->select();
    }
    else {
        QMessageBox::warning(this, "Error", "Failed to update the cost.");
    }
    ui.EditCostID->clear();
    ui.EditCTripID->clear();
    ui.EditSum->clear();
    ui.DescriptionText->clear();
}

void ListOfTripsAndCosts::onAddTripButtonClicked()
{
    
    if (ui.EditITripID->value() <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid Trip ID.");
        return;
    }
    if (tableOfTrips.RecordExists(ui.EditITripID->value())) {
        QMessageBox::warning(this, "Error", "A trip with this ID already exists.");
        return;
    }

    if (ui.EditCountry->text().isEmpty() || ui.EditCity->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all required fields: Country and City.");
        return;
    }
    if (ui.EditDepartureDate->text().isEmpty() || ui.EditReturnDate->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all required fields: Country and City.");
        return;
    }
   
    Trip newTrip(ui.EditITripID->value(), ui.EditCountry->text(), ui.EditCity->text(), ui.EditDepartureDate->date(), ui.EditReturnDate->date());
    if (tableOfTrips.AddTrip(newTrip)) {
        QMessageBox::information(this, "Success", "Trip added successfully!");
        TripsModel->select();
    }
    else {
        QMessageBox::warning(this, "Error", "Failed to add the trip.");
    }
    ui.EditITripID->clear();
    ui.EditCountry->clear();
    ui.EditCity->clear();
    ui.EditDepartureDate->date() = QDate::currentDate();
    ui.EditReturnDate->date() = QDate::currentDate();  
    
}

void ListOfTripsAndCosts::onAddCostButtonClicked()
{
  
    if (ui.EditCostID->value() <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid Cost ID.");
        return;
    }
    if (tableOfCosts.RecordExists(ui.EditCostID->value())) {
        QMessageBox::warning(this, "Error", "A cost with this ID already exists.");
        return;
    }

    if (ui.EditCTripID->value() <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid Trip ID associated with the cost.");
        return;
    }

    if (ui.EditSum->value() <= 0) {
        QMessageBox::warning(this, "Error", "Sum must be greater than 0.");
        return;
    }

    if (ui.DescriptionText->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a description for the cost.");
        return;
    }

    Cost newCost(ui.EditCostID->value(), ui.EditCTripID->value(), ui.EditSum->value(), ui.DescriptionText->text());
    if (!tableOfCosts.AddCost(newCost)) {
        QMessageBox::warning(this, "Error", "Failed to add the cost.");
    }
    else {
        QMessageBox::information(this, "Success", "Cost added successfully!");
        CostsModel->select();
    }
    ui.EditCostID->clear();
    ui.EditCTripID->clear();
    ui.EditSum->clear();
    ui.DescriptionText->clear();
  
}

void ListOfTripsAndCosts::onDeleteTripButtonClicked()
{
    int id = ui.EditITripID->value();
    if (id == 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid trip ID.");
        return;
    }

    if (!tableOfTrips.RecordExists( id)) {
        QMessageBox::warning(this, "Error", "No trip found with the specified ID.");
        return;
    }

    if (tableOfTrips.RemoveTrip(id)) {
        QMessageBox::information(this, "Success", "Trip deleted successfully!");
        TripsModel->select();
    }
    else {
        QMessageBox::warning(this, "Error", "Failed to delete the trip.");
    }
    ui.EditITripID->clear();
    ui.EditCountry->clear();
    ui.EditCity->clear();
    ui.EditDepartureDate->date() = QDate::currentDate();
    ui.EditReturnDate->date() = QDate::currentDate();
    

}

void ListOfTripsAndCosts::onUpdateTripButtonClicked()
{
    int id = ui.EditITripID->value();
    if (id == 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid trip ID.");
        return;
    }

    if (!tableOfTrips.RecordExists( id)) {
        QMessageBox::warning(this, "Error", "No trip found with the specified ID.");
        return;
    }

    Trip updTrip(id, ui.EditCountry->text(), ui.EditCity->text(), ui.EditDepartureDate->date(), ui.EditReturnDate->date());
    if (tableOfTrips.UpdateView(updTrip)) {
        QMessageBox::information(this, "Success", "Trip updated successfully!");
        TripsModel->select();
    }
    else {
        QMessageBox::warning(this, "Error", "Failed to update the trip.");
    }
    ui.EditITripID->clear();
    ui.EditCountry->clear();
    ui.EditCity->clear();
    ui.EditDepartureDate->date() = QDate::currentDate();
    ui.EditReturnDate->date() = QDate::currentDate();
 

}

void ListOfTripsAndCosts::ComboBoxFilterChanged()
{
    
        int index = ui.FilterComboBox->currentIndex();

        
        if (index == 2) { 
            ui.minlabel->show();
            ui.maxlabel->show();
            ui.MinSum->show();
            ui.maxSum->show();
            ui.ApplyPushButton->show();
            ui.ApplyPushButton->setEnabled(true);
        }
        else if (index == 1) { 
           
            ui.ApplyPushButton->show();
            ui.ApplyPushButton->setEnabled(true); 
        }
        else {
            ui.minlabel->hide();
            ui.maxlabel->hide();
            ui.MinSum->hide();
            ui.maxSum->hide();
            ui.DescriptionText->hide();
            ui.ApplyPushButton->setEnabled(false); 
        }

}

void ListOfTripsAndCosts::ComboBoxSortChanged()
{
    if (ui.SortComboBox->currentIndex() == 1) {
        tableOfTrips.SortByCountry();
        QMessageBox::information(this, "Success", "Sorted successfully!");
    }
    else if (ui.SortComboBox->currentIndex() == 2) {
        tableOfTrips.SortByDepartureDate();
        QMessageBox::information(this, "Success", "Sorted successfully!");
    }
    ui.CancelSortBtn->show();
}

void ListOfTripsAndCosts::onApplyFilterButtonClicked()
{
    int index = ui.FilterComboBox->currentIndex();

    if (index == 2) { 
        double minSum = ui.MinSum->value();
        double maxSum = ui.maxSum->value();
        tableOfCosts.FilterBySum(minSum, maxSum);
        CostsModel->select();
        QMessageBox::information(this, "Success", "Filtered successfully!");
    }
    else if (index == 1) { 
        QString description = ui.DescriptionText->text();
        if (description.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a description for filtering.");
            return;
        }
        tableOfCosts.FilterByDescription(description);
        CostsModel->select();
        QMessageBox::information(this, "Success", "Filtered successfully!");
    }


    ui.minlabel->hide();
    ui.maxlabel->hide();
    ui.MinSum->hide();
    ui.maxSum->hide();
    ui.DescriptionText->clear();
    ui.ApplyPushButton->setEnabled(false);
    ui.ApplyPushButton->hide();
}

void ListOfTripsAndCosts::onShowAllTrips()
{
    tableOfTrips.ShowAll();
}

void ListOfTripsAndCosts::onShowAllCosts()
{
    tableOfCosts.ShowAll();
}

void ListOfTripsAndCosts::onClearSortButtonClicked()
{
    tableOfTrips.CancelSorting();
    ui.CancelSortBtn->hide();
}
