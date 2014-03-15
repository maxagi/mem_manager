#include "memPage_t.h"
#include <assert.h>
using namespace std;

memPage_t::memPage_t(const int& pageSize) :data(new char[pageSize]()){
	capacity = pageSize;
	currentPos = 0;
	actualSize = 0;
}

memPage_t::~memPage_t(){
	delete[] data;
}

bool memPage_t::read(void *dst, const int & size, const int & fromPos) const{
	assert(fromPos + size <= capacity);
	memcpy(dst, data + fromPos, size);
	return true;
}

int  memPage_t::write(void* const newData, const int& sizeOfdata, const int& toPos){

	if (toPos < 0){
		return -1;
	}
	assert(toPos + sizeOfdata <= capacity);
	memcpy(data + toPos, newData, sizeOfdata);
	currentPos = currentPos + sizeOfdata;
	actualSize = max(actualSize, toPos + sizeOfdata);
	return sizeOfdata;
}

void memPage_t::print()const{
	for (int i = 0; i < capacity; i++){
		printf("%.8x,", data[i]);
	}
	cout << endl;
}
