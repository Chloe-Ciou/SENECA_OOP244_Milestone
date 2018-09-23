/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/08/01
  **********************************************************/
#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include <iostream>
#include <fstream>
#include "ErrorState.h"
namespace AMA{
    const int max_sku_length = 7;
    const int max_unit_length = 10;
    const int max_name_length = 75;
    const double TAX_RATE = 0.13;
    
    class Product{
        char m_type;
        char m_sku[max_sku_length + 1];
        char m_unit[max_unit_length + 1];
        char* m_name;
        int m_c_quantity;
        int m_n_quantity;
        double m_price;
        bool m_taxed;
        ErrorState m_errorState;
    protected:
        void name(const char* name);
        const char* name() const;
        const char* sku() const;
        const char* unit() const;
        bool taxed() const;
        double price() const;
        double cost() const;
        void message(const char* errorMessage);
        bool isClear() const;
    public:
        Product(char type = 'N');
        Product(const char* sku, const char* name, const char* unit, int c_quantity = 0, bool taxed = true, double price = 0.0, int n_quantity = 0);
        Product(const Product& product);
        Product& operator=(const Product& product);
        virtual ~Product();
        std::fstream& store(std::fstream& file, bool newLine = true) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear) const;
        std::istream& read(std::istream& is);
        bool operator==(const char*) const;
        double total_cost() const;
        void quantity(int);
        bool isEmpty() const;
        int qtyNeeded() const;
        int quantity() const;
        bool operator>(const char*) const;
        bool operator>(const Product& product) const;
        int operator+=(int);
    };
    std::ostream& operator<<(std::ostream& os, const Product& product);
    std::istream& operator>>(std::istream& is, Product& product);
    double operator+=(double& total, const Product& product);
}
#endif
