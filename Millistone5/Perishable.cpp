/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/08/06
  **********************************************************/
#include "Perishable.h"
namespace AMA{
    //** Public member functions of Perishable class **
    
    //No argument constructor
    Perishable::Perishable(): AMA::Product('P'){
        m_expiryDate = Date();
    }
    
    //Inserting a single perishable product data into a file object
    std::fstream& Perishable::store(std::fstream& file, bool newLine) const{
        Product::store(file, false);
        file << ',' << m_expiryDate;
        if(newLine) file << '\n';
        return file;
    }
    
    //Extracting a single product data from a file object into a perishable product
    std::fstream& Perishable::load(std::fstream& file){
        Product::load(file);
        file.ignore();
        m_expiryDate.read(file);
        file.ignore();
        return file;
    }
    
    //Inserting a sigle perishable product data into a ostream object
    std::ostream& Perishable::write(std::ostream& os, bool linear) const{
        Product::write(os, linear);
        if(!Product::isEmpty() && Product::isClear()){
            if(!linear) os << std::endl << " Expiry date: ";
            m_expiryDate.write(os);
        }
        return os;
    }
    
    //Extrating a single perishable product data from an istream object and store it into a perishable product object
    std::istream& Perishable::read(std::istream& is){
        Product::read(is);
        if(!Product::isEmpty()){
            std::cout << " Expiry date (YYYY/MM/DD): ";
            Date temp;
            temp.read(is);
            if(temp.bad()){
                switch (temp.errCode()) {
                    case CIN_FAILED:
                        message("Invalid Date Entry");
                        break;
                    case YEAR_ERROR:
                        message("Invalid Year in Date Entry");
                        break;
                    case MON_ERROR:
                        message("Invalid Month in Date Entry");
                        break;
                    case DAY_ERROR:
                        message("Invalid Day in Date Entry");
                        break;
                    default:
                        break;
                }
                is.setstate(std::ios::failbit);
            }else{
                this->m_expiryDate = temp;
            }
        }
        return is;
    }
    
    //Returning the expiry date of a perishable product
    const Date& Perishable::expiry() const{
        return m_expiryDate;
    }
}
