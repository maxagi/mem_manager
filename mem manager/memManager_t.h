#ifndef memManager_t_H
#define memManager_t_H

class memManager_t{

protected:

	int currentPos;
	int actualSize;

public:

	inline int setPos(const int & pos)		{ if (pos > actualSize) return -1; return currentPos = pos; }
	inline int getPos()          const		{ return currentPos; }
	inline int getActualSize()   const		{ return actualSize; }
	inline bool isEmpty()        const		{ return getActualSize() == 0; }


	virtual bool read(void *buf, const int & size, const int & fromPos) const = 0;
	inline  bool read(void *buf, const int & size) const {
		read(buf, size, getPos());
		return true;
	}

	virtual int write(void* const data, const int& sizeOfdata, const int& toPos) = 0;
	inline  int write(void* const data, const int& sizeOfdata){
		return write(data, sizeOfdata, getPos());
	}

};
#endif