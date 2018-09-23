/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/08/06
  **********************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Product.h"

namespace AMA {
    //**Protected member functions of Product class**
    
    //Setting product name
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

    //Returning product name
    const char* Product::name() const{
        return m_name;
    }
    
    //Returning the sku of product
    const char* Product::sku() const{
        return m_sku;
    }
    
     //Returning the unit of product
    const char* Product::unit() const{
        return m_unit;
    }
    
    //Returning taxable status of product
    bool Product::taxed() const{
        return m_taxed;
    }
    
    //Returning the price of product
    double Product::price() const{
        return m_price;
    }
    
    //Returning the cost of product
    double Product::cost() const{
        return m_taxed ? price() * (TAX_RATE + 1): price();
    }
    
    //Setting error message
    void Product::message(const char* errorMessage){
        m_errorState.message(errorMessage);
    }
    
    //Returning ErrorState
    bool Product::isClear() const{
        return m_errorState.isClear();
    }
    
    //**Public member functions of Product class**
    
    //Zero-one argument constructor
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
    
    //Seven argument constructor
    Product::Product(const char* sku, const char* name, const char* unit, int c_quantity, bool taxed, double price, int n_quantity){
        std::string tempSku = sku;
        std::string tempName = name;
        std::string tempUnit = unit;
        
        //I believe that we should do validation to avoid program crush even it is not mandatory in instruction document
        if(sku == nullptr || sku[0] == '\0' || tempSku.length() > max_sku_length ||
           name == nullptr || name[0] == '\0' || tempName.length() > max_name_length ||
           unit == nullptr || unit[0] == '\0' || tempUnit.length() > max_unit_length){
            m_name = nullptr;
            *this = Product();
        }else{
            strcpy(m_sku, tempSku.c_str());
            
            m_name = nullptr;
            this->name(name);
            
            strcpy(m_unit, tempUnit.c_str());
            
            m_c_quantity = c_quantity;
            m_taxed = taxed;
            m_price = price;
            m_n_quantity = n_quantity;
        }
    }
    
    //Copy Constructor
    Product::Product(const Product& product){
        m_name = nullptr;
        *this = product;
    }
    
    //Copy Assignmen Operator
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
    
    //Destructor
    Product::~Product(){
        delete m_name;
    }
    
    //Inserting a single product data into a file object
    std::fstream& Product::store(std::fstream& file, bool newLine) const{
        if(file){
            file << m_type << ',' << sku() << ',' << name() << ',' << unit() << ',' << (taxed()? 1: 0) << ',' << price() << ',' << quantity() << ',' << qtyNeeded();
            if(newLine) file << std::endl;
        }
        return file;
    }
    
    //Extracting a single product data from a file object into a product
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
    
    //Inserting a sigle product data into a ostream object
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
                
                os << std::endl << " Quantity on Hand: " << quantity() << ' ' << unit() << std::endl
                << " Quantity needed: " << qtyNeeded();
            }
        }else
            os << m_errorState.message();
        return os;
    }
    
    //Extrating a single product data from an istream object and store it into a product object
    std::istream& Product::read(std::istream& is){
        char sku[max_sku_length + 1];
        char name[max_name_length + 1];
        char unit[max_unit_length + 1];
        char taxed;
        double price;
        int c_quantity, n_quantity;
        
        std::cout << " Sku: ";
        is >> sku;
        std::cout << " Name (no spaces): ";
        is >> name;
        std::cout << " Unit: ";
        is >> unit;
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
                    }else if(is.get() == '\n'){ //checking trailing inputs
                        Product temp(sku, name, unit, c_quantity, (taxed == 'y' || taxed == 'Y'), price, n_quantity);
                        //checking if input is valid
                        if(!temp.isEmpty()){
                            char type = this->m_type;
                            *this = temp;
                            this->m_type = type;
                        }
                    }
                }
            }
        }
        return is;
    }
    
    //Comparing product sku
    bool Product::operator==(const char* sku) const{
        return !strcmp(m_sku, sku);
    }
    
    //Returning total cost of all iteams of the product on hand
    double Product::total_cost() const{
        return cost() * quantity();
    }
    
    //Reseting the number of product on hand
    void Product::quantity(int c_quantity){
        m_c_quantity = c_quantity;
    }
    
    //Checking safe empty state
    bool Product::isEmpty() const{
        return m_sku[0] == '0';
    }
    
    //Returning the number of product that are needed
    int Product::qtyNeeded() const{
        return m_n_quantity;
    }
    
    //Returning the number of product that are on hand
    int Product::quantity() const{
        return m_c_quantity;
    }
    
    //Comparing product sku
    bool Product::operator>(const char* sku) const{
        return strcmp(m_sku, sku) > 0;
    }
    
    //Comparing any kind of product name in the product hierachy
    bool Product::operator>(const iProduct& iproduct) const{
        return strcmp(name(), iproduct.name()) > 0;
    }
    
    //Reseting the number of product on hand
    int Product::operator+=(int unit){
        return m_c_quantity = (unit > 0) ? m_c_quantity + unit : m_c_quantity;
    }

    //**helper functions of Product class**
    
    //Inserting any kind of product record  in the product hierachy into an ostream object
    std::ostream& operator<<(std::ostream& os, const iProduct& iproduct){
        return iproduct.write(os, true);
    }
    
    //Extracting any kind of product record  in the product hierachy from an istream object
    std::istream& operator>>(std::istream& is, iProduct& iproduct){
        return iproduct.read(is);
    }
    
    //Caculating any kind of product cost in the product hierachy
    double operator+=(double& total, const iProduct& iproduct){
        return total += iproduct.total_cost();
    }
}

