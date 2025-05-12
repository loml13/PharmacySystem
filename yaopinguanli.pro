QT += core gui widgets

TARGET = yaopinguanli
TEMPLATE = app

SOURCES += \
    yaopinguanli.cpp \
    PharmacySystem.cpp \
    Database.cpp \
    AddMedicineDialog.cpp \
    SellMedicineDialog.cpp \
    StatisticsDialog.cpp \
    Medicine.cpp

HEADERS += \
    PharmacySystem.h \
    Database.h \
    AddMedicineDialog.h \
    SellMedicineDialog.h \
    StatisticsDialog.h \
    Medicine.h

# 定义预处理宏以指定数据目录
DEFINES += PROJECT_DATA_DIR=\\\"$$PWD/data\\\"
