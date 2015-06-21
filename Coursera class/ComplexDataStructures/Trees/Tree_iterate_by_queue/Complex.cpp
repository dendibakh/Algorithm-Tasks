#include "Complex.h"
#include <sstream>
#include "math.h"

Complex::Complex() : re_(0), im_(0) { }

Complex::Complex(double re):
re_(re),
im_(0)
{}

Complex::Complex(double re, double im):
re_(re),
im_(im)
{}

Complex::Complex (const Complex &c):
re_(c.re()), 
im_(c.im())
{}

std::string Complex::toString() const
{
	std::stringstream s;
	if (im_==0)
		s << re_;
	else if (re_==0)
		s << im_ << "i";
	else
		s << re_ << ((im_>=0) ? "+" : "-") << fabs(im_) << "i";
	return s.str();
}

Complex Complex::operator +(const Complex &c)
{
	return Complex (re_ + c.re(), im_ + c.im());
}

Complex Complex::operator -(const Complex &c)       
{
	return Complex(re_ - c.re(), im_ - c.im());
}

Complex Complex::operator * (const Complex &c)         
{
	double real=re_ * c.re() - im_ * c.im();
	double image=re_ * c.im() + im_ * c.re();
	return Complex(real, image); 
}

Complex Complex::operator / (const Complex &c)           
{
	double r = c.re() * c.re() + c.im() * c.im();
	if (r==0)
		throw std::runtime_error("Деление на нуль");
	else
		return Complex(((re_ * c.re() + im_ * c.im()) / r), ((im_ * c.re() - re_ * c.im()) / r));
}

double Complex::abs() const
{
	return sqrt(re_*re_ + im_*im_);
}

Complex Complex::conj() const
{
	return Complex(re_, -1*im_ );
}

bool operator ==(const Complex& left, const Complex& right){
	return left.re() == right.re() &&
		left.im() == right.im();
}

bool operator !=(const Complex& left, const Complex& right)
{
	return !(left == right);
}

bool operator >(const Complex& left, const Complex& right){
	return left.abs() > right.abs();
}

bool operator <(const Complex& left, const Complex& right){
	return left.abs() < right.abs();;
}

bool operator >=(const Complex& left, const Complex& right){
	return left.abs() >= right.abs();;
}

bool operator <=(const Complex& left, const Complex& right){
	return left.abs() <= right.abs();;
}

std::istream& operator >>(std::istream& is, Complex& d)     
{
	double re=0, im=0;
	is >> re >> im;
	d = Complex(re, im);
	return is;
}

std::ostream& operator <<(std::ostream& os, const Complex& d)
{
	os << d.toString();
	return os;

}

std::vector<Complex> Addition(std::vector<Complex> a, std::vector<Complex> b)
{
	std::vector<Complex> result;
	if(a.size()>b.size())
		for(int i=(int)b.size(); i<(int)a.size(); i++)
			b.push_back(Complex(0));
	else
		for(int i=(int)a.size(); i<(int)b.size(); i++)
			a.push_back(Complex(0));
	for(int i=0; i<(int)a.size(); i++)
	{
		result.push_back(a[i]+b[i]);
	}
	return result;
}
