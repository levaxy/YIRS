#include"AddStZn.h"

AddStZn:: AddStZn(){
this->ID = 5;
}

void AddStZn::Completer() {//вызывается в те моменты, когда завершается процесс или у хранилища, когда пришёл результат из лабы
	i++;
	this->container->content += 2;
	this->condition = 2;
	this->Motoclock -= RunTime;
	this->RunTime = RunTimes[i];
	this->Motoclock -= RunTime;
}
