#ifndef MEDICINE_H
#define MEDICINE_H

#include <string>
#include <ctime>

class Medicine {
private:
    std::string id;
    std::string name;
    std::string category;
    std::string manufacturer;
    double price;
    int stock;
    std::time_t productionDate;
    int shelfLife; // in days
    std::time_t lastRestockDate;

public:
    Medicine(const std::string& id, const std::string& name, const std::string& category,
             const std::string& manufacturer, double price, int stock,
             std::time_t productionDate, int shelfLife)
        : id(id), name(name), category(category), manufacturer(manufacturer),
          price(price), stock(stock), productionDate(productionDate),
          shelfLife(shelfLife), lastRestockDate(std::time(nullptr)) {}

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    std::string getManufacturer() const { return manufacturer; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    std::time_t getProductionDate() const { return productionDate; }
    int getShelfLife() const { return shelfLife; }
    std::time_t getLastRestockDate() const { return lastRestockDate; }

    // Setters
    void setStock(int newStock) { stock = newStock; }
    void setPrice(double newPrice) { price = newPrice; }
    void setLastRestockDate(std::time_t date) { lastRestockDate = date; }

    // Check if medicine is expired
    bool isExpired() const {
        std::time_t now = std::time(nullptr);
        return (now - productionDate) > (shelfLife * 24 * 3600);
    }

    // Check if medicine is near expiration (within 30 days)
    bool isNearExpiration() const {
        std::time_t now = std::time(nullptr);
        return (shelfLife * 24 * 3600 - (now - productionDate)) < (30 * 24 * 3600);
    }
};

#endif // MEDICINE_H 