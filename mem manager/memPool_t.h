#ifndef memPool_t_H
#define memPool_t_H

#include "memManager_t.h"
#include "memPage_t.h"
#include <algorithm> 
using namespace std;

class memPool_t :public memManager_t{
private:
	memPage_t **pages;							//an array of pointers to pages
	memPage_t *currentPage;
	int *pageSizes;
	int numOfPages;
	int defaultPageSize;


	memPool_t(const memPool_t& otherPage){}
	void operator=(const memPool_t& rhs){}

	/*
	calculate page number from posInPool , and store offset in that page inside posInPage
	*/
	int  getPage(int * posInPage, const int& posInPool) const;
	int  getPageHelper(const int& currentPageNum, int * posInPage, const int& pos)const;

	memPage_t * addNewPage(const int &pageSize);

public:

	memPool_t();
	virtual ~memPool_t();

	using memManager_t::read;
	using memManager_t::write;
	inline int getDefaultPageSize()const					{ return defaultPageSize; }
	inline void setDefaultPageSize(const int & newSize)		{ defaultPageSize = newSize; }
	inline int getNumOfPages()								{ return numOfPages; }


	/*
	* read  data starting from fromPos  , and store in dst
	*/
	int read(void *buf, const int & size, const int & fromPos) ;


	/*
	* write the data starting from toPos  ,  return number of bytes written
	*/
	int write(void* const data, const int& sizeOfdata, const int& toPos);


	/*
	for debugging
	*/
	void print()const;

};

#endif