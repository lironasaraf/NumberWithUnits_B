#include "NumberWithUnits.hpp"
namespace ariel {
	const double EPS = 0.001;
	static map<string,map<string, double>> units;

	NumberWithUnits::NumberWithUnits(double num, string const& Input){
        if (units.find(Input) == units.end())
        {
            throw "Error unit try againg";
        }
			this->number = num;
           	this->unit = Input;    
    }

	 void NumberWithUnits::casting(const string &f1, const string &f2)
    {
        for (auto &cas : units[f1])
        {
            double cast = units[f2][f1] * cas.second;
            units[f2][cas.first] = cast;
            units[cas.first][f2] = 1 / cast;
        }
		for (auto &cas : units[f2])
        {
            double cast = units[f1][f2] * cas.second;
            units[f1][cas.first] = cast;
            units[cas.first][f1] = 1 / cast;
        }
    }
    	double NumberWithUnits::convert(const string& u1, const string& u2, double value)
    {
        if (u1 == u2)
        {
            return value;
        }

        if (units[u2].find(u1) == units[u2].end())
        {
            throw "different type of unit";
        }
        return (value * units[u2][u1]); 
    }

	void NumberWithUnits::read_units(ifstream& stream)
	{
        	if (!stream) {
		    cout << "No such file";
	    }
        double d1;
        double d2;
        string s1;
        string s2; 
        string equal;
        while (!stream.eof())
        {
            stream >> d1 >> s1 >> equal >> d2 >> s2;
            units[s1][s2] = d2;
            units[s2][s1] = d1 / d2;
            casting(s1, s2);
        }
    }

    double NumberWithUnits::getNumber() const{
		return this->number;
	}

	string NumberWithUnits::getUnit(){
		return this->unit;
	}

    ///////////////////operators

	 NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num)
    {
        double add = NumberWithUnits::convert(this->unit, num.unit, num.number);
        double sum = this->number + add;
        return NumberWithUnits(sum, this->unit);
    }
        ostream &operator<<(ostream& os, const NumberWithUnits& num)
    {
        os << num.number << "[" << num.unit << "]";
        return os;
    }
	
    istream &operator>>(istream& in, NumberWithUnits& num)
    {
        char c = '\0';
        double numInput = 0;
        string  unitIn; 
        in >> numInput >> c;
        while(c != ']')
        {
            if(c != '[')
            {
                unitIn.insert( unitIn.end(), c);
            }
            
            in >> c;
        }
        if (units.count( unitIn) > 0)
        {
            num.number =  numInput;
            num.unit =  unitIn;
        }
        else
        
            throw "Invalid unit!!";
        
        return in;
    }


    NumberWithUnits NumberWithUnits::operator+()
    {
		NumberWithUnits num(+(this->number), this->unit);
        return num;
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        ++(this->number);
        return *this;
    }
	
    NumberWithUnits NumberWithUnits::operator++(int)
    {
		NumberWithUnits num(this->number, this->unit);
        ++(this->number);
        return num;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num)
    {
        double f1 = NumberWithUnits::convert(this->unit, num.unit, num.number);
        double ans = this->number - f1;
        return NumberWithUnits(ans, this->unit);
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &number)
    {
      return  *this = *this - number;
       
    }

    NumberWithUnits NumberWithUnits::operator-()
    {
	return NumberWithUnits (-(this->number), this->unit);
        
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
        --(this->number);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int)
    {
		NumberWithUnits ans(this->number, this->unit);
        --(this->number);
        return ans;
    }

    NumberWithUnits operator*(const double& f1,const NumberWithUnits& f2)
    {
        return NumberWithUnits(f1 * f2.number, f2.unit);
    }

    NumberWithUnits operator*(const NumberWithUnits& f2,const double& f1)
    {
        return NumberWithUnits(f1 * f2.number, f2.unit);
    }


    bool NumberWithUnits::operator<(const NumberWithUnits &num) const
    {
        double ans = NumberWithUnits::convert(this->unit, num.unit, num.number);
		return (ans - this->number) > EPS;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &f1) const
    {
        double ans = NumberWithUnits::convert(this->unit, f1.unit, f1.number);
        if (abs(ans - this->number) <= EPS) 
        {
            return true;
        }
        else 
			return (ans- this->number) > EPS;
    }
	    bool NumberWithUnits::operator>=(const NumberWithUnits &num) const
    {
        double ans = NumberWithUnits::convert(this->unit, num.unit, num.number);
        if (abs(ans - this->number) <= EPS)
        {
            return true;
        }
        else
			return (this->number - ans) > EPS;
    }
    bool NumberWithUnits::operator>(const NumberWithUnits &f2) const
    {
        double ans = NumberWithUnits::convert(this->unit, f2.unit, f2.number);
		return(this->number- ans) > EPS;
    }


    bool NumberWithUnits::operator==(const NumberWithUnits &f1) const
    {
		double ans = NumberWithUnits::convert(this->unit, f1.unit, f1.number);
        return abs(ans - this->number) <= EPS;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &f1) const
    {
		double ans = NumberWithUnits::convert(this->unit, f1.unit, f1.number);
    	return abs(this->number - ans) > EPS;
    }
        NumberWithUnits &NumberWithUnits::operator*=(const double &number)
    {
        this->number *= number;
        return *this;
    }
        NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num)
    {
        return *this = *this + num;
    }



}