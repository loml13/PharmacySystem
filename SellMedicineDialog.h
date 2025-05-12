#ifndef SELLMEDICINEDIALOG_H
#define SELLMEDICINEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include "Medicine.h"

class SellMedicineDialog : public QDialog {
    Q_OBJECT
public:
    SellMedicineDialog(const Medicine& medicine, QWidget* parent = nullptr);
    int getQuantity() const;

private:
    const Medicine& medicine;
    QSpinBox* quantityInput;

    void setupUI();
};

#endif // SELLMEDICINEDIALOG_H 