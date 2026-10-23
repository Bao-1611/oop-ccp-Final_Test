#include <iostream>
#include <string>
#include <vector>

std::string formatMoney(long long amount) {
    std::string s = std::to_string(amount);
    int position = s.length() - 3;
    while (position > 0) {
        s.insert(position, ",");
        position -= 3;
    }
    return s;
}

class Bill {
private:
    std::string billId;
    std::string customerName;
    std::string address;
    int month;
    int year;

public:
    Bill(std::string id, std::string name, std::string addr, int m, int y) {
        billId = id;
        customerName = name;
        address = addr;
        month = m;
        year = y;
    }

    virtual ~Bill() {}

    std::string getBillId() const { return billId; }
    std::string getCustomerName() const { return customerName; }
    std::string getAddress() const { return address; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    virtual double calculateTotal() const = 0;
    virtual std::string getCategoryName() const = 0;
};

class ElectricityBill : public Bill {
private:
    double kwhConsumed;

public:
    ElectricityBill(std::string id, std::string name, std::string addr, int m, int y, double kwh) 
        : Bill(id, name, addr, m, y) {
        kwhConsumed = kwh;
    }

    double calculateTotal() const override {
        return kwhConsumed * 2500.0;
    }

    std::string getCategoryName() const override {
        return "Electricity";
    }
};

class WaterBill : public Bill {
private:
    double cubicMeters;

public:
    WaterBill(std::string id, std::string name, std::string addr, int m, int y, double m3) 
        : Bill(id, name, addr, m, y) {
        cubicMeters = m3;
    }

    double calculateTotal() const override {
        return cubicMeters * 10000.0;
    }

    std::string getCategoryName() const override {
        return "Water";
    }
};

class InternetBill : public Bill {
public:
    InternetBill(std::string id, std::string name, std::string addr, int m, int y) 
        : Bill(id, name, addr, m, y) {}

    double calculateTotal() const override {
        return 200000.0;
    }

    std::string getCategoryName() const override {
        return "Internet";
    }
};

int main() {
    std::vector<Bill*> bills;

    bills.push_back(new ElectricityBill("E001", "Nguyen Chi Bao", "Phuoc Long Ward, HCMC", 10, 2026, 120));
    bills.push_back(new WaterBill("W001", "Tran Ngoc Quoc Thinh", "Binh Phu Ward, HCMC", 10, 2026, 15));
    bills.push_back(new InternetBill("I001", "Tran Duc Viet", "Thu Duc City, HCMC", 10, 2026));
    bills.push_back(new ElectricityBill("E002", "Le Trung Hieu", "Di An Ward, HCMC", 10, 2026, 250));
    bills.push_back(new WaterBill("W002", "Donald J. Trump", "Washington, D.C.", 10, 2026, 22));
    bills.push_back(new InternetBill("I002", "Vladimir Putin", "Saint Petersburg", 10, 2026));
    bills.push_back(new ElectricityBill("E003", "Kim Jong Un", "Pyongyang", 10, 2026, 85));
    bills.push_back(new WaterBill("W003", "Benjamin Bibi Netanyahu", "Tel Aviv", 10, 2026, 10));
    bills.push_back(new InternetBill("I003", "Yu Ji-Min", "Seoul", 10, 2026));
    bills.push_back(new ElectricityBill("E004", "La Phuong Tien Dat", "Go Vap Ward, HCMC", 10, 2026, 310));

    std::cout << "=== LIST OF ALL BILLS ===" << std::endl;
    for (size_t i = 0; i < bills.size(); ++i) {
        std::cout << "Bill ID: " << bills[i]->getBillId() << std::endl;
        std::cout << "Category: " << bills[i]->getCategoryName() << std::endl;
        std::cout << "Customer: " << bills[i]->getCustomerName() << std::endl;
        std::cout << "Address: " << bills[i]->getAddress() << std::endl;
        std::cout << "Period: " << bills[i]->getMonth() << "/" << bills[i]->getYear() << std::endl;
        std::cout << "Total Amount: " << formatMoney(static_cast<long long>(bills[i]->calculateTotal())) << " VND" << std::endl;        
        std::cout << "-----------------------------------" << std::endl;
    }

    std::string categories[3] = {"Electricity", "Water", "Internet"};
    int counts[3] = {0, 0, 0};
    double totals[3] = {0.0, 0.0, 0.0};
    double grandTotal = 0.0;

    for (size_t i = 0; i < bills.size(); ++i) {
        double amount = bills[i]->calculateTotal();
        grandTotal += amount;

        for (int j = 0; j < 3; ++j) {
            if (bills[i]->getCategoryName() == categories[j]) {
                counts[j]++;
                totals[j] += amount;
            }
        }
    }

    std::cout << "=== UTILITY BILLING SUMMARY ===" << std::endl;
    for (int j = 0; j < 3; ++j) {
        std::cout << "Service Category: " << categories[j] << std::endl;
        std::cout << "Number of Bills: " << counts[j] << std::endl;
        std::cout << "Total Amount Billed: " << formatMoney(static_cast<long long>(totals[j])) << " VND" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }

    std::cout << "Grand Total Across All Bills: " << formatMoney(static_cast<long long>(grandTotal)) << " VND" << std::endl;

    for (size_t i = 0; i < bills.size(); ++i) {
        delete bills[i];
    }

    return 0;
}