#include "CircullarIndexString.h"
#include <stdexcept>

CircullarIndexString::CircullarIndexString(const std::string& str) : str(const_cast<std::string*>(&str)), begin(0)
{

}

CircullarIndexString::CircullarIndexString(const std::string& str, size_t begin) : str(const_cast<std::string*>(&str)), begin(begin)
{

}

CircullarIndexString& CircullarIndexString::operator = (const CircullarIndexString& rhs)
{
	this->begin = rhs.begin;
	this->str = rhs.str;
	return *this;
}

std::string CircullarIndexString::getString() const
{
	validate();
	return std::string(str->substr(begin, str->size() - begin) + str->substr(0, begin));
}

size_t CircullarIndexString::getBegin() const
{
	return begin;
}

char CircullarIndexString::operator[](size_t index) const
{
        validate();
	return (*str)[(index + begin) % str->size()]; // this is circullarity
}

bool CircullarIndexString::operator==(const CircullarIndexString& rhs) const
{
	std::string myStr = this->getString();
	std::string rhsStr = rhs.getString();
	return myStr.size() == rhsStr.size() && std::equal(myStr.begin(), myStr.end(), rhsStr.begin());
}

void CircullarIndexString::validate() const
{
        if (!str)
             throw std::runtime_error("Pointer to string is not valid.");
}
