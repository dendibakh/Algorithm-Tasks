#include "IndexString.h"

IndexString::IndexString(std::string& str) : str(&str), begin(0), end(str.size())
{

}

IndexString::IndexString(std::string& str, size_t begin, size_t end) : str(&str), begin(begin), end(end)
{

}

IndexString& IndexString::operator = (const IndexString& rhs)
{
	this->begin = rhs.begin;
	this->end = rhs.end;
	this->str = rhs.str;
	return *this;
}

std::string IndexString::getString() const
{
	return std::string(str->substr(begin, end - begin));
}

size_t IndexString::getBegin() const
{
	return begin;
}

char IndexString::operator[](size_t index) const
{
	return (*str)[index + begin];
}

bool IndexString::operator==(const IndexString& rhs) const
{
	std::string myStr = this->getString();
	std::string rhsStr = rhs.getString();
	return myStr.size() == rhsStr.size() && std::equal(myStr.begin(), myStr.end(), rhsStr.begin());
}
