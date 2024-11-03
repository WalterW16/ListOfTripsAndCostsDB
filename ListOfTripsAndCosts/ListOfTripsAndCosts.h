#pragma once

#include <QtWidgets/QWidget>
#include "ui_ListOfTripsAndCosts.h"
#include"connector.h"
#include"TableOfTrips.h"
#include"TableOfCosts.h"
class ListOfTripsAndCosts : public QWidget
{
    Q_OBJECT

public:
    ListOfTripsAndCosts(QWidget *parent = nullptr);
    ~ListOfTripsAndCosts();

private:
    Ui::ListOfTripsAndCostsClass ui;
    TableOfTrips tableOfTrips;
    TableOfCosts tableOfCosts;
    QSqlTableModel* TripsModel;
    QSqlTableModel* CostsModel;
private slots:
    void onAddCostButtonClicked();
    void onDeleteCostButtonClicked();
    void onUpdateCostButtonClicked();
    void onAddTripButtonClicked();
    void onDeleteTripButtonClicked();
    void onUpdateTripButtonClicked();
    void ComboBoxFilterChanged();
    void ComboBoxSortChanged();
    void onApplyFilterButtonClicked();
    void onShowAllTrips();
    void onShowAllCosts();
};
