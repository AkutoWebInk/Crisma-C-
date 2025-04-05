#pragma once
#include <iostream>

class Item{

    // Attributtes
    private:
        int id;
        std::string name;
        std::string reference;
        std::string code;
        std::string line;
        double capacity;
        int quantity;
        std::string imagepath;
    
    // Constructor
    public:
        Item(int id, const std::string& name, const std::string& reference, const std::string& code, const std::string& line,
         double capacity, int quantity, const std::string& imagepath);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getReference() const;
    std::string getCode() const;
    std::string getLine() const;
    double getCapacity() const;
    int getQuantity() const;
    std::string getImagePath() const;

    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setReference(const std::string& reference);
    void setCode(const std::string& code);
    void setLine(const std::string& line);
    void setCapacity(double capacity);
    void setQuantity(int quantity);
    void setImagePath(const std::string& imgPath);

};