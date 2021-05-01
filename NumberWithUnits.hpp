#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
using namespace std;
namespace ariel {
	class NumberWithUnits {	

		private:
			static double convert(const string& f1, const string& f2, double value);
       		static void casting(const string &f1, const string &f2);
			double number;
			string unit;	

		public:	
		
			double getNumber() const;
			string getUnit();
			static void read_units(ifstream& stream);
			NumberWithUnits(double, string const&);
			NumberWithUnits operator+(const NumberWithUnits& num);
			NumberWithUnits operator+();
			NumberWithUnits& operator +=(const NumberWithUnits& num);
			NumberWithUnits& operator++();    
			NumberWithUnits operator++(int); 
			NumberWithUnits operator-();
			NumberWithUnits operator--(int); 
			NumberWithUnits& operator--();    
			NumberWithUnits& operator -=(NumberWithUnits const& num);
			NumberWithUnits operator-(const NumberWithUnits& num);
			friend NumberWithUnits operator*(const double& f1,const NumberWithUnits& f2);
			friend NumberWithUnits operator*(const NumberWithUnits& f1,const double& f2);
			NumberWithUnits& operator*=(const double& num);
			bool operator <=(NumberWithUnits const& f1) const;
			bool operator >=(NumberWithUnits const& f1) const;
			bool operator>(const NumberWithUnits& number) const;
			bool operator <(NumberWithUnits const& number) const;
			bool operator ==(NumberWithUnits const& f1) const;
			bool operator !=(NumberWithUnits const& f1) const;
			friend ostream& operator<<(ostream& os, const NumberWithUnits& num);
			friend istream& operator>>(istream& is, NumberWithUnits& num);


	
	};
}

