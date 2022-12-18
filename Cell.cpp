#include"Cell.h"

//надо 
Cell:: Cell():Operation(){//полем кондитион не оперурием в этом классе, только содержимым контейнера, помещЄнного в гнездо
	this->addstzn = &NullOper;
	this->granulator = &NullOper;
	this->press = &NullOper;
	this->Motoclock = 1;// т.к. в конструкторе по умолчанию RunTime = 0, то моточасы не будут отбавл€тьс€ у гнезда в комплитере 
	this->CodePrior = 10;// при получении кода приоритетности в managing_manip если брак, то будет это число добавл€тьс€ в очередь запросов.(Ёто код приоритетности увоза на переработку). ≈сли придЄтс€ мен€ть логику, что брак везут на пресс, то можно просто убрать весь код, св€зааный с увозом контейнера и привоза в то же место.
}
	Operation* Cell:: GetNextOper(){
		if(this->container->content == 1){//если пустой контейнер, то следующий пункт - это гранул€тор
			return this->granulator;
		}
		if (this->container->content == 9|| this->container->content == 5) {//если брак, то манипул€тор вернЄт пустой контейнер в то же гнездо. ќбсудить, куда должен увозитьс€ брак
			return this;
		}
		if (this->container->content == 4) {//уср, не брак, то в стеар. цинка
			return addstzn;
		}
		if (this->container->content == 8) {//если готовый, то на пресс
			return press;
		}
		return &NullOper;//в иных случа€х следующей операции нет
	}
	bool Cell::CheckReady() { 
		if(this->container->content == 5 || this->container->content == 9){
			return true;
		}// ≈сли брак в гнезде, гет кондит вернЄт 2(подаю запрос), гет некст опер вернЄт указатель на себ€, у него возьмЄтс€ геткондит, который вернЄт 2, а надо, чтоб был готов прин€ть контейнер, поэтому случай с браком отдельно провер€етс€.
		return (this->GetCondit(2) == 2 && this->GetNextOper()->GetCondit(0) == 0);
	}
	void Cell:: Beginner(const int& current_time, Container* cont){
		this->container = cont;
	}
	int Cell::GetCondit(int flag)const {//flag тут не используетс€
		if(this->container->content == 0){
			return 0;
		}
		else if(this->container->content == 7 || this->container->content == 3){
			return 1;
		}
		else if(this->container->content == 2 || this->container->content == 6){
			throw("ЌеусреднЄнный порошок попал в хранилище!\n");
		}
		else{
			return 2;
		}
	}
