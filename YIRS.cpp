﻿#include <iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
#include"Operation.h"
#include"Granulating.h"
#include"Averaging.h"
#include"AddStZn.h"
#include"Granulating.h"
#include"Manipulator.h"
#include"Container.h"
#include"Laba.h"
#include"Cell.h"
#include"Press.h"
#include"Storage.h"
#include"Probe.h"
#include<fstream>

//extern const Container NullContainer{};

// Предустановка // Из стартового файла берёт начальное состояние системы

void Init(ifstream& in, vector<Operation*>& obj, Manipulator& manip, Storage& stor, int& tStart, int& tend, vector<Container*>& conteiners, vector<Cell*>& Cells){
	string s;
	in>>tStart>>tend;
	for(Container* c: conteiners){
		in>>c->content>>c->ID;
	}
	//читаем данные контейнеров
	int TimeInWork = 0, IDcont = 0, PPR = 0, MotorTime = 0, NewMotorTime = 0, RunTime = 0;
//читаем даные об объектах
	for(Operation*& o: obj){
		in>>o->condition>>TimeInWork>>o->CodePrior>>IDcont>>PPR>>MotorTime>>NewMotorTime>>RunTime; 
		//считали данные из строки
		o->SetRunTime(RunTime, tStart, tend);//заполняем массив случайными числами (RunTime + (0-10)%)
		for(Container*& c: conteiners ){//ищем контейнер по ID
			if(c->ID == IDcont){
				o->container = c;
			}
		}
		//если работает, записываем время окончания
		if(o->condition == 1){
			o->EndTime = tStart + o->RunTime - TimeInWork;
		}
		//всякие штучки приколючки
		o->PPR = PPR;
		o->Motoclock = MotorTime;
		o->NewMotorTime = NewMotorTime;

	}
	//читаем данные о гнездах хранилища
	for(Cell*& n: Cells){
		in>>IDcont>>n->ID;
		if(IDcont == 0){//если нет контейнера
			n->container = &NullContainer;
			n->condition = 0;
		}
		else{//если есть, ищем по ID контейнера
			for (Container*& c : conteiners) {
				if (c->ID == IDcont) {
					n->container = c;
					n->condition = 1;
				}
			}
		}
	}
	//читаем манипулятор
	int IDdestination = 0;//ID объекта, куда везёт
	in>>manip.condition>>IDcont>> IDdestination >> manip.TimeEnd >> PPR >> MotorTime >> NewMotorTime;

	//давай пока предположим, что при предустановке не находится на ППР
	//если чё, то доп-но по кондитиону надо проверять и в файле вводить время конца ппр
	manip.Motoclock = MotorTime;
	manip.PPR = PPR;
	manip.NewMotorTime = NewMotorTime;//это полные моточасы


	if(manip.condition == 1){
		if(IDdestination<10 && IDdestination >= 0){	//проверяем типа что это это не гнездо и по ID ищем пункт назначения
			for(Operation*& o: obj){
				if(o->ID == IDdestination){
					manip.Destination = o;
				}
			}
		}
		//если гнездо, то ищем среди гнёзд
		else if(IDdestination>10){
			for(Cell*& n : Cells){
				if(IDdestination == n->ID){
					manip.Destination = n;
				}
			}
		}

	}

}


// В файл, эмитирующий БД записывает реальные состояния объектов к текущему моменту, но не меняет сами объекты
//Здесь не нужно ловить то что гнездо подаёт запрос, так как функция управления состояниями далее это сделает, но не на основе инфы из "БД", а через лабу. Надо здесь игнорить проверку хранилища. Можно сделать в Operation с этой целью метод проверки на конец выполнения CheckEnd, переопределить его у хранилища, чтоб он всегда возвращал фолз.
void EmulatorBD(ofstream& BD, const vector<Operation*>& Objects, const Manipulator& manip, const int& current_time){
	BD<<current_time<<"\t";
	if(manip.TimeEnd<=current_time && manip.condition == 1){//завершился ли процесс к этому времени
		BD << 0 << "\t";
	}
	else if(manip.CheckEndPPR(current_time)){//закончился ли ППР
		BD << 0 <<"\t";
	}
	else{
		BD<<manip.condition<<"\t";
	}
	for(const Operation* obj: Objects){
		if(obj->CheckEnd(current_time)){//если в эту секунду закончил, то пишется двоечка
			BD << 2 <<"\t";
		}
		else if(obj->CheckEndPPR(current_time)){
			BD << 0<<"\t";
		}
		else{
			BD << obj->condition<<"\t";
		}
	}

	BD<<"\n";
	
}


// УПРАВЛЕНИЕ СОСТОЯНИЯМИ // Сравнивает с файлом эмитирующим БД состояния объектов, которые остались с прошлой итерации и если есть отличие, то вызывает Completer
void Managing(ifstream& BD, vector<Operation*>& obj,Manipulator& manip){//Над этой функцией надо подумать
	int condit = 0, time = 0, ConditManip = 0;
	BD>>time>>ConditManip;
	for(Operation*& o: obj){	
		BD>>condit;
		if(condit != o->condition){
			if(o->condition == 3){
				o->CompletePPR();
			}
			else{
				o->Completer();
			}
		}
	}
	if(manip.container->ID != 0 && ConditManip == 0){
		manip.Completer();
	}
	else if(manip.condition == 3 && ConditManip == 0){
		manip.CompletePPR();
	}
}

int main(){
///////////////////////////////////////////

	ifstream init;
	init.open("Init2.txt");
	ofstream out;
	ofstream BDout;
	ofstream out_MotoTime;
	ifstream BDin;
	out.open("Out_Condition.txt");
	out<<"time\tmanip\tgran\tpress\taverat\tlaba\tproba\tStZn\tcell_1\tcell_2\tcell_3\n";
	BDout.open("BD.txt");
	BDout << "time\tmanip\tgran\tpress\taverat\tlaba\tproba\tStZn\n";
	BDout.close();
	BDin.open("BD.txt");
	string s;
	getline(BDin,s);
	out_MotoTime.open("Out_MotoTime.txt");
	out_MotoTime << "time\tmanip\tgran\tpress\taverat\tlaba\tproba\tStZn\n";
	/////////////////////////////////////////////////////////////////////////////////////////

	vector<Container*> containers;
	vector<Operation*> Objects;
	vector<Cell*> Cells;
	vector<int> Queue;

	int tStart = 0, tend = 0, QuantCont = 4;

	Cells.reserve(3);
	containers.reserve(QuantCont);
	Queue.reserve(QuantCont);
	Objects.reserve(8);
	Container c1{};
	Container c2{};
	Container c3{};
	Container c4{};

	containers.push_back(&c1);
	containers.push_back(&c2);
	containers.push_back(&c3);
	containers.push_back(&c4);

	Manipulator manip;
	Storage stor;
	Granulating granulation;
	Averaging averaging;
	Probe probe;
	Laba lab;
	AddStZn addSt;
	Press press;

	granulation.NextOper = &averaging;
	averaging.NextOper = &probe;
	probe.laba = &lab;
	probe.NextOper = &stor;
	addSt.NextOper = &averaging;
	press.aver = &averaging;
	press.NextOper = &granulation;

	Cell Cell1{};
	Cell Cell2{};
	Cell Cell3{};

	Cells.push_back(&Cell1);
	Cells.push_back(&Cell2);
	Cells.push_back(&Cell3);
	for(Cell*& n: Cells){
		n->addstzn = &addSt;
		n->granulator = &granulation;
		n->press = &press;
	}
	stor.SetCells(Cells);

	Objects.push_back(&granulation);//гран, пресс, уср, лаба, проба, стеарат
	Objects.push_back(&press);
	Objects.push_back(&averaging);
	Objects.push_back(&lab);
	Objects.push_back(&probe);
	Objects.push_back(&addSt);
	
 ////////////////////////////////////////////////////////////
	
	Init(init, Objects, manip, stor, tStart, tend, containers, Cells);

 ////////////////////////////////////////////////////////////
	for (size_t t = tStart; t < tend; t++){
		///////////////////////////////////////////////////////////
		out.open("Out_Condition.txt", ios::app);
		out_MotoTime.open("Out_MotoTime.txt",ios::app);
		BDout.open("BD.txt", ios::app);
		////////////////////////////////////////////////////
		EmulatorBD(BDout, Objects, manip, t);
		BDout.close();

		Managing(BDin, Objects, manip);

		if(manip.condition == 0){
			manip.ManipManaging(t, Objects, Queue, &stor);
		}
		/////////////////////////////////////////////////////
		Queue.clear();
		out<<t<<"\t";
		out_MotoTime<<t<<"\t";
		out<<manip.condition << "\t";
		out_MotoTime << manip.Motoclock << "\t";
		/////////////////////////////////////////////
		for(Operation*& obj : Objects){
			out<< obj->condition<<"\t";
			out_MotoTime<<obj->Motoclock<<"\t";
		}
		for (Cell*& Cell : stor.Cells) {
			out << Cell->container->content << "\t";
		}
		////////////////////////////////////////
		out<<"\n";
		out.close();
		out_MotoTime<<"\n";
		out_MotoTime.close();
		/////////////////////////////////////////
	}
   return 0;
}

