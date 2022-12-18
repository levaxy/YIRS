#pragma once
#include <iostream>
using namespace std;
#include"Operation.h"

class Probe : public Operation
{
public:
	Probe();
	void Completer()override ;
	int GetCondit(int flag)const;//если лаба занята, то и взятие пробы занято(пахнет хуетой) ну да ладно. Главное где попало её не вызывать
//	Operation* GetNextOper();
	Operation* laba;
};
//проверка, чо взятие пробы свободно 
//если у пробы следующий пункт это гнездо, то надо переопределить метод возвращающий NextOper решено