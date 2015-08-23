#pragma once
#include <string>
#include <stdexcept>

class CircullarIndexString
{
public:
	//CircullarIndexString(const CircullarIndexString& rhs) = default;
	CircullarIndexString& operator=(const CircullarIndexString& rhs);
	CircullarIndexString(const std::string& str);
	CircullarIndexString(const std::string& str, size_t begin);

	std::string getString() const;
	size_t size() const;
	inline size_t& getBegin() { return begin; }
	char operator[](size_t index) const;
	bool operator==(const CircullarIndexString& rhs) const;
protected:
	std::string& str;
	const size_t strSize;
	size_t begin;
};
