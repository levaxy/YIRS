#include"Averaging.h"


Averaging::Averaging(){
this->ID = 1;
}

void Averaging:: SetRunTime(const int& runtime, const int& tStart, const int& tend) {

	this->RunTimes = {8,4,5,10,7,13,15,6,2,3,11};//  астомизаци€ времени работы усреднител€

	RunTime = RunTimes[0];
}
