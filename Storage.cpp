#include"Storage.h"

Storage::Storage() {
		this->ID = 4;
	}
void Storage::SetCells(vector<Cell*>& Cells){
	this->Cells = Cells;
}
Operation* Storage::GetNextOper() {
	return this->NextOper;
}

int Storage::GetCondit(int flag)const{//flag: 2 - вернуть 2, если есть подающие запрос, 0 - вернуть 0, если есть свободные гнёзда
	if(flag == 0){
		for(const Operation* obj: this->Cells){
			if(obj->GetCondit(0) == 0){
				return 0;
			}
		}
	}
	if(flag == 2){
		for (const Operation* cell : this->Cells) {
			if (cell->GetCondit(2) == 2) {
				return 2;
			}
		}
	}
	return 1;
}
//?
Operation* Storage::GetThisOper(){
	for(Cell*& cell: Cells){
		if (cell->GetCondit(0) == 0) {
			return cell;
		}
	}
	return &NullOper;
}

bool Storage::CheckEnd(const int& current_time)const {//чтоб пропускать в БД
		return (false);
}

