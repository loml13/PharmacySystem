#include "SellMedicineDialog.h"

SellMedicineDialog::SellMedicineDialog(const Medicine& medicine, QWidget* parent)
    : QDialog(parent), medicine(medicine) {
    setWindowTitle("销售药品");
    setupUI();
}

int SellMedicineDialog::getQuantity() const {
    return quantityInput->value();
}

void SellMedicineDialog::setupUI() {
    QFormLayout* layout = new QFormLayout(this);

    QLabel* nameLabel = new QLabel(QString::fromStdString(medicine.getName()), this);
    QLabel* priceLabel = new QLabel(QString::number(medicine.getPrice(), 'f', 2), this);
    QLabel* stockLabel = new QLabel(QString::number(medicine.getStock()), this);

    quantityInput = new QSpinBox(this);
    quantityInput->setRange(1, medicine.getStock());

    layout->addRow("药品名称:", nameLabel);
    layout->addRow("单价:", priceLabel);
    layout->addRow("库存:", stockLabel);
    layout->addRow("销售数量:", quantityInput);

    QPushButton* okButton = new QPushButton("确定", this);
    QPushButton* cancelButton = new QPushButton("取消", this);
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addRow(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
} 