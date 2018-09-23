/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/08/01
  **********************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Product.h"

namespace AMA {
    //Protected member functions
    void Product::name(const char* name){
        delete [] m_name;
        if(nullptr == name){
            m_name = nullptr;
        }else{
            std::string nameCopy = name;
            if(nameCopy.length() < max_name_length){
                m_name = new char[nameCopy.length() + 1];
                strcpy(m_name, nameCopy.c_str());
            }else
                m_name = nullptr;
        }
    }
    const char* Product::name() const{
        return m_name;
    }
    const char* Product::sku() const{
        return m_sku;
    }
    const char* Product::unit() const{
        return m_unit;
    }
    bool Product::taxed() const{
        return m_taxed;
    }
    double Product::price() const{
        return m_price;
    }
    double Product::cost() const{
        return m_taxed ? price() * (TAX_RATE + 1): price();
    }
    void Product::message(const char* errorMessage){
        m_errorState.message(errorMessage);
    }
    bool Product::isClear() const{
        return m_errorState.isClear();
    }
    
    //Public member functions
    Product::Product(char type){
        m_type = type;
        m_sku[0] = '0';
        m_unit[0] = '0';
        m_name = nullptr;
        m_c_quantity = 0;
        m_n_quantity = 0;
        m_price = 0.0;
        m_taxed = true;
    }
    Product::Product(const char* sku, const char* name, const char* unit, int c_quantity, bool taxed, double price, int n_quantity){
        if(sku != nullptr){
            std::string temp = sku;
            if(temp.length() < max_sku_length)
                strcpy(m_sku, temp.c_str());
            else
                m_sku[0] = '\0';
        }
        
        m_name = nullptr;
        this->name(name);
        
        if(unit != nullptr){
            std::string temp = unit;
            if(temp.length() < max_unit_length)
                strcpy(m_unit, temp.c_str());
            else
                m_unit[0] = '\0';
        }
        
        m_c_quantity = c_quantity;
        m_taxed = taxed;
        m_price = price;
        m_n_quantity = n_quantity;
    }
    Product::Product(const Product& product){
        m_name = nullptr;
        *this = product;
    }
    Product& Product::operator=(const Product& product){
        if(this != &product){
            m_type = product.m_type;
            strcpy(m_sku, product.m_sku);
            strcpy(m_unit, product.m_unit);
            name(product.m_name);
            m_c_quantity = product.m_c_quantity;
            m_n_quantity = product.m_n_quantity;
            m_price = product.m_price;
            m_taxed = product.m_taxed;
            message(product.m_errorState.message());
        }
        return *this;
    }
    Product::~Product(){
        delete m_name;
    }
    std::fstream& Product::store(std::fstream& file, bool newLine) const{
        if(file){
            file << m_type << ',' << sku() << ',' << name() << ',' << unit() << ',' << (taxed()? 1: 0) << ',' << price() << ',' << quantity() << ',' << qtyNeeded();
            if(newLine) file << std::endl;
        }
        return file;
    }
    
    std::fstream& Product::load(std::fstream& file){
        if(file){
            char sku[max_sku_length + 1];
            char name[max_name_length + 1];
            char unit[max_unit_length + 1];
            int  c_quantity, n_quantity;
            double price;
            char taxed;
            file.getline(sku, max_sku_length + 1, ',');
            file.getline(name, max_name_length + 1, ',');
            file.getline(unit, max_unit_length + 1, ',');
            file >> taxed;
            file.ignore();
            file >> price;
            file.ignore();
            file >> c_quantity;
            file.ignore();
            file >> n_quantity;
            *this = Product(sku, name, unit, c_quantity, taxed != '0', price, n_quantity);
        }
        return file;
    }
    std::ostream& Product::write(std::ostream& os, bool linear) const{
        if(m_errorState.isClear()){
            if(linear){
                os << std::left << std::setw(max_sku_length) << sku() << '|'
                << std::setw(20) << name() << '|'
                << std::right << std::setw(7) << std::fixed <<std::setprecision(2)<< cost() << '|'
                << std::setw(4) << quantity() << '|'
                << std::left << std::setw(10) << unit() << '|'
                << std::right << std::setw(4) << qtyNeeded() << '|';
            }else{
                os << " Sku: " << sku() << std::endl
                << " Name (no spaces): " << name() << std::endl
                << " Price: " << price() << std::endl
                << " Price after tax: ";
                if(m_taxed == true){
                    os << cost();
                }else
                    os << "N/A";
                
                os << std::endl << " Quantity on hand: " << quantity() << ' ' << unit() << std::endl
                << " Quantity needed: " << qtyNeeded();
            }
        }else
            os << m_errorState.message();
        return os;
    }
    std::istream& Product::read(std::istream& is){
        std::string str;
        char sku[max_sku_length + 1];
        char name[max_name_length + 1];
        char unit[max_unit_length + 1];
        char taxed;
        double price;
        int c_quantity, n_quantity;
        
        std::cout << " Sku: ";
        is >> str;
        if(nullptr != str.c_str() && str.length() <= max_sku_length){
            strcpy(sku, str.c_str());
            std::cout << " Name (no spaces): ";
            is >> str;
            if(nullptr != str.c_str() && str.length() <= max_name_length){
                strcpy(name, str.c_str());
                std::cout << " Unit: ";
                is >> str;
                if(nullptr != str.c_str() && str.length() <= max_unit_length){
                    strcpy(unit, str.c_str());
                    std::cout << " Taxed? (y/n): ";
                    is >> taxed;
                    if(is.fail() || ( taxed != 'y' && taxed != 'Y' && taxed != 'n' && taxed != 'N')){
                        is.setstate(std::ios::failbit);
                        message("Only (Y)es or (N)o are acceptable");
                    }else{
                        std::cout << " Price: ";
                        is >> price;
                        if(is.fail()){
                            message("Invalid Price Entry");
                        }else{
                            std::cout << " Quantity on hand: ";
                            is >> c_quantity;
                            if(is.fail()){
                                message("Invalid Quantity Entry");
                            }else{
                                std::cout << " Quantity needed: ";
                                is >> n_quantity;
                                if(is.fail()){
                                    message("Invalid Quantity Needed Entry");
                                }else{
                                    Product temp(m_type);
                                    *this = Product(sku, name, unit, c_quantity, (taxed == 'y' || taxed == 'Y'), price, n_quantity);
                                    if(!isEmpty()) this->m_type = temp.m_type;
                                    //clear '\n' character
                                    is.ignore();
                                }
                            }
                        }
                    }
                }
            }
        }
        return is;
    }
    bool Product::operator==(const char* sku) const{
        return !strcmp(m_sku, sku);
    }
    double Product::total_cost() const{
        return cost() * quantity();
    }
    void Product::quantity(int c_quantity){
        m_c_quantity = c_quantity;
    }
    bool Product::isEmpty() const{
        return m_sku[0] == '0';
    }
    int Product::qtyNeeded() const{
        return m_n_quantity;
    }
    int Product::quantity() const{
        return m_c_quantity;
    }
    bool Product::operator>(const char* sku) const{
        return strcmp(m_sku, sku) > 0;
    }
    bool Product::operator>(const Product& product) const{
        return strcmp(name(), product.name()) > 0;
    }
    int Product::operator+=(int unit){
        return m_c_quantity = (unit > 0) ? m_c_quantity + unit : m_c_quantity;
    }
    //helper functions
    std::ostream& operator<<(std::ostream& os, const Product& product){
        return product.write(os, true);
    }
    std::istream& operator>>(std::istream& is, Product& product){
        return product.read(is);
    }
    double operator+=(double& total, const Product& product){
        return total += product.total_cost();
    }
}

