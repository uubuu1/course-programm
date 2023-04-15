#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct dataAccount
{
	string username;
	string password;
};

struct dataSubscribers
{
	string Surname, Name, Otchestvo;
	string PhoneNumber;
	int dayReg{0}, monthReg{0}, yearReg{0};
	int TariffPlan{0};
};

struct tariffs
{
	string nameTariffPlan;
	int costTariffPlan;
	int codeTariffPlan;
};

void inclear()
{
	char buf;
	if (scanf_s("%c", &buf, 1) == 1) while (buf != '\n') scanf_s("%c", &buf, 1);
	return;
}

char checkName(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (!((str[i] >= '�' && str[i] <= '�') || (str[i] >= '�' && str[i] <= '�')))
			return str[i];
	}
	return NULL;
}

void registration()
{
	ifstream accounts("accounts.txt");
	if (!accounts.is_open())
	{
		cout << "������ ��� �������� ����� � ���������� �������������\n";
		return;
	}
	int countAccounts;
	accounts >> countAccounts;
	dataAccount* account = new dataAccount[countAccounts+1];
	int i;
	char temp;
	for (i = 0; i < countAccounts; i++)
		accounts >> account[i].username >> account[i].password;
	accounts.close();
	cout << "������� ����� ������������. ������, ��� ����� ����� ��������� ������ ����� �������� �������� � ���� \"_\".\n�����: ";
	i = 0;
	while (1) //���� � �������� ������
	{
		string username;
		getline(cin, username);
		account[countAccounts].username = username;
		if (account[countAccounts].username == "-")
		{
			delete[] account;
			return;
		}
		temp = checkName(account[countAccounts].username);
		if (temp != NULL)
		{
			cout << "�������� ��� ������������ �������� ������������ ������: " << temp << "\n��������� ������� ��� �������� ����������� ����� \"-\"\n";
			break;
		}
		for (i = 0; i < countAccounts; i++)
			if (account[i].username == account[countAccounts].username)
			{
				cout << "������ ������� ��� ���������������. ��������� ������� ��� �������� ����������� ����� \"-\"\n";
				break;
			}
		if (i == countAccounts)
		{
			cout << "������� �������� ������ �� ��������. ������, ��� ������ �� ����� ��������� �������.\n������: ";
			while (1) //���� ������
			{
				getline(cin, account[countAccounts].password);
				if (account[countAccounts].username == "-")
				{
					delete[] account;
					return;
				}
				for (i = 0; i < account[countAccounts].password.size(); i++)
				{
					if (account[countAccounts].password[i] == ' ')
					{
						cout << "�������� ������ ������������ �������� ������������ ������.\n��������� ������� ��� �������� ����������� ����� \"-\"\n";
						break;
					}
				}
				ofstream accounts("accounts.txt"); //�������� ������������ � ����
				if (!accounts.is_open())
				{
					cout << "������ ��� �������� ����� � ���������� �������������\n";
					return;
				}
				accounts << countAccounts + 1 << "\n";
				for (i = 0; i < countAccounts + 1; i++)
				{
					accounts << account[i].username << " " << account[i].password << "\n";
				}
				accounts.close();
				return;
			}
		}
	}
	for (int i=0; i<countAccounts; i++)
		if (account[i].username == account[countAccounts].username)
		{
			cout << "������ ������� ��� ���������������. ��������� ������� ��� �������� ����������� ����� \"-\"\n";
			break;
		}
	delete[] account;
	return;
}

int autorisation()
{
	cout << "������� ����� � ������: ";
	string log, pass;
	string dataLog, dataPass;
	int countAccounts;
	while (1)
	{
		ifstream accounts("accounts.txt");
		if (!accounts.is_open())
		{
			cout << "������ ��� �������� ����� � ���������� �������������\n";
			return 0;
		}
		accounts >> countAccounts;
		cin >> log;
		if (log == "-")
		{
			return 0;
		}
		cin >> pass;
		for (int i = 0; i < countAccounts; i++)
		{
			accounts >> dataLog;
			accounts >> dataPass;
			if (log == dataLog && pass == dataPass)
			{
				if (i == 0) return 2; else return 1;
			}
		}
		cout << "������� ������������ ������. ��������� ������� ��� �������� ����������� ����� \"-\"\n";
		accounts.close();
	}
}

void newsub()
{
	ifstream subscribers("subscribers.txt");
	if (!subscribers.is_open())
	{
		cout << "������ ��� �������� ����� � ���������� �������������\n";
		return;
	}
	int countSubscribers;
	char temp;
	subscribers >> countSubscribers;
	dataSubscribers* sub = new dataSubscribers[countSubscribers + 1];
	int i;
	for (i = 0; i < countSubscribers; i++)
	{
		subscribers >> sub[i].Surname >> sub[i].Name >> sub[i].Otchestvo;
		subscribers >> sub[i].PhoneNumber;
		subscribers >> sub[i].dayReg >> sub[i].monthReg >> sub[i].yearReg;
		subscribers >> sub[i].TariffPlan;
	}
	subscribers.close();

	ifstream tariffplan("tariffplans.txt");
	if (!tariffplan.is_open())
	{
		cout << "������ ��� �������� ����� � �������� �������� ���������\n";
		return;
	}
	int countTariffs;
	string str;
	tariffplan >> countTariffs;
	tariffs* Tariff = new tariffs[countTariffs];
	for (i = 0; i < countTariffs; i++)
	{
		getline(tariffplan, str);
		getline(tariffplan, str);
		getline(tariffplan, str);
		Tariff[i].nameTariffPlan = str;
		tariffplan >> Tariff[i].costTariffPlan;
		tariffplan >> Tariff[i].codeTariffPlan;
	}
	tariffplan.close();

	while (1)
	{
		while (1) //���� �������
		{
			cout << "������� ������� ��������: ";
			cin >> sub[countSubscribers].Surname;
			if (sub[countSubscribers].Surname == "-")
			{
				delete[] sub;
				delete[] Tariff;
				return;
			}
			if ((temp = checkName(sub[countSubscribers].Surname)) == NULL)
				break;
				cout << "�������� ������� �������� ������������ ������: " << temp << "\n��������� ������� ��� �������� ���������� �������� ����� \"-\"\n";
		}
		while (1) //���� �����
		{
			cout << "������� ��� ��������: ";
			cin >> sub[countSubscribers].Name;
			if (sub[countSubscribers].Name == "-")
			{
				delete[] sub;
				delete[] Tariff;
				return;
			}
			if ((temp = checkName(sub[countSubscribers].Name)) == NULL)
				break;
			cout << "�������� ��� �������� ������������ ������: " << temp << "\n��������� ������� ��� �������� ���������� �������� ����� \"-\"\n";
		}
		while (1) //���� ��������
		{
			cout << "������� �������� ��������: ";
			cin >> sub[countSubscribers].Otchestvo;
			if (sub[countSubscribers].Otchestvo == "-")
			{
				delete[] sub;
				delete[] Tariff;
				return;
			}
			if ((temp = checkName(sub[countSubscribers].Otchestvo)) == NULL)
				break;
			cout << "�������� �������� �������� ������������ ������: " << temp << "\n��������� ������� ��� �������� ���������� �������� ����� \"-\"\n";
		}
		while (1) //���� ����������� ������ ��������
		{
			cout << "������� ���������� ����� ��������: ";
			cin >> sub[countSubscribers].PhoneNumber;
			if (sub[countSubscribers].PhoneNumber == "-")
			{
				delete[] sub;
				delete[] Tariff;
				return;
			}
			if (sub[countSubscribers].PhoneNumber.size() != 13 || sub[countSubscribers].PhoneNumber[0]!='+' || sub[countSubscribers].PhoneNumber[1]!='3' || sub[countSubscribers].PhoneNumber[2]!='7' || sub[countSubscribers].PhoneNumber[3]!='5' || sub[countSubscribers].PhoneNumber[4]!='0' || sub[countSubscribers].PhoneNumber[5]!='0')
			{
				cout << "�������� ���������� ����� �����������. ������ ����������� ������: +37500xxxxxxx\n";
				continue;
			}
			for (i = 6; i < 13; i++)
				if (!(sub[countSubscribers].PhoneNumber[i] >= '0' && sub[countSubscribers].PhoneNumber[i] <= '9'))
					i = 14;
			if (i == 14)
				cout << "���������� ����� ������ �������� ������ �� ����";
			else for (i = 0; i < countSubscribers; i++)
				if (sub[countSubscribers].PhoneNumber == sub[i].PhoneNumber)
				{
					cout << "������ ���������� ����� ��� �����";
					i = 14;
				}
			if (i != 14) break;
		}
		while (1) //���� ����
		{
			cout << "������� ���� ����������� �������� � ������� dd mm yy: ";
			int day, month, year;
			//if (!scanf_s("%d%d%d", sub[countSubscribers].dayReg, sub[countSubscribers].monthReg, sub[countSubscribers].yearReg))
			if (!scanf_s("%d%d%d", &day, &month, &year))
			{
				char buf;
				scanf_s("%c", &buf, 1);
				if (buf == '-')
				{
					inclear();
					delete[] sub;
					delete[] Tariff;
					return;	
				}
				inclear();
				cout << "������������ ����. ���� �������� ������� � ������� dd mm yy\n";
				continue;
			}
			sub[countSubscribers].dayReg = day;
			sub[countSubscribers].monthReg = month;
			sub[countSubscribers].yearReg = year;
			if ((sub[countSubscribers].yearReg > 23 && sub[countSubscribers].yearReg < 50) || (sub[countSubscribers].monthReg < 1 || sub[countSubscribers].monthReg >12) || (sub[countSubscribers].dayReg<1 || sub[countSubscribers].dayReg>31))
			{
				cout << "�������� ���� �����������. ��������� ������� ��� ������� \"-\" ��� ������ ���������� ��������\n";
				continue;
			}
			if (sub[countSubscribers].yearReg % 4 != 0 && sub[countSubscribers].monthReg == 2 && sub[countSubscribers].dayReg > 28)
			{
				cout << "�������� ���� �����������. ��������� ������� ��� ������� \"-\" ��� ������ ���������� ��������\n";
				continue;
			}
			else if (sub[countSubscribers].yearReg % 4 == 0 && sub[countSubscribers].monthReg == 2 && sub[countSubscribers].dayReg > 29)
			{
				cout << "�������� ���� �����������. ��������� ������� ��� ������� \"-\" ��� ������ ���������� ��������\n";
				continue;
			}
			else if ((sub[countSubscribers].monthReg == 4 || sub[countSubscribers].monthReg == 6 || sub[countSubscribers].monthReg == 9 || sub[countSubscribers].monthReg == 11) && sub[countSubscribers].dayReg > 30)
			{
				cout << "�������� ���� �����������. ��������� ������� ��� ������� \"-\" ��� ������ ���������� ��������\n";
				continue;
			}
			break;
		}
		while (1) //���� ��������� �����
		{
			cout << "������� ��� ��������� �����: ";
			int Tarif;
			//if (!scanf_s("%d", sub[countSubscribers].TariffPlan))
			if (!scanf_s("%d", &Tarif))
			{
				char buf;
				scanf_s("%c", &buf, 1);
				if (buf == '-')
				{
					inclear();
					delete[] sub;
					delete[] Tariff;
					return;
				}
				inclear();
				cout << "������������ ����. ��� ��������� ����� �������� ������ � ������������ ���������������.\n";
				continue;
			}
			for (i = 0; i < countTariffs; i++)
				if (Tarif == Tariff[i].codeTariffPlan)
				{
					i--;
					break;
				}
			if (i != countTariffs)
			{
				sub[countSubscribers].TariffPlan = Tarif;
				break;
			}
			cout << "�������� ��� �� ������������� �� ������ �� �������� ������. ��������� ������� ��� ������� \"-\" ��� ������ ���������� ��������\n";
		}
		ofstream subscribers("subscribers.txt"); //�������� �������� � ����
		if (!subscribers.is_open())
		{
			cout << "������ ��� �������� ����� � ���������� �������������\n";
			delete[] sub;
			delete[] Tariff;
			return;
		}
		subscribers << countSubscribers + 1 << "\n";
		for (i = 0; i < countSubscribers + 1; i++)
		{
			subscribers << sub[i].Surname << " " << sub[i].Name << " " << sub[i].Otchestvo << " ";
			subscribers << sub[i].PhoneNumber << " ";
			subscribers << sub[i].dayReg << " " << sub[i].monthReg << " " << sub[i].yearReg << " ";
			subscribers << sub[i].TariffPlan << "\n";
		}
		subscribers.close();
		delete[] sub;
		return;
	}
}

void addTariff()
{
	ifstream tariffplan("tariffplans.txt");
	if (!tariffplan.is_open())
	{
		cout << "������ ��� �������� ����� � �������� �������� ���������\n";
		return;
	}
	int countTariffs;
	char temp;
	string str;
	tariffplan >> countTariffs;
	tariffs* Tariff = new tariffs[countTariffs + 1];
	int i;
	for (i = 0; i < countTariffs; i++)
	{
		getline(tariffplan, str);
		getline(tariffplan, str);
		getline(tariffplan, str);
		Tariff[i].nameTariffPlan = str;
		tariffplan >> Tariff[i].costTariffPlan;
		tariffplan >> Tariff[i].codeTariffPlan;
	}
	tariffplan.close();
	while (1)
	{
		while (1) //���� ����
		{
			cout << "������� ��� ��������� �����: ";
			int code;
			if (!scanf_s("%d", &code))
			{
				char buf;
				scanf_s("%c", &buf, 1);
				if (buf == '-')
				{
					inclear();
					delete[] Tariff;
					return;
				}
				inclear();
				cout << "������������ ����. ��� ��������� ����� �������� ������.\n";
				continue;
			}
			Tariff[countTariffs].codeTariffPlan = code;
			for (i = 0; i < countTariffs; i++)
			{
				if (Tariff[countTariffs].codeTariffPlan == Tariff[i].codeTariffPlan)
				{
					cout << "�������� ���� � ������ ����� ��� �����. ��������� ������� ��� ������� \"-\" ��� ������ ���������� ��������� �����\n";
					break;
				}
			}
			if (i != countTariffs)
				continue;
			while (1) //���� ��������
			{
				cout << "������� �������� ��������� �����\n";
				inclear();
				getline(cin, str);
				Tariff[countTariffs].nameTariffPlan = str;
				if (Tariff[countTariffs].nameTariffPlan == "-")
				{
					delete[] Tariff;
					return;
				}
				break;
			}
			while (1) //���� ���������
			{
				cout << "������� ��������� ��������� �����: ";
				int Cost;
				if (!scanf_s("%d", &Cost))
				{
					char buf;
					scanf_s("%c", &buf, 1);
					if (buf == '-')
					{
						inclear();
						delete[] Tariff;
						return;
					}
					inclear();
					cout << "������������ ����. ��������� ��������� ����� �������� ������ � ������ ���� ������ ����.\n";
					continue;
				}
				if (Cost < 1)
				{
					cout << "������������ ����. ��������� ��������� ����� ������ ���� �������������.\n";
					continue;
				}
				Tariff[countTariffs].costTariffPlan = Cost;
				break;
			}
			ofstream tariffplan("tariffplans.txt"); //�������� ������ � ����
			if (!tariffplan.is_open())
			{
				cout << "������ ��� �������� ����� � ��������\n";
				delete[] Tariff;
				return;
			}
			tariffplan << countTariffs + 1 << "\n\n";
			for (i = 0; i < countTariffs + 1; i++)
			{
				tariffplan << Tariff[i].nameTariffPlan << "\n" << Tariff[i].costTariffPlan << " " << Tariff[i].codeTariffPlan << "\n\n";
			}
			tariffplan.close();
			delete[] Tariff;
			return;
		}
	}
}

void userMenu()
{
	while (1)
	{
		cout << "�������� ��������: ���������� ������� (1), �������� ������ ��������� (2), ������������� ���� ��������� (3), ����� �� ������� (0)\n";
		int choice;
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			inclear();
			//
			break;
		case 2:
			inclear();
			//
			break;
		case 3:
			inclear();
			
			while (choice)
			{
				cout << "������ �������� � ���� - 1\n������������� ���������� � �������� - 2\n������� �������� �� ���� - 3\n��������� �������������� - 0\n";
				scanf_s("%d", &choice);
				switch (choice)
				{
				case 1:
					inclear();
					newsub();
					break;
				case 2:
					inclear();
					//
					break;
				case 3:
					inclear();
					//
					break;
				case 0:
					inclear();
					//
					break;
				default: printf("������������ ����!\n");
					inclear();
					break;
				}
			}

			break;
		case 0:
			inclear();
			//
			return;
		default: printf("������������ ����!\n");
			inclear();
			break;
		}
	}
	return;
}

void adminMenu()
{
	while (1)
	{
		cout << "������� � ���� ������������ - 1\n���������������� ������ ������������ - 2\n������������� �������� ����� - 3\n����� �� ������� - 0\n";
		int choice;
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			inclear();
			userMenu();
			break;
		case 2:
			inclear();
			registration();
			break;
		case 3:
			inclear();
			while (choice)
			{
				cout << "�������� ����� �������� ���� - 1\n��������� �������������� �������� ������ - 0\n";
				scanf_s("%d", &choice);
				switch (choice)
				{
				case 1:
					inclear();
					addTariff();
					break;
				case 0:
					inclear();
					//
					break;
				default:
					printf("������������ ����!\n");
					inclear();
					break;
				}
			}
			break;
		case 0:
			inclear();
			//
			return;
		default:
			printf("������������ ����!\n");
			inclear();
			break;
		}
	}
}