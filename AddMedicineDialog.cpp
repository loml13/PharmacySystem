#include "AddMedicineDialog.h"

AddMedicineDialog::AddMedicineDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("添加药品");
    setupUI();
}

Medicine AddMedicineDialog::getMedicine() const {
    return Medicine(
        idInput->text().toStdString(),
        nameInput->text().toStdString(),
        categoryInput->currentText().toStdString(),
        manufacturerInput->text().toStdString(),
        priceInput->value(),
        stockInput->value(),
        productionDateInput->dateTime().toSecsSinceEpoch(),
        shelfLifeInput->value()
    );
}

void AddMedicineDialog::setupUI() {
    QFormLayout* layout = new QFormLayout(this);

    idInput = new QLineEdit(this);
    nameInput = new QLineEdit(this);
    categoryInput = new QComboBox(this);
    categoryInput->addItems({"处方药", "非处方药", "中药", "西药", "保健品"});
    manufacturerInput = new QLineEdit(this);
    priceInput = new QDoubleSpinBox(this);
    priceInput->setRange(0, 999999.99);
    priceInput->setDecimals(2);
    stockInput = new QSpinBox(this);
    stockInput->setRange(0, 999999);
    productionDateInput = new QDateEdit(this);
    productionDateInput->setCalendarPopup(true);
    productionDateInput->setDate(QDate::currentDate());
    shelfLifeInput = new QSpinBox(this);
    shelfLifeInput->setRange(1, 3650);
    shelfLifeInput->setSuffix(" 天");

    layout->addRow("药品编号:", idInput);
    layout->addRow("药品名称:", nameInput);
    layout->addRow("药品类别:", categoryInput);
    layout->addRow("生产厂家:", manufacturerInput);
    layout->addRow("价格:", priceInput);
    layout->addRow("库存:", stockInput);
    layout->addRow("生产日期:", productionDateInput);
    layout->addRow("保质期:", shelfLifeInput);

    QPushButton* okButton = new QPushButton("确定", this);
    QPushButton* cancelButton = new QPushButton("取消", this);
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addRow(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
} 