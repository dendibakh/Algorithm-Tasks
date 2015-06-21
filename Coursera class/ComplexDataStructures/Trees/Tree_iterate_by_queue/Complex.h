#pragma once
#include <vector>
#include <iostream>
#include <string>

class Complex
{
public:
	Complex();
	Complex(double re);
	Complex(double re, double im);
	Complex (const Complex &c);
	std::string toString() const;

	Complex operator + (const Complex &c);
	Complex operator - (const Complex &c);
	Complex operator * (const Complex &c);
	Complex operator / (const Complex &c);

	double re() const { return re_; }
	double im() const { return im_; }
	double abs() const;
	Complex conj() const;

private:
	double re_;
	double im_;

};

bool operator ==(const Complex& left, const Complex& right);
bool operator !=(const Complex& left, const Complex& right);
bool operator >(const Complex& left, const Complex& right);
bool operator <(const Complex& left, const Complex& right);
bool operator <=(const Complex& left, const Complex& right);
bool operator >=(const Complex& left, const Complex& right);

std::istream& operator >>(std::istream& is, Complex& d);
std::ostream& operator <<(std::ostream& os, const Complex& d);

std::vector<Complex> Addition(std::vector<Complex> x, std::vector<Complex> y);