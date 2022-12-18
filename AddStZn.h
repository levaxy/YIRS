#pragma once
#include <iostream>
using namespace std;
#include"Operation.h"

class AddStZn : public Operation
{
public:
	AddStZn();
	void Completer()override;
private:

};