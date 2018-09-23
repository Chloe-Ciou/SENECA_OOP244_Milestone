/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/08/06
  **********************************************************/
#include <iostream>
#include <cstring>
#include "ErrorState.h"

namespace AMA{
    //** public member functions of Errorstate class **
    
    //Seting errorstate
    ErrorState::ErrorState(const char* errorMessage){
        m_message = nullptr;
        if(nullptr != errorMessage){
            message(errorMessage);
        }
    }
    
    //Destructor
    ErrorState::~ErrorState(){
        delete m_message;
    }
    
    //Cleaning errorstate
    void ErrorState::clear(){
        delete m_message;
        m_message = nullptr;
    }
    
    //Checking errorstate
    bool ErrorState::isClear() const{
        return m_message == nullptr;
    }
    
    //Reseting errorstate
    void ErrorState::message(const char* str){
        clear();
        if( nullptr != str){
            std::string strCopy = str;
            m_message = new char[strCopy.length() + 1];
            std::strcpy(m_message, strCopy.c_str());
        }
    }
    
    //Returning the error message
    const char* ErrorState::message() const{
        return m_message;
    }
    
    //** Heloper function of the Errorstate class **
    
    //Inserting the error message to an ostream object
    std::ostream& operator<<(std::ostream& os, const ErrorState& error){
        if(!error.isClear())
            os << error.message();
        return os;
    }
}

