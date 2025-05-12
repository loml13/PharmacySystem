#include "PharmacySystem.h"
#include "AddMedicineDialog.h"
#include "SellMedicineDialog.h"
#include "StatisticsDialog.h"
#include <QMessageBox>
#include <QDebug>

PharmacySystem::PharmacySystem(QWidget* parent) : QMainWindow(parent) {
    try {
        setWindowTitle("药店药品管理系统");
        setupUI();
        refreshTable();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "错误", "程序初始化失败：" + QString(e.what()));
    }
}

void PharmacySystem::setupUI() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);

    // Create search bar
    searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("输入药品名称或编号搜索");
    mainLayout->addWidget(searchInput);

    // Create buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("入库", this);
    sellButton = new QPushButton("销售", this);
    searchButton = new QPushButton("搜索", this);
    statsButton = new QPushButton("统计", this);
    clearButton = new QPushButton("清除", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(sellButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(statsButton);
    buttonLayout->addWidget(clearButton);
    mainLayout->addLayout(buttonLayout);

    // Create medicine table
    medicineTable = new QTableWidget(this);
    medicineTable->setColumnCount(8);
    medicineTable->setHorizontalHeaderLabels(
        {"药品编号", "药品名称", "类别", "生产商", "价格", "库存", "生产日期", "保质期"});
    mainLayout->addWidget(medicineTable);

    // Connect signals and slots
    connect(addButton, &QPushButton::clicked, this, &PharmacySystem::addMedicine);
    connect(sellButton, &QPushButton::clicked, this, &PharmacySystem::sellMedicine);
    connect(searchButton, &QPushButton::clicked, this, &PharmacySystem::searchMedicine);
    connect(statsButton, &QPushButton::clicked, this, &PharmacySystem::showStatistics);
    connect(clearButton, &QPushButton::clicked, this, &PharmacySystem::showClearOptions);
}

void PharmacySystem::refreshTable() {
    medicineTable->setRowCount(0);
    auto medicines = database.searchMedicines("");
    for (const auto& medicine : medicines) {
        int row = medicineTable->rowCount();
        medicineTable->insertRow(row);
        medicineTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(medicine.getId())));
        medicineTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(medicine.getName())));
        medicineTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(medicine.getCategory())));
        medicineTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(medicine.getManufacturer())));
        medicineTable->setItem(row, 4, new QTableWidgetItem(QString::number(medicine.getPrice(), 'f', 2)));
        medicineTable->setItem(row, 5, new QTableWidgetItem(QString::number(medicine.getStock())));
        
        QDateTime productionDate;
        productionDate.setSecsSinceEpoch(medicine.getProductionDate());
        medicineTable->setItem(row, 6, new QTableWidgetItem(productionDate.toString("yyyy-MM-dd")));
        
        medicineTable->setItem(row, 7, new QTableWidgetItem(QString::number(medicine.getShelfLife()) + " 天"));
    }
}

void PharmacySystem::addMedicine() {
    AddMedicineDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Medicine medicine = dialog.getMedicine();
        database.addMedicine(medicine);
        refreshTable();
    }
}

void PharmacySystem::sellMedicine() {
    int currentRow = medicineTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "警告", "请先选择要销售的药品");
        return;
    }

    std::string id = medicineTable->item(currentRow, 0)->text().toStdString();
    if (Medicine* medicine = database.findMedicine(id)) {
        SellMedicineDialog dialog(*medicine, this);
        if (dialog.exec() == QDialog::Accepted) {
            int quantity = dialog.getQuantity();
            medicine->setStock(medicine->getStock() - quantity);
            database.updateMedicine(*medicine);
            database.addSalesRecord(id, quantity);
            refreshTable();
        }
    }
}

void PharmacySystem::searchMedicine() {
    std::string query = searchInput->text().toStdString();
    auto results = database.searchMedicines(query);
    medicineTable->setRowCount(0);
    for (const auto& medicine : results) {
        int row = medicineTable->rowCount();
        medicineTable->insertRow(row);
        medicineTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(medicine.getId())));
        medicineTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(medicine.getName())));
        medicineTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(medicine.getCategory())));
        medicineTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(medicine.getManufacturer())));
        medicineTable->setItem(row, 4, new QTableWidgetItem(QString::number(medicine.getPrice(), 'f', 2)));
        medicineTable->setItem(row, 5, new QTableWidgetItem(QString::number(medicine.getStock())));
        
        QDateTime productionDate;
        productionDate.setSecsSinceEpoch(medicine.getProductionDate());
        medicineTable->setItem(row, 6, new QTableWidgetItem(productionDate.toString("yyyy-MM-dd")));
        
        medicineTable->setItem(row, 7, new QTableWidgetItem(QString::number(medicine.getShelfLife()) + " 天"));
    }
}

void PharmacySystem::showStatistics() {
    StatisticsDialog dialog(database, this);
    dialog.exec();
}

void PharmacySystem::showClearOptions() {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("清除数据");
    msgBox.setText("请选择要清除的数据类型：");
    
    QPushButton* salesButton = msgBox.addButton("清除销售记录", QMessageBox::ActionRole);
    QPushButton* inventoryButton = msgBox.addButton("清除库存", QMessageBox::ActionRole);
    QPushButton* allButton = msgBox.addButton("清除所有数据", QMessageBox::ActionRole);
    msgBox.addButton("取消", QMessageBox::RejectRole); // 不需要存储取消按钮的指针
    
    msgBox.exec();
    
    if (msgBox.clickedButton() == salesButton) {
        clearSalesRecords();
    } else if (msgBox.clickedButton() == inventoryButton) {
        clearInventory();
    } else if (msgBox.clickedButton() == allButton) {
        clearAllData();
    }
}

void PharmacySystem::clearSalesRecords() {
    QMessageBox confirmBox(QMessageBox::Warning, "确认操作", "确定要清除所有销售记录吗？此操作无法恢复！", 
                        QMessageBox::Yes | QMessageBox::No, this);
    if (confirmBox.exec() == QMessageBox::Yes) {
        database.clearSalesRecords();
        QMessageBox::information(this, "操作成功", "所有销售记录已清除");
        refreshTable();
    }
}

void PharmacySystem::clearInventory() {
    QMessageBox confirmBox(QMessageBox::Warning, "确认操作", "确定要清除所有库存数据吗？此操作无法恢复！", 
                        QMessageBox::Yes | QMessageBox::No, this);
    if (confirmBox.exec() == QMessageBox::Yes) {
        database.clearInventory();
        QMessageBox::information(this, "操作成功", "所有库存数据已清除");
        refreshTable();
    }
}

void PharmacySystem::clearAllData() {
    QMessageBox confirmBox(QMessageBox::Critical, "确认操作", "确定要清除所有数据吗？包括库存和销售记录！此操作无法恢复！", 
                        QMessageBox::Yes | QMessageBox::No, this);
    if (confirmBox.exec() == QMessageBox::Yes) {
        database.clearAllData();
        QMessageBox::information(this, "操作成功", "所有数据已清除");
        refreshTable();
    }
}