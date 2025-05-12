#include <QApplication>
#include "PharmacySystem.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PharmacySystem window;
    window.show();
    return app.exec();
} 