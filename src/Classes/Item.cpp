#include "Item.h"

// Constructor Implementation:


Item::Item(int id, const std::string& name, const std::string& reference, const std::string& code, const std::string& line, 
double capacity, int quantity, const std::string& imagepath) : 
    id(id), 
    name(name), 
    reference(reference), 
    code(code), 
    line(line), 
    capacity(capacity), 
    quantity(quantity), 
    imagepath(imagepath) {}


    // Getters
    int Item::getId() const{return id;}
    std::string Item::getName()const{return name;}
    std::string Item::getReference() const{return reference;}
    std::string Item::getCode() const {return code;}
    std::string Item::getLine() const {return line;}
    double Item::getCapacity() const{return capacity;}
    int Item::getQuantity() const {return quantity;}
    std::string Item::getImagePath() const {return imagepath;}

    // Setters
    void Item::setId(int id){this->id = id;}
    void Item::setName(const std::string& name){this-> name=name;}
    void Item::setReference(const std::string& reference){this->reference=reference;}
    void Item::setCode(const std::string& code){this-> code=code;}
    void Item::setLine(const std::string& line){this-> line=line;}
    void Item::setCapacity(double capacity){this-> capacity=capacity;}
    void Item::setQuantity(int quantity){this-> quantity=quantity;}
    void Item::setImagePath(const std::string& imagepath){this-> imagepath=imagepath;}