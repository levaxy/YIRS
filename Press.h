#pragma once
#include <iostream>
using namespace std;
#include"Operation.h"
#include"Averaging.h"

class Press : public Operation
{
public:
	Press();
	void Completer()override;
	bool CheckReady()override;
	void Beginner(const int& current_time, Container* cont);
	int GetCondit(int flag)const;
	Averaging* aver;
};
