#pragma once
#include <iostream>
using namespace std;
#include"Container.h"
#include"Operation.h"
#include<vector>
#include<algorithm>
#include"Storage.h"

class Manipulator
{
public:
	Manipulator();

	Container* container = &NullContainer;
	Operation* Destination;
	int TimeEnd = 0;
	int condition = 0;
	int Motoclock = 0;
	int NewMotorTime;
	int PPR;
	int EndPPR;
	int CurrentWay;
	void Beginner(const int& CurrentTime, Operation*& Source, Operation* destination);
	void Completer();
	void ManipManaging(const int& current_time, vector<Operation*>& Objects, vector<int>& queue, Storage* stor);
	void BeginPPR(const int& CurTime);
	void CompletePPR();
	void InitWaysArray();
	bool CheckEndPPR(const int& current_time)const;
private:
	int Gran_averaging;
	int Averaging_prob;
	int Prob_store;
	int Store_AddStZn;
	int AddStZn_averaging;
	int Store_defect_Store;
	int Store_press;
	int Press_gran;
	int Ways[8][8];
};