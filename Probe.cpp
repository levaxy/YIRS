#include"Probe.h"


Probe::	Probe() {
		this->ID = 2;
		this->laba = &NullOper;
	}
	void Probe::Completer(){//вызывается в те моменты, когда завершается процесс или у хранилища, когда пришёл результат из лабы (странный комментарий)

		this->condition = 2;
		this->RunTime = RunTimes[i];
		i++;
		laba->Beginner(this->EndTime, (this->container));
	}
	int Probe::GetCondit(int flag)const {//если лаба занята, то и взятие пробы занято(пахнет хуетой) ну да ладно. Главное где попало её не вызывать
		if(flag == 0){
			if(laba->GetCondit(0) == 0){
				return this->condition;
			}
			return 1;
		}
		return this->condition;
	}
	//Operation* Probe::GetNextOper() {
	//	return this->NextOper->GetThisOper();
	//}

//проверка, чо взятие пробы свободно 
//если у пробы следующий пункт это гнездо, то надо переопределить метод возвращающий NextOper решено