#include<iostream>
#include<cmath>
using namespace std;
class Date{

private:
	int day;
	int month;
	int year;

public:
	Date();
	Date(int d, int m, int y);
	Date(const Date & x);
	~Date();
	int Day() const;
	int Month() const;
	int Year() const;
	int Period(Date x);
	void set_date(int d, int m, int y);
	Date & operator=(const Date & x);
	Date & operator+=(int x);
	Date & operator-=(int x);
	bool operator==(const Date & x) const;
	bool operator>(const Date & x) const;
	bool operator<=(const Date & x) const;
	bool operator!=(const Date & x) const;
	friend ostream & operator<<(ostream & os, const Date & x);
	friend istream & operator>>(istream &is, Date & x);
};

bool isV(int x){//Вычисляет, является ли год високосным.
	if (x%400==0)
		return true;
	if (x%4==0 && x%100!=0)
		return true;
	return false;
}

void Date::set_date(int d, int m, int y) {
	if (y<0)
		throw "Wrong year";
	if (m<1 || m>12)
		throw "Wrong month";
	int dim [] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (d<1)
		throw "Wrong day";
	if (isV(y) && m==2)
		if (d>dim[m]+1)
			throw "Wrong day";
	if (d>dim[m] && m!=2)
		throw "Wrong day";
	day = d;
	month = m;
	year = y;
	return;
}

Date::Date () {
	day = 1;
	month = 1;
	year = 0;
}

Date::Date (int d, int m, int y) {
	day = 1;
	month = 1;
	year = 0;
	try{
		set_date(d, m, y);
	}
	catch(const char * x){
		cout << "Exception: " << x << endl;
	}
}

Date::Date (const Date & x) {
	day = x.day;
	month = x.month;
	year = x.year;
}

Date::~Date () {
}

int Date::Day() const {
	return day;
}

int Date::Month() const {
	return month;
}

int Date::Year() const {
	return year;
}

int Date::Period(Date x) {
	int ans=0;
	Date a, b;
	if (year<x.year){
		a=x;
		b=*this;
	}
	if (year>x.year){
		a=*this;
		b=x;
	}
	if (year==x.year){
		if (month<x.month){
			a=x;
			b=*this;
		}
		if (month>x.month){
			a=*this;
			b=x;
		}
		if (month==x.month)
			return abs(day-x.day);
	}
	while((a.year!=b.year && a.month>=b.month) || (a.year-b.year!=1 && a.month<b.month)){
		if ((a.month>2 && isV(a.year)) || (a.month<=2 && isV(a.year-1)))
			ans+=366;
		else
			ans+=365;
		a.year--;
	}
	int dim [] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	while (a.month!=b.month){
		ans+=a.day;
		if (a.month==2 && isV(a.year))
			a.day=dim[a.month-1]+1;
		else
			a.day=dim[a.month-1];
		a.month--;
		if (a.month==0)
			a.month=12;
	}
	if (a.month==b.month)
		ans+=(a.day-b.day);
	return ans;
}

Date & Date::operator=(const Date & x) {
	day = x.day;
	month = x.month;
	year = x.year;
	return *this;
}

Date & Date::operator+=(int x) {
	int y=x;
	while (y>365){
		if ((month<=2 && isV(year)) || (month>2 && isV(year+1)))
			y-=366;
		else
			y-=365;
		year++;
	}
	int dim [] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	while (y!=0){
		int k;
		if (month==2 && isV(year))
			k=dim[month]+1;
		else
			k=dim[month];
		if (day+y>k){
			y-=(k-day+1);
			day=1;
			month++;
		}
		else{
			day+=y;
			y=0;
		}
		if (month==13){
			month=1;
			year++;
		}
	}
	return *this;
}

Date & Date::operator-=(int x) {
	int y=x;
	while (y>365){
		if ((month>2 && isV(year)) || (month<=2 && isV(year-1)))
			y-=366;
		else
			y-=365;
		year--;
	}
	int dim [] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	while (y!=0){
		int k;
		if (month==3 && isV(year))
			k=dim[month-1]+1;
		else
			k=dim[month-1];
		if (day-y>0){
			day-=y;
			y=0;
		}
		else{
			y-=day;
			day=k;
			month--;
		}
		if (month==0){
			month=12;
			year--;
		}
	}
	return *this;
}

bool Date::operator==(const Date & x) const {
	if (day==x.day && month==x.month && year==x.year)
		return true;
	return false;
}

bool Date::operator>(const Date & x) const {
	if (year>x.year)
		return true;
	if (year==x.year){
		if (month>x.month)
			return true;
		if (month<x.month)
			return false;
		if (month==x.month){
			if (day>x.day)
				return true;
			else
				return false;
		}
	}
	return false;
}

bool Date::operator<=(const Date & x) const {
	if (year<x.year)
		return true;
	if (year==x.year){
		if (month<x.month)
			return true;
		if (month>x.month)
			return false;
		if (month==x.month){
			if (day<=x.day)
				return true;
			else
				return false;
		}
	}
	return false;
}

bool Date::operator!=(const Date & x) const {
	if(day!=x.day || month!=x.month || year!=x.year)
		return true;
	return false;
}

ostream & operator<<(ostream & os, const Date & x) {
	os << x.day << "." << x.month << "." << x.year;
	return os;
}

istream & operator>>(istream & is, Date & x) {
	int d, m, y;
	is >> d >> m >> y;
	try{
		x.set_date(d, m, y);
	}
	catch(const char * x){
		cout << "Exception: " << x << endl;
	}
	return is;
}

int main() {
	int x;
	Date a, b;
	Date c(32, 2, 1992);
	cout << c << endl;
	Date d(29, 2, 2000);
	cout << d << endl;
	cout<<"Vvedite datu a\n";
	cin>>a;
	cout<<"Vvedite datu b\n";
	cin>>b;
	cout<<"Vvedite x\n";
	cin>>x;
	a+=x;
	cout<<"a+=x:\n";
	cout << a << endl;
	a-=x;
	cout<<"a-=x:\n";
	cout << a << endl;
	cout<<"a:\n";
	cout << a << endl;
	cout<<"b:\n";
	cout << b << endl;
	int t = b.Period(a);
	cout<<"Period:\n";
	cout << t << endl;
	return 0;
}
