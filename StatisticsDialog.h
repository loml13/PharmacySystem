#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "Database.h"

class StatisticsDialog : public QDialog {
    Q_OBJECT
public:
    StatisticsDialog(Database& db, QWidget* parent = nullptr);

private:
    Database& database;
    QComboBox* periodCombo;
    QTableWidget* statsTable;

    void setupUI();

private slots:
    void refreshStats();
};

#endif // STATISTICSDIALOG_H 