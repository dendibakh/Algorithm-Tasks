#pragma once
#include <string>

class CircullarIndexString
{
public:
	//CircullarIndexString(const CircullarIndexString& rhs) = default;
	CircullarIndexString& operator=(const CircullarIndexString& rhs);
	CircullarIndexString(std::string& str);
	CircullarIndexString(std::string& str, size_t begin);

	std::string getString() const;
	size_t getBegin() const;
	char operator[](size_t index) const;
	bool operator==(const CircullarIndexString& rhs) const;
private:
	std::string* str;
	size_t begin;
};
