#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include <string>
using namespace std;

class Rational {
public:
	int numer;// Числитель
	int denom;// Знаменатель (>=1)
			  //конструкторы
	Rational() {
		numer = 0;
		denom = 1;
	}

	Rational(int n) {
		numer = n;
		denom = 1;
	}

	Rational(int n, int d) {
		numer = n;
		denom = d;
	}
	//ПЕРЕГРУЗКА ОПЕРАТОРОВ
	Rational& operator =(const Rational& r) {
		numer = r.numer;
		denom = r.denom;
		return *this;
	}
	//оператор добавления
	Rational& operator +=(const Rational& r) {
		numer = (numer*r.denom + denom*r.numer);
		denom = denom*r.denom;
		simplify();
		return *this;
	}
	//оператор сложения
	Rational operator +(const Rational& r) const {
		Rational res(*this);
		return res += r;
	}
	//опереатор отрицания/ унарный минус
	Rational operator -() const {
		Rational r(-numer, denom);
		return r;
	}
	//опереатор уменьшения
	Rational& operator -=(const Rational& r) {
		return (*this += (-r));
	}
	Rational& operator -(const Rational& r) {
		return *this -= r;
	}
	//опереатор умнoжения
	Rational operator *=(const Rational& r) {
		numer = numer*r.numer;
		denom = denom*r.denom;
		simplify();
		return *this;
	}
	Rational& operator *(const Rational& r) {
		Rational res(*this);
		return res *= r;
	}
	//опереатор деления
	Rational operator /=(const Rational& r) {
		numer = numer*r.denom;
		denom = denom*r.numer;
		simplify();
		return *this;
	}
	Rational& operator /(const Rational& r) {
		Rational res(*this);
		return res /= r;
	}

	//Операторы инкремента
	Rational operator ++() {//префиксный
		numer += denom;
		return *this;
	}
	Rational operator ++(int) {//постфиксный
		Rational r(*this);
		numer += denom;
		return r;
	}
	Rational operator --() {//префиксный
		numer -= denom;
		return *this;
	}
	Rational operator --(int) {//постфиксный
		Rational r(*this);
		numer -= denom;
		return r;
	}

	//ОПЕРАТОРЫ СРАВНЕНИЯ
	bool operator ==(const Rational& r) const {
		return (numer == r.numer) && (denom == r.denom);
	}
	bool operator !=(const Rational& r) const {
		return !(*this == r);
	}
	bool operator >(const Rational& r) const {
		return (numer*r.denom > r.numer*denom);
	}
	bool operator <(const Rational& r) const {
		return (numer*r.denom < r.numer*denom);
	}
	bool operator >=(const Rational& r) const {
		return (numer*r.denom >= r.numer*denom);
	}
	bool operator <=(const Rational& r) const {
		return (numer*r.denom <= r.numer*denom);
	}



	//ОПЕРАТОРЫ ПРЕОБРОЗОВАНИЯ ТИПОВ
	operator int() const {
		return numer / denom;
	}
	operator double() const {
		return ((double)numer) / denom;
	}
	/*operator float() const {
		return ((float)numer) / denom;
	}*/

	Rational (double d){
		const int e = 100000;
		numer = floor(d);
		denom = floor((d - numer)* e);
		numer *= e;
		numer += denom;
		denom = e;
		simplify();
	}
	
	//ОПЕРАТОРЫ ВВОДА/ВЫВОДА
	friend istream& operator >>(istream& in, Rational& r) {
		in >> r.numer >> r.denom;
		return in;
	}
	friend ostream& operator <<(ostream& out, const Rational& r) {
		out << r.numer << "/" << r.denom;
		return out;
	}

	/*Rational pow(Rational& r, int step) {
		int n = r.numer, d = r.denom;
		for (int i = 0; i < step-1; i++)
		{
			r.numer *= n;
			r.denom *= d;
		}
		return r;
	}*/

	//решение квадратного уравнения
	int korni(double a, double b, double c) {
		Rational x[2], D;
		D = Rational(pow(b,2)- 4*a*c);
		cout << "Дискриминант = " << double(D) << endl;
		D = sqr(D, 2);
		if (D > Rational(0)) {
			x[0] = (Rational (-b) + D) / Rational(2*a);
			x[1] = (Rational(-b) - D) / Rational(2 * a);
			cout << "Найдено два корня: " << endl;
			cout << "x1 = " << double(x[0]) << endl;
			cout << "x2 = " << double(x[1]) << endl;
		};
		if (D == Rational(0)) {
			x[0] = Rational(-b)/ Rational(2 * a);
			cout << "Найден один корень: " << endl;
			cout << "x1 = " << double(x[0]) << endl;
		}
		if (D < Rational(0))
			cout << "Дискриминант < 0, не существует действительных корней " << endl;
		return 0;
	}


private:
	//упрощение/сокращение
	void simplify() {
		if (denom < 0) {
			numer = -numer;
			denom = -denom;
		}
		for (int i = 2; i <= abs(denom) && i <= abs(numer); i++)
			if (numer%i == 0 && denom%i == 0) {
				numer /= i;
				denom /= i;
				i--;
			}
	}

	//к0рёнь. метод градиентного спуска
	Rational sqr(Rational& o, int step) {
		double r = double(o);
		double x[25];//точность
		double c, xi;
		x[0] = r;
		for (int i = 0; i < 24; i++)
		{
			xi = x[i];
			x[i + 1] = pow(xi, step - 1);
			x[i + 1] = r / x[i + 1];
			c = x[i] * (step - 1);
			x[i + 1] += c;
			x[i + 1] /= step;
		}

		return Rational(x[24]);
	}
};

double prov(string s) {
	int k = 0;//k-счётчик т0чёк
	for (int i = 0; i < s.size(); i++){
		if (s[i] == ',') k++;
		if (s[i] == '.') {
			s[i] = ',';
			k++;
		}
		if (k > 1) throw exception();
		if (!(isdigit(s[i]) || s[i] == ',')) throw exception();
	}
	return stod(s.c_str());
}
int main()
{
	setlocale(LC_ALL, "rus");
	string s;
	double a, b, c;
	try
	{
		cout << "ax^2+bx+c=0" << endl << "Введите a<>0, b, c" << endl << "a = "; cin >> s;
		a = prov(s);
		if (a == 0) throw exception();
		cout << "b = "; cin >> s; b = prov(s);
		cout << "c = "; cin >> s; c = prov(s);
	}
	catch (const exception&)
	{
		cout << "Error!!!";
	}
	cout <<(new Rational())->korni(a,b,c);
	_getch();
	return 0;
}
