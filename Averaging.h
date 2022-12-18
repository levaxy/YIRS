#pragma once
#include <iostream>
using namespace std;
#include"Operation.h"
#include"Container.h"


class Averaging : public Operation
{
public:
	Averaging();
	void SetRunTime(const int& runtime, const int& tStart, const int& tend)override;
private:

};