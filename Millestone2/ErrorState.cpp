/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/07/16
  **********************************************************/
#include <iostream>
#include <cstring>
#include "ErrorState.h"

namespace AMA{
    ErrorState::ErrorState(const char* errorMessage){
        m_message = nullptr;
        if(nullptr != errorMessage){
            message(errorMessage);
        }
    }
    
    ErrorState::~ErrorState(){
        delete m_message;
    }
    
    void ErrorState::clear(){
            delete m_message;
            m_message = nullptr;
    }
    bool ErrorState::isClear() const{
        return m_message == nullptr;
    }
    
    void ErrorState::message(const char* str){
        clear();
        if( nullptr != str){
            std::string strCopy = str;
            m_message = new char[strCopy.length() + 1];
            std::strcpy(m_message, strCopy.c_str());
        }
    }
    
    const char* ErrorState::message() const{
        return m_message;
    }
    
    std::ostream& operator<<(std::ostream& os, const ErrorState& error){
        if(!error.isClear())
            os << error.message();
        return os;
    }
}
