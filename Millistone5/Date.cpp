/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/08/06
  **********************************************************/

#include <iostream>
#include <iomanip>
#include "Date.h"

namespace AMA {
    //** Private member functions of Date class **
    
    //number of days in month mon_ and year year_
    int Date::mdays(int mon, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int month = mon >= 1 && mon <= 12 ? mon : 13;
        month--;
        return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    
    //Seting the error code
    void Date::errCode(int errorCode){
        switch(errorCode){
            case 0:
                m_error = NO_ERROR;
                break;
            case 1:
                m_error = CIN_FAILED;
                break;
            case 2:
                m_error = YEAR_ERROR;
                break;
            case 3:
                m_error = MON_ERROR;
                break;
            case 4:
                m_error = DAY_ERROR;
                break;
            default:
                break;
        }
    }
    
    //** Public member functions of Date class **
    
    //Default constructor
    Date::Date(){
        m_year = 0;
        m_month = 0;
        m_day = 0;
        m_error = NO_ERROR;
        m_comp = 0;
    }
    
    //Three parameters constructor
    Date::Date(int year, int month, int day){
        bool valid = true;
        int error = NO_ERROR;
        if(year > max_year || year < min_year){
            valid = false;
            error = YEAR_ERROR;
        }
        
        if (valid && (month < 1 || month > 12)) {
            valid = false;
            error = MON_ERROR;
        }
        
        if(valid && (day < 1 || day > mdays(month, year))){
            valid = false;
            error = DAY_ERROR;
        }
        if(valid){
            m_year = year;
            m_month = month;
            m_day = day;
            m_error = NO_ERROR;
            m_comp = m_year * 372 + m_month * 13 + day;
        }else{
            *this = Date();
            this->errCode(error);
        }
    }
    
    //Checking empty status of two Date objects
    bool Date::noEmpty(const Date& rhs)const{
        return m_year != 0 && rhs.m_year != 0;
    }
    
    //Comparing two Date objects
    bool Date::operator==(const Date& rhs) const{
        return noEmpty(rhs) && m_comp == rhs.m_comp;
    }
    
    bool Date::operator!=(const Date& rhs) const{
        return noEmpty(rhs) && m_comp != rhs.m_comp;
    }
    
    bool Date::operator<(const Date& rhs) const{
        return noEmpty(rhs) && m_comp < rhs.m_comp;
    }
    bool Date::operator>(const Date& rhs) const{
        return noEmpty(rhs) && m_comp > rhs.m_comp;
    }
    bool Date::operator<=(const Date& rhs) const{
        return noEmpty(rhs) && m_comp <= rhs.m_comp;
    }
    bool Date::operator>=(const Date& rhs) const{
        return noEmpty(rhs) && m_comp >= rhs.m_comp;
    }
    
    //Returning error code
    int Date::errCode() const{
        return m_error;
    }
    
    //Returning true if error state is not NO_ERROR
    bool Date::bad() const{
        return errCode();
    }
    
    //Extracting a Date data from an istream object into a Date object
    std::istream& Date::read(std::istream& istr){
        int year, month, day;
        istr >> year;
        if(istr.fail()){
            errCode(CIN_FAILED);
        }else{
            istr.ignore();
            istr >> month;
            if(istr.fail()){
                errCode(CIN_FAILED);
            }else{
                istr.ignore();
                istr >> day;
                if(istr.fail()){
                    errCode(CIN_FAILED);
                }else{
                    Date temp = Date(year, month, day);
                    if(temp.bad()){
                        this->m_error = temp.m_error;
                    }else
                        *this = temp;
                }
            }
        }
        return istr;
    }
    
    //Inserting a Date data into an ostream object
    std::ostream& Date::write(std::ostream& ostr) const{
        ostr << std::setfill('0') << m_year << "/";
        ostr << std::setw(2) << m_month << "/" << std::setw(2) << m_day << std::setfill(' ');
        return ostr;
    }
    
    //** Helper functions of Date class **
    
    //Inserting a Date data into an ostream object
    std::ostream& operator<<(std::ostream& ostr, const Date& date){
        date.write(ostr);
        return ostr;
    }
    
    //Extrating a Date data from an istream object
    std::istream& operator>>(std::istream& istr, Date& date){
        date.read(istr);
        return istr;
    }
}

