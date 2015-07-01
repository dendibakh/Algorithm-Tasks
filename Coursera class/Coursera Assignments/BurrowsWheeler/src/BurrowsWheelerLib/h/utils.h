#pragma once

#include <vector>

std::vector<bool> getBinaryRepresentation(char symbol);
char getSymbol(const std::vector<bool>& BinaryRepresentation);
char getSymbol(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end);
