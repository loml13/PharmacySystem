#ifndef PHARMACYSYSTEM_H
#define PHARMACYSYSTEM_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include "Database.h"

class PharmacySystem : public QMainWindow {
    Q_OBJECT

private:
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QTableWidget* medicineTable;
    QLineEdit* searchInput;
    QPushButton* addButton;
    QPushButton* sellButton;
    QPushButton* searchButton;
    QPushButton* statsButton;
    QPushButton* clearButton; // 添加清除按钮

    Database database;

public:
    PharmacySystem(QWidget* parent = nullptr);

private:
    void setupUI();
    void refreshTable();

private slots:
    void addMedicine();
    void sellMedicine();
    void searchMedicine();
    void showStatistics();
    void showClearOptions(); // 显示清除选项对话框
    void clearSalesRecords(); // 清除销售统计
    void clearInventory(); // 清除库存
    void clearAllData(); // 清除所有数据
};

#endif // PHARMACYSYSTEM_H