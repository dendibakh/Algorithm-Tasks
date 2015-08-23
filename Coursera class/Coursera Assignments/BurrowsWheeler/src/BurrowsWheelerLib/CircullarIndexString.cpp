#include "CircullarIndexString.h"

CircullarIndexString::CircullarIndexString(const std::string& str) : str(const_cast<std::string&>(str)), strSize(str.size()), begin(0)
{

}

CircullarIndexString::CircullarIndexString(const std::string& str, size_t begin) : str(const_cast<std::string&>(str)), strSize(str.size()), begin(begin)
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
	return std::string(str.substr(begin, strSize - begin) + str.substr(0, begin));
}

size_t CircullarIndexString::size() const
{
        return strSize;
}

char CircullarIndexString::operator[](size_t index) const
{
	return str.at((index + begin) % strSize); // this is circullarity
}

bool CircullarIndexString::operator==(const CircullarIndexString& rhs) const
{
	std::string myStr = this->getString();
	std::string rhsStr = rhs.getString();
	return myStr.size() == rhsStr.size() && std::equal(myStr.begin(), myStr.end(), rhsStr.begin());
}
