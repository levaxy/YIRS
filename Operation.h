#pragma once
#include <iostream>
using namespace std;
#include"Container.h"
#include<vector>
#include"NullContainer.h"


class Operation
{
public:
	Operation();
	virtual int GetCondit(int flag)const;
	int condition;
	int EndTime;
	int RunTime;
	int CodePrior;
	int ID;//начинаются с 0
	int i;
	Container* container;
	Operation* NextOper;
	int Motoclock;
	int NewMotorTime;
	int PPR;
	int EndPPR;
	vector<int> RunTimes;//задаётся при предустановке
	virtual void Completer();//вызывается в те моменты, когда завершается процесс или у хранилища, когда пришёл результат из лабы
	virtual void Beginner(const int& current_time, Container* cont);
	virtual bool CheckReady();
	virtual bool CheckEnd(const int& current_time)const;
	virtual Operation* GetNextOper();
	virtual Operation* GetThisOper();
	virtual int GetMotorTime();
	virtual void SetRunTime(const int& runtime, const int& tStart, const int& tend);
	void BeginPPR(const int& CurTime);
	void CompletePPR();
	bool CheckEndPPR(const int& current_time)const;
private:


};
extern Operation NullOper;