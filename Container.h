#pragma once
#include <iostream>
using namespace std;
//#include"NullContainer.h"
class Container
{
public:
	Container();

	Container(const int& content, const int& id);
	int content = 0;
	int ID = 0;
private:

};