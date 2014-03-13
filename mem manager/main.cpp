#include <iostream>
#include "memPage_t.h"
#include "memPool_t.h"
using namespace std;

/*
this is an example  of how to use memPool_t
the examples are using only ints but you can use any data type you want,
including arrays , structs , objects , etc' (just like in fread & fwrite)
*/

//==============================================================

int main() {

	bool cont = true;			// trigger to stop loop

	int value, position, size, result, temp;
	int rx;

	memPool_t pool;

	while (cont) {
		unsigned int c;
		cout << "Enter your choise:" << endl
			<< "1 - write from current position" << endl
			<< "2 - write from position" << endl
			<< "3 - read from current position" << endl
			<< "4 - read from position" << endl
			<< "5 - get position" << endl
			<< "6 - set position" << endl
			<< "7 - print" << endl
			<< "8 - empty?" << endl
			<< "9 - size?" << endl
			<< "10 - get default size of memory page " << endl
			<< "11 - set default size of memory page " << endl
			<< "Any other key - quit" << endl;
		cin >> c;

		switch (c) {
		case 1:
			temp = pool.getPos();
			cout << "enter value to write (int) " << endl;
			cin >> value;
			result = pool.write(&value, sizeof(int));
			cout << "written " << result << " bytes from position " << temp << endl;
			break;
		case 2:
			cout << "enter value to write" << endl;
			cin >> value;
			cout << "enter position" << endl;
			cin >> position;
			pool.write(&value, sizeof(int), position);
			break;
		case 3:
			pool.read(&rx, sizeof(int));
			printf("read from current position : %d\n", rx);
			break;
		case 4:
			cout << "enter position" << endl;
			cin >> position;
			pool.read(&rx, sizeof(int), position);
			printf("read from position %d : %d\n", position, rx);
			break;
		case 5:
			cout << "current position = " << pool.getPos() << endl;
			break;
		case 6:
			cout << "enter new position" << endl;
			cin >> position;
			pool.setPos(position);
			printf("new position set to %d \n", position);
			break;
		case 7:
			pool.print();
			break;
		case 8:
			if (pool.isEmpty())
				printf("Empty\n");
			else
				printf("Not Empty\n\n");
			break;
		case 9:
			printf("size = %d\n", pool.getActualSize());
			break;
		case 10:
			size = pool.getDefaultPageSize();
			printf("size of memory page = %d\n", size);
			break;
		case 11:
			cout << "enter size of memory page" << endl;
			cin >> size;
			pool.setDefaultPageSize(size);
			break;

		default:
			cont = false;
			break;
		}
	}

	return 0;
}