#pragma once
#include <iostream>
using namespace std;
#include"Operation.h"
#include"Cell.h"
#include<vector>

// Выступает типа как буфер для гнезд
class Storage : public Operation
{
public:
	Storage();
	void SetCells(vector<Cell*>& Cells);
	virtual Operation* GetNextOper();

	int GetCondit(int flag)const override;
	Operation* GetThisOper()override;

	bool CheckEnd(const int& current_time)const override;
	vector<Cell*> Cells;
private:

};

