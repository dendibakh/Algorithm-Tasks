#pragma once
#include <string>

class IndexString
{
public:
	IndexString(const IndexString& rhs) = default;
	IndexString& operator=(const IndexString& rhs);
	IndexString(std::string& str);
	IndexString(std::string& str, size_t begin, size_t end);

	std::string getString() const;
	size_t getBegin() const;
	char operator[](size_t index) const;
	bool operator==(const IndexString& rhs) const;
private:
	std::string* str;
	size_t begin;
	size_t end;
};