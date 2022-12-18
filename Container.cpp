#include <iostream>
using namespace std;
#include"Container.h"



Container:: Container(){
		this->content = 0;
		this->ID = 0;
	}

Container::	Container(const int& content, const int& id){
		this->content = content;
		this->ID = id;
	}



