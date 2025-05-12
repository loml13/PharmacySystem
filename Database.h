#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
#include "Medicine.h"

class Database {
private:
    std::vector<Medicine> medicines;
    std::map<std::string, std::vector<std::pair<std::time_t, int>>> salesRecords;
    std::string dataDir;
    std::string MEDICINE_FILE;
    std::string SALES_FILE;

public:
    Database() {
        try {
            // 指定数据目录在项目文件夹的data子文件夹中
            // 使用绝对路径指向项目文件夹的data子目录
            dataDir = "E:/cpp_code/yaopinguanli_project/data";
            
            qDebug() << "数据目录:" << QString::fromStdString(dataDir);
            
            // 确保目录存在
            if (std::filesystem::create_directories(dataDir)) {
                qDebug() << "创建数据目录成功";
            }
            
            MEDICINE_FILE = dataDir + "/medicines.dat";
            SALES_FILE = dataDir + "/sales.dat";
            qDebug() << "药品数据文件:" << QString::fromStdString(MEDICINE_FILE);
            qDebug() << "销售数据文件:" << QString::fromStdString(SALES_FILE);
            
            loadData();
        } catch (const std::exception& e) {
            QMessageBox::warning(nullptr, "警告", "初始化数据库失败：" + QString(e.what()));
        }
    }

    ~Database() {
        try {
            saveData();
        } catch (const std::exception& e) {
            QMessageBox::warning(nullptr, "警告", "保存数据失败：" + QString(e.what()));
        }
    }

    void addMedicine(const Medicine& medicine) {
        try {
            medicines.push_back(medicine);
            qDebug() << "添加药品:" << QString::fromStdString(medicine.getName());
            saveData();
        } catch (const std::exception& e) {
            QMessageBox::warning(nullptr, "警告", "添加药品失败：" + QString(e.what()));
        }
    }

    void updateMedicine(const Medicine& medicine) {
        try {
            for (auto& m : medicines) {
                if (m.getId() == medicine.getId()) {
                    m = medicine;
                    qDebug() << "更新药品:" << QString::fromStdString(medicine.getName());
                    break;
                }
            }
            saveData();
        } catch (const std::exception& e) {
            QMessageBox::warning(nullptr, "警告", "更新药品失败：" + QString(e.what()));
        }
    }

    Medicine* findMedicine(const std::string& id) {
        for (auto& medicine : medicines) {
            if (medicine.getId() == id) {
                return &medicine;
            }
        }
        return nullptr;
    }

    std::vector<Medicine> searchMedicines(const std::string& query) {
        std::vector<Medicine> results;
        for (const auto& medicine : medicines) {
            if (medicine.getName().find(query) != std::string::npos ||
                medicine.getId().find(query) != std::string::npos) {
                results.push_back(medicine);
            }
        }
        return results;
    }

    void addSalesRecord(const std::string& medicineId, int quantity) {
        salesRecords[medicineId].push_back({std::time(nullptr), quantity});
        saveData();
    }

    std::map<std::string, double> getSalesByCategory(std::time_t start, std::time_t end) {
        std::map<std::string, double> categorySales;
        for (const auto& [id, records] : salesRecords) {
            if (Medicine* medicine = findMedicine(id)) {
                double totalSales = 0;
                for (const auto& [time, quantity] : records) {
                    if (time >= start && time <= end) {
                        totalSales += medicine->getPrice() * quantity;
                    }
                }
                categorySales[medicine->getCategory()] += totalSales;
            }
        }
        return categorySales;
    }
    
    // 清除销售统计数据
    void clearSalesRecords() {
        salesRecords.clear();
        saveData();
    }
    
    // 清除库存数据并重置
    void clearInventory() {
        medicines.clear();
        saveData();
    }
    
    // 清除所有数据
    void clearAllData() {
        medicines.clear();
        salesRecords.clear();
        saveData();
    }

private:
    void saveData() {
        try {
            qDebug() << "开始保存数据...";
            
            // Save medicines
            std::ofstream medFile(MEDICINE_FILE);
            if (!medFile.is_open()) {
                throw std::runtime_error("无法打开药品数据文件：" + MEDICINE_FILE);
            }
            
            for (const auto& medicine : medicines) {
                medFile << medicine.getId() << ","
                       << medicine.getName() << ","
                       << medicine.getCategory() << ","
                       << medicine.getManufacturer() << ","
                       << medicine.getPrice() << ","
                       << medicine.getStock() << ","
                       << medicine.getProductionDate() << ","
                       << medicine.getShelfLife() << "\n";
            }
            qDebug() << "保存药品数据成功";

            // Save sales records
            std::ofstream salesFile(SALES_FILE);
            if (!salesFile.is_open()) {
                throw std::runtime_error("无法打开销售数据文件：" + SALES_FILE);
            }
            
            for (const auto& [id, records] : salesRecords) {
                for (const auto& [time, quantity] : records) {
                    salesFile << id << "," << time << "," << quantity << "\n";
                }
            }
            qDebug() << "保存销售数据成功";
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("保存数据失败: ") + e.what());
        }
    }

    void loadData() {
        try {
            qDebug() << "开始加载数据...";
            
            // Load medicines
            std::ifstream medFile(MEDICINE_FILE);
            if (!medFile.is_open()) {
                qDebug() << "药品数据文件不存在，创建新文件";
                std::ofstream createFile(MEDICINE_FILE);
                return;
            }

            std::string line;
            while (std::getline(medFile, line)) {
                std::stringstream ss(line);
                std::string id, name, category, manufacturer;
                double price;
                int stock;
                std::time_t productionDate;
                int shelfLife;
                
                std::getline(ss, id, ',');
                std::getline(ss, name, ',');
                std::getline(ss, category, ',');
                std::getline(ss, manufacturer, ',');
                ss >> price; ss.ignore();
                ss >> stock; ss.ignore();
                ss >> productionDate; ss.ignore();
                ss >> shelfLife;

                medicines.emplace_back(id, name, category, manufacturer, price, stock, productionDate, shelfLife);
            }
            qDebug() << "加载药品数据成功，共" << medicines.size() << "条记录";

            // Load sales records
            std::ifstream salesFile(SALES_FILE);
            if (!salesFile.is_open()) {
                qDebug() << "销售数据文件不存在，创建新文件";
                std::ofstream createFile(SALES_FILE);
                return;
            }

            while (std::getline(salesFile, line)) {
                std::stringstream ss(line);
                std::string id;
                std::time_t time;
                int quantity;
                
                std::getline(ss, id, ',');
                ss >> time; ss.ignore();
                ss >> quantity;

                salesRecords[id].push_back({time, quantity});
            }
            qDebug() << "加载销售数据成功";
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("加载数据失败: ") + e.what());
        }
    }
};

#endif // DATABASE_H