#pragma once
#include <string>

class CircullarIndexString
{
        void validate() const;
public:
	//CircullarIndexString(const CircullarIndexString& rhs) = default;
	CircullarIndexString& operator=(const CircullarIndexString& rhs);
	CircullarIndexString(const std::string& str);
	CircullarIndexString(const std::string& str, size_t begin);

	std::string getString() const;
	size_t size() const;
	size_t getBegin() const;
	char operator[](size_t index) const;
	bool operator==(const CircullarIndexString& rhs) const;
protected:
	const std::string* str;
	size_t begin;
};
