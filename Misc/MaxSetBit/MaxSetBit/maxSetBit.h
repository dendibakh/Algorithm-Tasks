#pragma once

#include <vector>

const size_t bitsInByte = 8;

template <class T>
std::vector<bool> binaryRepresentation(T number)
{
	std::vector<bool> bin(sizeof(T) * bitsInByte, 0);
	for (int i = sizeof(T) * bitsInByte - 1; i >= 0; i--) 
	{
		T bound = static_cast<T>(pow(double(2), i));
		if (number >= bound) 
		{
			bin[i] = 1;
			T d = number / bound;
           	number -= d * bound;
		} 
	}
	return bin;
}

namespace CastToBinary
{
	template <class T>
	size_t findLeftMostSetBit(T number)
	{
		if (number == 0)
			return -1;
		std::vector<bool> bin = binaryRepresentation(number);
		for (auto i = bin.rbegin(); i != bin.rend(); i++)
		{
			if (*i)
				return bin.size() - (i - bin.rbegin() + 1);
		}
		return -1;
	}
}

namespace PutMask
{
	template <class T>
	size_t findLeftMostSetBit(T number)
	{
		if (number == 0)
			return -1;
		for (int i = sizeof(T) * bitsInByte; i >= 0; i--) 
		{
			T mask = static_cast<T>(pow(double(2), i));
			if (number & mask)
				return i;
		}
		return -1;
	}
}

namespace BinarySearchMask
{
	template <class T>
	size_t findLeftMostSetBit(T number)
	{
		if (number == 0)
			return -1;
		int left = sizeof(T) * bitsInByte;
		int right = 0;
		while(left > right) 
		{
			int middle = (left + right) / 2;
			T mask = static_cast<T>(pow(double(2), left) - pow(double(2), middle));
			if (number & mask)
			{
				if (abs(left - middle) <= 1)
					return middle;
				right = middle;
			}
			else
			{
				left = middle;
			}
		}
		return -1;
	}
}