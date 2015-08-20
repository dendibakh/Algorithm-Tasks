#pragma once

#include <vector>
#include <string>

std::vector<bool> getBinaryRepresentation(char symbol);
char getSymbol(const std::vector<bool>& BinaryRepresentation);
char getSymbol(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end);

std::vector<bool> getBinaryRepresentation(size_t value);
size_t getValue(const std::vector<bool>& BinaryRepresentation);
size_t getValue(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end);

std::string readFile(const std::string& fileName);
