//
//  Date.hpp
//  Milestone1
//
//  Created by henry on 08/03/2019.
//  Copyright © 2019 HenryNguyen. All rights reserved.
//

#ifndef Date_hpp
#define Date_hpp
#include <iostream>
using namespace std;

namespace ama {
    const int min_year = 2019;
    const int max_year = 2028;
    const int no_error = 0;
    const int error_year = 1;
    const int error_mon = 2;
    const int error_day = 3;
    const int error_invalid_operation = 4;
    const int error_input = 5;
    class Date{
        int year;
        int month;
        int day;
        int statusNum;
        void status(int newStauts);// not completed
        int mdays(int year, int month) const;
    public:
        void setEmptyState();
        bool isValidDate(int year, int month, int day);
//        bool validateDate(int year, int month, int day);
        Date(); // default Constructor
        Date( int year, int month, int day);// custom Constructor
        int status();
        void clearError();
        bool isGood();
        Date& operator+=(int days);
        Date& operator++();
        Date operator++(int);// not completed
        Date& operator+(int days); // not completed
        bool operator==(const Date& rhs);
        bool operator!=(const Date& rhs);
        bool operator<(const Date& rhs);
        bool operator>(const Date& rhs);
        bool operator<=(const Date& rhs);
        bool operator>=(const Date& rhs);
        istream& read(istream& in);
        ostream& write(ostream& out) const;
    };
    istream &operator>>(istream&, Date &);
    ostream &operator<<(ostream&,const Date &);
}
#endif /* Date_hpp */
