// Lab_10_3.cpp
// < Кузів Назар >
// Лабораторна робота № 10.3
// Пошук слів у текстовому файлі
// Варіант 6

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;


struct Tovar
{
	char name[25];
	int price;
	int kilk;
	char mass[25];

};


void Create(char* fname);
void Print(char* fname);
void SearchByName(char* fname);
void SearchByPrise(char* fname);

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char fname[100]; 
	int menuItem;
	

	do {
		cout << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - ввести дані у файл" << endl;
		cout << " [2] - вивести дані на екран" << endl;
		cout << " [3] - пошук товару по назві" << endl;
		cout << " [4] - пошук товару по діапазону вартості" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
		
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть ім'я файла: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case 2:
			cin.get(); 
			cin.sync(); 
			cout << "Введіть ім'я файла: "; cin.getline(fname, sizeof(fname));
			Print(fname);
			break;
		case 3:
			cin.get();
			cin.sync();
			cout << "Введіть ім'я файла: "; cin.getline(fname, sizeof(fname));
			SearchByName(fname);
			break;
		case 4:
			cin.get();
			cin.sync();
			cout << "Введіть ім'я файла: "; cin.getline(fname, sizeof(fname));
			SearchByPrise(fname);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	return 0;

	
}
void Create(char* fname)
{
	FILE* f;
	if ((f = fopen(fname, "w")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	Tovar towar;
	char ch;
	do
	{
		cout  << endl;
		cout << " Назва : ";  cin.sync(); cin >> towar.name;
		cout << " Ціна: "; cin >> towar.price;
		cout << " Кількість: "; cin >> towar.kilk;
		cout << " Оиниця вмірювання :"; cin.sync(); cin >> towar.mass;

		if (fwrite(&towar, sizeof(Tovar), 1, f) != 1)
		{
			cerr << "Error writing file." << endl;
			return;
		}

		cout << "продовжити? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');

	fclose(f);
}
void Print(char* fname) // виведення файлу на екран
{
	FILE* f;
	if ((f = fopen(fname, "r")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	Tovar towar;

	

	while (!feof(f))
	{

		if (fread(&towar, sizeof(Tovar), 1, f) != 1)
			if (feof(f))
			{
				return;
			}

		cout << endl;
		cout << " Назва : " << towar.name<<endl;
		cout << " Ціна: " << towar.price << endl;
		cout << " Кількість: " << towar.kilk << endl;
		cout << " Оиниця вмірювання :" << towar.mass << endl;
	}


	fclose(f);
}
void SearchByName(char* fname)
{
	int be = 0;
	string Name;
	cout << "Введіть назву товару, який ви шукаєте : ";
	cin.sync();
	getline(cin, Name);


	FILE* f;
	if ((f = fopen(fname, "r")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}

	Tovar towar;
	

	while (!feof(f))
	{
		if (fread(&towar, sizeof(Tovar), 1, f) != 1)
			if (feof(f))
			{
				break;
			}
			
		if (towar.name == Name)
		{
			be++;
			cout << endl;
			cout << " Назва : " << towar.name << endl;
			cout << " Ціна: " << towar.price << endl;
			cout << " Кількість: " << towar.kilk << endl;
			cout << " Оиниця вмірювання :" << towar.mass << endl;
		}
			

		
	}
	
	if (be == 0)
	{
		cout << "Такого товару немає" << endl;
	}

	fclose(f);
}
void SearchByPrise(char* fname)
{
	int from, to;
	int be = 0;
	cout << "Введіть діапазон вартості: " << endl;
	cout << "Від: "; cin >> from;
	cout << "До: "; cin >> to;

	FILE* f;
	if ((f = fopen(fname, "r")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}

	Tovar towar;

	while (!feof(f))
	{
		if (fread(&towar, sizeof(Tovar), 1, f) != 1)
			if (feof(f))
			{
				break;
			}

		if (towar.price >= from && towar.price <= to)
		{
			cout << endl;
			cout << " Назва : " << towar.name << endl;
			cout << " Ціна: " << towar.price << endl;
			cout << " Кількість: " << towar.kilk << endl;
			cout << " Оиниця вмірювання :" << towar.mass << endl;
			cout << endl;
			be++;
			
		}

	}
	if (be == 0)
	{
		cout << "Такого товару немає" << endl;
	}
	fclose(f);
}
