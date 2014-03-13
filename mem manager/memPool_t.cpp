#include "memPool_t.h"
using namespace std;

memPool_t::memPool_t(){

	pages = new memPage_t*[1];
	pageSizes = new int[1];

	currentPage = pages[0] = new memPage_t();

	pageSizes[0] = defaultPageSize = 8;
	numOfPages = 1;
	actualSize = 0;
}

memPool_t::~memPool_t(){
	for (int i = 0; i < numOfPages; i++){
		delete(pages[i]);
	}
	delete[] pages;
	delete pageSizes;
}

int memPool_t::write(void* const data, const int& sizeOfdata, const int& toPos){
	int posInPage, bytesWritten = 0;												//will hold offset inside page
	int targetPageNumber = getPage(&posInPage, toPos);

	if (targetPageNumber == numOfPages)
		addNewPage(defaultPageSize);

	memPage_t * targetPage = pages[targetPageNumber];
	targetPage->setPos(posInPage);

	if (posInPage + sizeOfdata <= targetPage->getCapacity()){					//if whole data fits in page 
		bytesWritten = targetPage->write(data, sizeOfdata);						//write data in current page
	}
	else{																		//else a split is needed 
		int bytesWrittenInThisPage = 0, restOfBytes = 0;
		memPage_t * nextPage = 0;

		if (targetPageNumber == numOfPages - 1)									//if its the last page 
			nextPage = addNewPage(defaultPageSize);
		else
			nextPage = pages[targetPageNumber + 1];

		int sizeOfFirstChunk = targetPage->leftSpace();

		targetPage->setPos(posInPage);
		bytesWrittenInThisPage = targetPage->write(data, sizeOfFirstChunk);		//fill current page and continue in next pages
		restOfBytes = write((char *)data + sizeOfFirstChunk, sizeOfdata - sizeOfFirstChunk, toPos + sizeOfFirstChunk);
		bytesWritten = bytesWrittenInThisPage + restOfBytes;
	}

	currentPos = toPos + sizeOfdata;
	currentPage = targetPage;
	actualSize = max(toPos + sizeOfdata, actualSize);
	return bytesWritten;
}


void memPool_t::read(void *buf, const int & sizeOfData, const int & fromPos) const{
	int posInPage;															//will hold offset inside page
	int targetPageNumber = getPage(&posInPage, fromPos);
	int bytesToRead = min(sizeOfData, actualSize - fromPos);				//dont read beyond actual size 

	memPage_t * targetPage = pages[targetPageNumber];

	if (posInPage + bytesToRead <= targetPage->getCapacity()){				//the whole data is in tagetPage
		targetPage->setPos(posInPage);
		targetPage->read(buf, bytesToRead);
	}
	else {																	//need to read from multiple pages
		int pageCapacity = targetPage->getCapacity();
		int sizeOfFirstChunk = bytesToRead + posInPage > pageCapacity ?		//is data to read bigger then page capacity ?
			pageCapacity - posInPage : pageCapacity - bytesToRead;

		targetPage->read(buf, sizeOfFirstChunk, posInPage);					//first read until end of current page
		read((char *)buf + sizeOfFirstChunk,								//countinue recursively from next pages 
			bytesToRead - sizeOfFirstChunk, fromPos + sizeOfFirstChunk);
	}
}


memPage_t * memPool_t::addNewPage(const int &pageSize){
	memPage_t * newPage = new memPage_t(defaultPageSize);

	int  *newPageSizes = new int[numOfPages + 1];
	memPage_t **newPages = new memPage_t*[numOfPages + 1];

	for (int i = 0; i < numOfPages; i++){
		newPageSizes[i] = pageSizes[i];
		newPages[i] = pages[i];
	}
	newPageSizes[numOfPages] = defaultPageSize;
	newPages[numOfPages] = newPage;

	numOfPages++;

	delete[] pages;
	delete[]pageSizes;

	pages = newPages;
	pageSizes = newPageSizes;

	return newPage;
}

int  memPool_t::getPage(int * posInPage, const int& posInPool) const  {
	return getPageHelper(0, posInPage, posInPool);
}

int memPool_t::getPageHelper(const int& currentPageNum, int * posInPage, const int& pos)const   {

	if (currentPageNum == numOfPages){
		*posInPage = 0;
		return currentPageNum;
	}
	for (int i = currentPageNum; i < numOfPages; i++){
		int pageSize = pageSizes[i];
		if (pos < pageSize){
			*posInPage = pos;
			return i;
		}
		else return getPageHelper(currentPageNum + 1, posInPage, pos - pageSize);
	}
}

void memPool_t::print()const{
	for (int i = 0; i < numOfPages; i++){
		cout << "page " << i << ": ";
		pages[i]->print();
	}
	cout << endl;
}