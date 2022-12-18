#pragma once
#include <iostream>
using namespace std;
#include"Operation.h"
#include<vector>

class Laba : public Operation
{
public:
	Laba();
	void Completer() override;
	bool CheckReady() override;
private:
	int result = 1;   //1 - <<+>>; 2 - <<->>
};