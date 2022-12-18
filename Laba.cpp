#include"Laba.h"
#include"NullContainer.h"

Laba:: Laba(){
		this->ID = 3;
	}
void Laba::Completer() {//
	if((double)rand()/RAND_MAX < 0.8)
		this->result = 1;
	else
		this->result = 2;
	this->container->content += this->result;
	this->RunTime = this->RunTimes[i];
	i++;
	this->condition = 0;
	this->container = &NullContainer;
}
bool Laba::CheckReady() {//лаба не подаёт запрос
	return (false);
}



