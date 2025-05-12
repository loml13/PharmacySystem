#ifndef ADDMEDICINEDIALOG_H
#define ADDMEDICINEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QDateEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include "Medicine.h"

class AddMedicineDialog : public QDialog {
    Q_OBJECT
public:
    AddMedicineDialog(QWidget* parent = nullptr);
    Medicine getMedicine() const;

private:
    QLineEdit* idInput;
    QLineEdit* nameInput;
    QComboBox* categoryInput;
    QLineEdit* manufacturerInput;
    QDoubleSpinBox* priceInput;
    QSpinBox* stockInput;
    QDateEdit* productionDateInput;
    QSpinBox* shelfLifeInput;

    void setupUI();
};

#endif // ADDMEDICINEDIALOG_H 