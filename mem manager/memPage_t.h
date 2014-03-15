#ifndef memPage_t_H
#define memPage_t_H

#include <algorithm> 
#include "memManager_t.h"
#include<iostream>
using namespace std;

class memPage_t : public memManager_t{

private:
	char * const data;						//const pointer to the START of data in heap 
	int capacity;

	memPage_t(const memPage_t& otherPage)	//private copy CTOR , not supposed to get called
		:data(new char[otherPage.getCapacity()]()){
	}

	void operator=(const memPage_t& rhs){}

public:
	memPage_t(const int & pageSize = 5);
	virtual ~memPage_t();

	using memManager_t::write;
	using memManager_t::read;
	inline bool isFull()		 const		{ return getActualSize() == getCapacity(); }
	inline int getCapacity()	 const		{ return capacity; }
	inline int leftSpace()       const		{ return capacity - actualSize; }

	/*
	* read  data starting from fromPos  , and store in buf 
	*/
	bool read(void *buf, const int & size, const int & fromPos) const;


	/*
	* write the data starting from toPos  , return number of bytes written
	*/
	int write(void* const data, const int& sizeOfdata, const int& toPos);


	/*
	for debugging
	note that data may be displayed in BIG-ENDIAN!
	*/
	void print()const;
};
#endif