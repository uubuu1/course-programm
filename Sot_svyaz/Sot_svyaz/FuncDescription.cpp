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
		if (!((str[i] >= 'а' && str[i] <= 'я') || (str[i] >= 'А' && str[i] <= 'Я')))
			return str[i];
	}
	return NULL;
}

void registration()
{
	ifstream accounts("accounts.txt");
	if (!accounts.is_open())
	{
		cout << "Ошибка при открытии файла с аккаунтами пользователей\n";
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
	cout << "Введите логин пользователя. Учтите, что логин может содержать только буквы русского алфавита и знак \"_\".\nЛогин: ";
	i = 0;
	while (1) //Ввод и проверка логина
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
			cout << "Введённое имя пользователя содержит недопустимый символ: " << temp << "\nПовторите попытку или отмените регистрацию введя \"-\"\n";
			break;
		}
		for (i = 0; i < countAccounts; i++)
			if (account[i].username == account[countAccounts].username)
			{
				cout << "Данный аккаунт уже зарегестрирован. Повторите попытку или отмените регистрацию введя \"-\"\n";
				break;
			}
		if (i == countAccounts)
		{
			cout << "Введите желаемый пароль от аккаунта. Учтите, что пароль не может содержать пробелы.\nПароль: ";
			while (1) //Ввод пароля
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
						cout << "Введённый пароль пользователя содержит недопустимый символ.\nПовторите попытку или отмените регистрацию введя \"-\"\n";
						break;
					}
				}
				ofstream accounts("accounts.txt"); //Внесение пользователя в файл
				if (!accounts.is_open())
				{
					cout << "Ошибка при открытии файла с аккаунтами пользователей\n";
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
			cout << "Данный аккаунт уже зарегестрирован. Повторите попытку или отмените регистрацию введя \"-\"\n";
			break;
		}
	delete[] account;
	return;
}

int autorisation()
{
	cout << "Введите логин и пароль: ";
	string log, pass;
	string dataLog, dataPass;
	int countAccounts;
	while (1)
	{
		ifstream accounts("accounts.txt");
		if (!accounts.is_open())
		{
			cout << "Ошибка при открытии файла с аккаунтами пользователей\n";
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
		cout << "Введены некорректные данные. Повторите попытку или отмените авторизацию введя \"-\"\n";
		accounts.close();
	}
}

void newsub()
{
	ifstream subscribers("subscribers.txt");
	if (!subscribers.is_open())
	{
		cout << "Ошибка при открытии файла с аккаунтами пользователей\n";
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
		cout << "Ошибка при открытии файла с тарифами сотового оператора\n";
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
		while (1) //Ввод фамилии
		{
			cout << "Введите фамилию абонента: ";
			cin >> sub[countSubscribers].Surname;
			if (sub[countSubscribers].Surname == "-")
			{
				delete[] sub;
				delete[] Tariff;
				return;
			}
			if ((temp = checkName(sub[countSubscribers].Surname)) == NULL)
				break;
				cout << "Введённая фамилия содержит недопустимый символ: " << temp << "\nПовторите попытку или отмените добавление абонента введя \"-\"\n";
		}
		while (1) //Ввод имени
		{
			cout << "Введите имя абонента: ";
			cin >> sub[countSubscribers].Name;
			if (sub[countSubscribers].Name == "-")
			{
				delete[] sub;
				delete[] Tariff;
				return;
			}
			if ((temp = checkName(sub[countSubscribers].Name)) == NULL)
				break;
			cout << "Введённое имя содержит недопустимый символ: " << temp << "\nПовторите попытку или отмените добавление абонента введя \"-\"\n";
		}
		while (1) //Ввод отчества
		{
			cout << "Введите отчество абонента: ";
			cin >> sub[countSubscribers].Otchestvo;
			if (sub[countSubscribers].Otchestvo == "-")
			{
				delete[] sub;
				delete[] Tariff;
				return;
			}
			if ((temp = checkName(sub[countSubscribers].Otchestvo)) == NULL)
				break;
			cout << "Введённое отчество содержит недопустимый символ: " << temp << "\nПовторите попытку или отмените добавление абонента введя \"-\"\n";
		}
		while (1) //Ввод телефонного номера абонента
		{
			cout << "Введите телефонный номер абонента: ";
			cin >> sub[countSubscribers].PhoneNumber;
			if (sub[countSubscribers].PhoneNumber == "-")
			{
				delete[] sub;
				delete[] Tariff;
				return;
			}
			if (sub[countSubscribers].PhoneNumber.size() != 13 || sub[countSubscribers].PhoneNumber[0]!='+' || sub[countSubscribers].PhoneNumber[1]!='3' || sub[countSubscribers].PhoneNumber[2]!='7' || sub[countSubscribers].PhoneNumber[3]!='5' || sub[countSubscribers].PhoneNumber[4]!='0' || sub[countSubscribers].PhoneNumber[5]!='0')
			{
				cout << "Введённый телефонный номер некорректен. Шаблон правильного номера: +37500xxxxxxx\n";
				continue;
			}
			for (i = 6; i < 13; i++)
				if (!(sub[countSubscribers].PhoneNumber[i] >= '0' && sub[countSubscribers].PhoneNumber[i] <= '9'))
					i = 14;
			if (i == 14)
				cout << "Телефонный номер должен состоять только из цифр";
			else for (i = 0; i < countSubscribers; i++)
				if (sub[countSubscribers].PhoneNumber == sub[i].PhoneNumber)
				{
					cout << "Данный телефонный номер уже занят";
					i = 14;
				}
			if (i != 14) break;
		}
		while (1) //Ввод даты
		{
			cout << "Введите дату подключения абонента в формате dd mm yy: ";
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
				cout << "Некорректный ввод. Дата вводится цифрами в формате dd mm yy\n";
				continue;
			}
			sub[countSubscribers].dayReg = day;
			sub[countSubscribers].monthReg = month;
			sub[countSubscribers].yearReg = year;
			if ((sub[countSubscribers].yearReg > 23 && sub[countSubscribers].yearReg < 50) || (sub[countSubscribers].monthReg < 1 || sub[countSubscribers].monthReg >12) || (sub[countSubscribers].dayReg<1 || sub[countSubscribers].dayReg>31))
			{
				cout << "Введённая дата некорректна. Повторите попытку или введите \"-\" для отмены добавления абонента\n";
				continue;
			}
			if (sub[countSubscribers].yearReg % 4 != 0 && sub[countSubscribers].monthReg == 2 && sub[countSubscribers].dayReg > 28)
			{
				cout << "Введённая дата некорректна. Повторите попытку или введите \"-\" для отмены добавления абонента\n";
				continue;
			}
			else if (sub[countSubscribers].yearReg % 4 == 0 && sub[countSubscribers].monthReg == 2 && sub[countSubscribers].dayReg > 29)
			{
				cout << "Введённая дата некорректна. Повторите попытку или введите \"-\" для отмены добавления абонента\n";
				continue;
			}
			else if ((sub[countSubscribers].monthReg == 4 || sub[countSubscribers].monthReg == 6 || sub[countSubscribers].monthReg == 9 || sub[countSubscribers].monthReg == 11) && sub[countSubscribers].dayReg > 30)
			{
				cout << "Введённая дата некорректна. Повторите попытку или введите \"-\" для отмены добавления абонента\n";
				continue;
			}
			break;
		}
		while (1) //Ввод тарифного плана
		{
			cout << "Введите код тарифного плана: ";
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
				cout << "Некорректный ввод. Код тарифного плана является числом и определяется администратором.\n";
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
			cout << "Введённый код не соответствует ни одному из тарифных планов. Повторите попытку или введите \"-\" для отмены добавления абонента\n";
		}
		ofstream subscribers("subscribers.txt"); //Внесение абонента в файл
		if (!subscribers.is_open())
		{
			cout << "Ошибка при открытии файла с аккаунтами пользователей\n";
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
		cout << "Ошибка при открытии файла с тарифами сотового оператора\n";
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
		while (1) //Ввод кода
		{
			cout << "Введите код тарифного плана: ";
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
				cout << "Некорректный ввод. Код тарифного плана является числом.\n";
				continue;
			}
			Tariff[countTariffs].codeTariffPlan = code;
			for (i = 0; i < countTariffs; i++)
			{
				if (Tariff[countTariffs].codeTariffPlan == Tariff[i].codeTariffPlan)
				{
					cout << "Тарифный план с данным кодом уже введён. Повторите попытку или введите \"-\" для отмены добавления тарифного плана\n";
					break;
				}
			}
			if (i != countTariffs)
				continue;
			while (1) //Ввод названия
			{
				cout << "Введите название тарифного плана\n";
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
			while (1) //Ввод стоимости
			{
				cout << "Введите стоимость тарифного плана: ";
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
					cout << "Некорректный ввод. Стоимость тарифного плана является числом и должна быть больше нуля.\n";
					continue;
				}
				if (Cost < 1)
				{
					cout << "Некорректный ввод. Стоимость тарифного плана должна быть положительной.\n";
					continue;
				}
				Tariff[countTariffs].costTariffPlan = Cost;
				break;
			}
			ofstream tariffplan("tariffplans.txt"); //Внесение тарифа в файл
			if (!tariffplan.is_open())
			{
				cout << "Ошибка при открытии файла с тарифами\n";
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
		cout << "Выберите действие: рассчитать прибыль (1), получить список абонентов (2), редактировать базу абонентов (3), выйти из системы (0)\n";
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
				cout << "Внести абонента в базу - 1\nРедактировать информацию о абоненте - 2\nУдалить абонента из базы - 3\nЗавершить редактирование - 0\n";
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
				default: printf("Некорректный ввод!\n");
					inclear();
					break;
				}
			}

			break;
		case 0:
			inclear();
			//
			return;
		default: printf("Некорректный ввод!\n");
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
		cout << "Перейти в меню пользователя - 1\nЗарегестрировать нового пользователя - 2\nРедактировать тарифные планы - 3\nВыйти из системы - 0\n";
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
				cout << "Добавить новый тарифный план - 1\nЗавершить редактирование тарифных планов - 0\n";
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
					printf("Некорректный ввод!\n");
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
			printf("Некорректный ввод!\n");
			inclear();
			break;
		}
	}
}
