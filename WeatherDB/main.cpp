//
//  main.cpp
//  WeatherDB
//
//  Created by Sumite Ramchande on 26/01/2017.
//  Copyright © 2017 Sumite Ramchande. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <iomanip>


using namespace std;

class WeatherDB{
protected:
    int d,m,year;
    float htemp, ltemp;
    int humidity;
 
    
public:
    bool single_m = false;
    bool single_d = false;
    bool s_fields = true;
    bool duplicate = false;
    string str;
//constructor
    
public:
    WeatherDB(const int d){}
    WeatherDB(const int d, const int m, const int year, const float htemp, const float ltemp, const int humidity):
    d(d),
    m(m),
    year(year),
    htemp(htemp),
    ltemp(ltemp),
    humidity(humidity)
    {}

    float calculateMean(){return (htemp+ltemp)/2;}
    // can be usaed for search too
    void check_duplicate(){
        check_zero();
        ifstream reader("Database.txt");
    
        while (getline(reader, str)) {
            // output the line
            string a = str.substr(0,4);
            string c = to_string(d);
            string m1 = to_string(m);
            //cout << a << " " << c << " " << m1 << endl;
            if (single_d && single_m && (a[0] == c[0]) && (a[1]==c[1]) && (a[2]==m1[0]) && (a[3]==m1[1])){cout << "1.Data in" << a << " " << c << " " << m1 << endl;duplicate = true;break;}// if both with 00 us
            // month is with 0 use x
            else if (s_fields && single_d && (a[0] == c[0]) && (a[1]==c[1]) && (a[3]==m1[0])){cout << "2.Data existent" << endl;duplicate = true; break;} // day is with 0 use x
            else if (s_fields && single_m && (a[1] == c[0]) && (a[2]==m1[0]) && (a[3]==m1[1])){cout << "3.Data in" << endl;duplicate = true;break;}
            else if (s_fields && (single_d == false) && (single_m==false) && (a[1]==c[0]) && (a[3]==m1[0])) {cout << "4.Error : Data already exists!" << endl;duplicate = true;break;}
            //cout << typeid(find).name() << typeid(a).name() << endl;
            
           
        }
    }
    
    int check_zero(){
        if (d>9 & m>9){return single_d = true,single_m = true,s_fields = false;}
        else if (m>9){return single_m = true;}
        else if (d>9){return single_d = true;}
        //cout << single_m << endl;
        //cout << single_d << endl;
        return 0;
    }
    // before input, check for duplicate data
        // if duplicate exists, give error
    int input_data(){
        check_duplicate();
        ofstream writer("Database.txt",ios::in | ios::out | ios::ate | ios::app);
        if(!writer){
            cout << "Error, file not found" << endl;
            return -1;
        }else{ //case statement required to check 0 in days and months
            cout << "Inputting data..." << endl;
            if (duplicate){cout << "Error, data exists" << endl;}
            else{
            if (d<9 && m<9 ){writer << 0 << d << 0 << m << year << htemp << ltemp << humidity << endl;} // add 0 if less than 9
            else if (m<9) {writer  << d << 0 << m << year << htemp << ltemp << humidity << endl;}
            else if (d<9) {writer  << 0 << d << m << year << htemp << ltemp << humidity << endl;}
            else{writer << d << m << year << htemp << ltemp << humidity << endl;} // else continues normally
            writer.close();
            }
        }
        
        return 0;
    }
    // read data from input
    // pointers will get data from check_duplicate if duplicate is found
    int read_data(const int &day, const int &month){
        m = month;
        d = day;
        check_duplicate();
        if (duplicate) {cout << str <<  endl;}
        else{cout << "Not existent"<< endl;}
        return 0 ;
}

// menu will contain
    // Input Data
        // Read data
            // Modify Data
                // Get mean
}; // end of class

void menu(){}

int main() {
 
    cout << "*******************************" << endl;
    cout << "1 - Input data" << endl;
    cout << "2 - Read data" << endl;
    cout << "3 - Calculate mean" << endl;
    cout << "Choose an option: ";
    
    int choice;
    int d,m,y,h;
    float lt,ht;

    cin >> choice ;
    
    
    
    switch (choice) {
        case 1:
            cout << "Day ";
            cin >> d;
            cout << "Month ";
            cin >> m;
            cout << "Year ";
            cin >> y;
            cout << "Low Temp ";
            cin>>lt;
            cout << "High Temp ";
            cin>>ht;
            cout << "Humidity ";
            cin>>h;
            WeatherDB day(d,m,y,lt,ht,h);
            day.input_data();
            break;
    }
    
    
  
    return 0;
}
    


// Advanced features

// Automated data missing detector
    // If a day is missed, randomly generate htemp,ltemp,humidity...
    // place on the txt file
// Intelligent day detector
    // Knows for which day the data is missing




