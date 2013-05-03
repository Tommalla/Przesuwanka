/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cmath>
#include <climits>
#include <cassert>
#include <QDebug>
#include <cstdio>
#include <bitset>
#include "BitContainer.h"

int BitContainer::getBegin (const int id) {
	return (this->bitsPerValue * id) % this->bitsPerInt;
}

int BitContainer::getRow (const int id) {
	return (this->bitsPerValue * id) / this->bitsPerInt;
}

long long unsigned int BitContainer::getMask (const int begin, const int end, const int value) {
	unsigned long long int mask = value;
	mask <<= this->bitsPerInt - end;
	return mask;
}

long long unsigned int BitContainer::getClearMask (const int begin, const int end) {
	unsigned long long int clearMask = ULLONG_MAX - (pow(2.0, (long double)this->bitsPerInt - begin) - 1);
	clearMask += (unsigned long long int)(pow(2.0, (long double)this->bitsPerInt - end) - 1);
	return clearMask;
}

int BitContainer::getBits (const int row, const int begin, const int end) {
	unsigned long long int mask = ~this->getClearMask(begin, end);
// 	printf("\tgetBits(row = %d, begin = %d, end = %d)\n", row, begin, end);
// 	printf("mask = %s\n", bitset<64>(mask).to_string<char,char_traits<char>,allocator<char> >().c_str());
	mask &= container[row];
// 	printf("mask = %s\n", bitset<64>(mask).to_string<char,char_traits<char>,allocator<char> >().c_str());
// 	puts("Done(getBits)");
	return mask / pow(2, (long double)this->bitsPerInt - end);//(container[row] - (ULLONG_MAX - (pow(2.0, (long double)this->bitsPerInt - begin) - 1))) /
		//pow(2, (long double)this->bitsPerInt - end);
}

void BitContainer::setBits (const int row, const int begin, const int end, const int value) {
// 	qDebug("\tsetBits(row=%d, begin=%d, end=%d, value=%d)\n", row, begin, end, value);
	
	unsigned long long int clearMask = this->getClearMask(begin, end);
	unsigned long long int mask = this->getMask(begin, end, value);
	
	container[row] &= clearMask;
	container[row] |= mask;
}


BitContainer::BitContainer (int size, int maxValue) {
	qDebug("Konstruktor BitContainer:\n\tsize = %d, maxValue = %d\n", size, maxValue);
	this->size = size;
	this->maxValue = maxValue;
	
	this->bitsPerValue = ceil(log2(maxValue));
	this->container.resize(ceil((double)(size * this->bitsPerValue) / (double)this->bitsPerInt), 0);
}

void BitContainer::setValue (const int id, int value) {
	assert(value <= maxValue);
	assert(id < size);
	
	int row = this->getRow(id);
	int begin = this->getBegin(id);
	int end = min(begin + this->bitsPerValue, this->bitsPerInt);
	
// 	QDebug() << "setValue(" << id << ", " << value <<"):\n\trow = " << row << "; begin = " << begin << "; end = " << end <<
// 	 "; mask = " << mask << "; clearMask = " << clearMask << "\n";
	this->setBits(row, begin, end, value >> (this->bitsPerValue - end + begin));
	
	//printf("DBG %d\n", this->bitsPerValue - end + begin);
	
	if (end - begin == this->bitsPerValue)
		return;
	
	value -= value - value / pow(2, this->bitsPerValue - end + begin);
	row++;
	end = this->bitsPerValue - end + begin;
	begin = 0;
	
	this->setBits(row, begin, end, value);
}

int BitContainer::getValue (const int id) {
	assert(id < size);
	
	int row = this->getRow(id);
	int begin = this->getBegin(id);
	int end = min(begin + this->bitsPerValue, this->bitsPerInt);
	
	int result = this->getBits(row, begin, end);
// 	printf("result = %s\n", bitset<64>(result).to_string<char,char_traits<char>,allocator<char> >().c_str());
	
	if (end - begin == this->bitsPerValue)
		return result;
	
	result <<= this->bitsPerValue - (end - begin);
// 	printf("result = %s\n", bitset<64>(result).to_string<char,char_traits<char>,allocator<char> >().c_str());
	row++;
	end = this->bitsPerValue - end + begin;
	begin = 0;
	
	return result + this->getBits(row, begin, end);
}

const QString BitContainer::getHash() {
	QString res = "";
	for (int i = 0; i < this->container.size(); ++i)
		res += QString::number(this->container[i]);
	return res;
}
