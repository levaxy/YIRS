#include"Probe.h"


Probe::	Probe() {
		this->ID = 2;
		this->laba = &NullOper;
	}
	void Probe::Completer(){//���������� � �� �������, ����� ����������� ������� ��� � ���������, ����� ������ ��������� �� ���� (�������� �����������)

		this->condition = 2;
		this->RunTime = RunTimes[i];
		i++;
		laba->Beginner(this->EndTime, (this->container));
	}
	int Probe::GetCondit(int flag)const {//���� ���� ������, �� � ������ ����� ������(������ ������) �� �� �����. ������� ��� ������ � �� ��������
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

//��������, �� ������ ����� �������� 
//���� � ����� ��������� ����� ��� ������, �� ���� �������������� ����� ������������ NextOper ������