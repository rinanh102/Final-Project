//
//  Date.cpp
//  Milestone1
//
//  Created by henry on 08/03/2019.
//  Copyright © 2019 HenryNguyen. All rights reserved.
//

#include "Date.hpp"
#include <iostream>
using namespace std;
namespace ama {
    
    void Date::status(int newStatus){
        this->statusNum = newStatus;
    }
    
    int Date::mdays(int year, int mon) const
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int month = mon >= 1 && mon <= 12 ? mon : 13;
        month--;
        return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    
    //Set an empty State
    void Date::setEmptyState(){
        this->year = 0;
        this->month = 0;
        this->day = 0;
    }
    bool Date::isValidDate(int year, int month, int day){
        int max_day = mdays(year, month);
        if (year > max_year || year < min_year){
            status(error_year);
            return false;
        } else if (month > 12 || month < 1){
            status(error_mon);
            return false;
        }else if (day < 1 || day > max_day){
            status(error_day);
            return false;
        }
        return true;
    }
//    bool Date::validateDate(int year, int month, int day){
//        int max_day = mdays(year, month);
//        if (year > max_year || year < min_year){
//            status(error_year);
//            return false;
//        } else if (month > 12 || month < 1){
//            status(error_mon);
//            return false;
//        }else if (day < 1 || day > max_day){
//            status(error_day);
//            return false;
//        }
//        return true;
//    }

    
    // Default Constructor
    Date::Date(){
        this->statusNum = no_error;
        setEmptyState();
    }
    //
    Date::Date( int year, int month, int day){
        int max_day = mdays(year, month);
        if (year > max_year || year < min_year){
            status(error_year);
            setEmptyState();
        } else if (month > 12 || month < 1){
            status(error_mon);
            setEmptyState();
        }else if (day < 1 || day > max_day){
            status(error_day);
            setEmptyState();
        } else {
            this->year = year;
            this->month = month;
            this->day = day;
            status(no_error);
        }
    }
    //
    int Date::status(){
        return this->statusNum;
    }
    //
    void Date::clearError(){
        status(no_error);
    }
    //MARK: valid date? and no_error
    bool Date::isGood(){
        if (status() == no_error && year <= max_year && year >= min_year && month <= 12 && month >= 1 && day >= 1 && day <= mdays(this->year, this->month) ){
            return true;
        } else {
            return false;
        }
    }
    //MARK: operator += -- true
    Date& Date::operator+=(int days){
        if (isGood()) {
            if ((day + days) > mdays(year, month) || (day +days) <= 0 ){
                status(error_invalid_operation);
            } else {
                day += days;
            }
        } else {
                status(error_invalid_operation);
            }
        return *this;
    }
    
    //MARK: operator ++ prefix -- true
    Date& Date::operator++(){
        if (isGood()) {
            if ((day + 1) > mdays(year, month) || (day + 1) <= 0 ){
                status(error_invalid_operation);
            } else {
                day += 1;
            }
        } else {
            status(error_invalid_operation);
        }
        return *this;
    }
        
    
    
    //MARK: operator ++ postfix --true
    Date Date::operator++(int){
        Date tmp;
//        = Date(this->year, this->month, this->day);
        tmp.year = this->year;
        tmp.month = this->month;
        tmp.day = this->day;
        if (isGood()) {
            if ((this->day + 1) > mdays(this->year, this->month) || (this->day + 1) <= 0 ) {
                status(error_invalid_operation);
            } else {
                this->day += 1;
            }
        } else {
                status(error_invalid_operation);
        }
        return tmp;
    }
    
    //MARK: operator + 
    Date& Date::operator+(int days){
        Date* tmp = new Date(this->year, this->month, this->day);
        *tmp += days;
        return *tmp;
    }
    bool Date::operator==(const Date& rhs){
        return (this->year == rhs.year && this->month == rhs.month && this->day == rhs.day) ? true : false;
    }
    
    bool Date::operator!=(const Date& rhs){
        return (this->year == rhs.year && this->month == rhs.month && this->day == rhs.day) ? false : true;
    }
    
    bool Date::operator<(const Date& rhs){
        if (this->year == rhs.year ){
            if (this->month == rhs.month) {
                if (this->day < rhs.day) {
                    return true;
                }
            } else if (this->month < rhs.month){
                return true;
            }
        } else if (this->year < rhs.year){
            return true;
        }
        return false;
    }
    
    bool Date::operator>(const Date& rhs){
        if (this->year == rhs.year ){
            if (this->month == rhs.month) {
                if (this->day > rhs.day) {
                    return true;
                }
            } else if (this->month > rhs.month){
                return true;
            }
        } else if (this->year > rhs.year){
            return true;
        }
        return false;
    }
    
    bool Date::operator>=(const Date& rhs){
        if (this->year >= rhs.year ){
            if (this->month >= rhs.month) {
                if (this->day >= rhs.day) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool Date::operator<=(const Date& rhs){
        if (this->year <= rhs.year ){
            if (this->month <= rhs.month) {
                if (this->day <= rhs.day) {
                    return true;
                }
            }
        }
        return false;
    }
    
    istream& Date::read(istream& in){
        char gap1,gap2;
        //fail
        in >> year >> gap1 >> month >> gap2 >> day;
        if (in.fail()){
            setEmptyState();
            status(error_input);
        } else {
            if (isValidDate(year, month, day)) {
                status(no_error);
            }else{
                setEmptyState();
            }
//            //success
//            Date(year, month, day);
        }
        return in;
    }
    ostream& Date::write(ostream& out) const{
        out.setf(std::ios::fixed);
        out.setf(std::ios::right);
        out.width(4);
        out.fill('0');
        out << year << '/';
        
        out.setf(std::ios::right);
        out.width(2);
        out.fill('0');
        out << month << '/';
        
        out.width(2);
        out.fill('0');
        out << day;
        
        out.fill(' ');
        out.unsetf(std::ios::fixed);
        
        return out;
    }
   istream &operator>>(istream &in, Date &date){
       return date.read(in);
//       return in;
    }
    
    ostream &operator<<(ostream &out,const Date &date){
       return date.write(out);
//        return out;
    }
}

