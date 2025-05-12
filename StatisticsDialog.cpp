#include "StatisticsDialog.h"

StatisticsDialog::StatisticsDialog(Database& db, QWidget* parent)
    : QDialog(parent), database(db) {
    setWindowTitle("销售统计");
    setupUI();
}

void StatisticsDialog::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    periodCombo = new QComboBox(this);
    periodCombo->addItems({"今日", "本月", "本季度", "本年"});
    layout->addWidget(periodCombo);

    statsTable = new QTableWidget(this);
    statsTable->setColumnCount(2);
    statsTable->setHorizontalHeaderLabels({"类别", "销售额"});
    layout->addWidget(statsTable);

    QPushButton* refreshButton = new QPushButton("刷新", this);
    layout->addWidget(refreshButton);

    connect(refreshButton, &QPushButton::clicked, this, &StatisticsDialog::refreshStats);
    connect(periodCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &StatisticsDialog::refreshStats);

    refreshStats();
}

void StatisticsDialog::refreshStats() {
    std::time_t now = std::time(nullptr);
    std::time_t start;
    switch (periodCombo->currentIndex()) {
        case 0: // 今日
            start = now - 24 * 3600;
            break;
        case 1: // 本月
            start = now - 30 * 24 * 3600;
            break;
        case 2: // 本季度
            start = now - 90 * 24 * 3600;
            break;
        case 3: // 本年
            start = now - 365 * 24 * 3600;
            break;
        default:
            start = now - 24 * 3600;
    }

    auto categorySales = database.getSalesByCategory(start, now);
    statsTable->setRowCount(static_cast<int>(categorySales.size()));
    int row = 0;
    for (const auto& [category, sales] : categorySales) {
        statsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(category)));
        statsTable->setItem(row, 1, new QTableWidgetItem(QString::number(sales, 'f', 2)));
        row++;
    }
} 