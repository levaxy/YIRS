#pragma once
#include <iostream>
using namespace std;
#include"Operation.h"

class Cell : public Operation
{
public:
	Cell();
	Operation* GetNextOper()override;
	void Beginner(const int& current_time, Container* cont)override;
	int GetCondit(int flag)const;
	bool CheckReady()override;
	Operation* press;
	Operation* addstzn;
	Operation* granulator;
private:

};