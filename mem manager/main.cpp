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

	bool cont = true, flag;			// trigger to stop loop
	int writeflag = 0;
	int value, position, size, result, temp;
	int rx = -1;

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
			<< "12 - quit " << endl;
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
			result = pool.write(&value, sizeof(int), position);
			if (result == -1){
				printf("position Does not exist\n");
				break;
			}
			cout << "written " << result << " bytes from position " << position << endl;
			break;
		case 3:
			result = pool.read(&rx, sizeof(int));
			if (result > 0) 
				printf("read %d bytes from current position, value read =  : %d\n", result, rx);
			else
				printf("error reading from current position\n");
			break;
		case 4:
			cout << "enter position" << endl;
			cin >> position;
			result = pool.read(&rx, sizeof(int), position);
			if (result >0)
				printf("read %d bytes from position %d , value read =  %d\n",result, position, rx);
			else
				printf("error reading from position %d\n" ,position);
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
		case 12:
			cont = false;
			break;
		default:
			printf("wrong choice\n");
			break;
		}
	}

	return 0;
}
