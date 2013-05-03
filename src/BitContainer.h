/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef BITCONTAINER_H
#define BITCONTAINER_H
#include <vector>
#include <QString>

using namespace std;

/**
 * @brief Klasa służaca jako skompresowany kontener na inty
 **/
class BitContainer {
	private:
		const int bitsPerInt = 64;
		int bitsPerValue, maxValue, size;
		vector<unsigned long long int> container;
		
		unsigned long long int getMask(const int begin, const int end, const int value);
		unsigned long long int getClearMask(const int begin, const int end);
		void setBits(const int row, const int begin, const int end, const int value);
		int getBits(const int row, const int begin, const int end);
		int getBegin(const int id);
		int getRow(const int id);
	public:
		/**
		 * @brief Konstruktor
		 *
		 * @param size rozmiar pożadanej tablicy
		 * @param maxValue maksymalna wartość do przechowywania
		 **/
		BitContainer(int size, int maxValue);
		
		void setValue(const int id, int value);
		int getValue(const int id);
		const QString getHash();
};

#endif // BITCONTAINER_H
