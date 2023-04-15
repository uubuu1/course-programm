#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;
void registration();
int autorisation();
void userMenu();
void adminMenu();
bool startMenu()
{
	int permission = 0;
	while (!permission)
	{
		cout << "Авторизуйтесь для входа в систему (1) или завершите сеанс (0).\n";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			permission = autorisation();
			break;
		case 0:
			return false;
		default:
			cout << "Введённое значение некорректно.";
			break;
		}
	}
	if (permission == 1) userMenu(); else adminMenu();
	return true;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while(startMenu());
	return 0;
}
