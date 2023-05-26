/*
Поиск максимального элемента. Поиск минимального. 
Список: "Пациент". ФИО. Домашний адрес. Номер мед карты. Номер страхового полиса.
Меню
Функции: Подсчет элементов. Удаление повторяющихся. Удаление списка
*/
#include "functions.h"
int main()
{
	SetConsoleCP(1251);
	List* spisok = NULL;
	bool CheckCreating = false;
	bool work = true;
	while (work)
	{
		system("cls");
		cout << "-- Choose a varient --" << endl;
		cout << "1. Create the list" << endl;
		cout << "2. Add a patient" << endl;
		cout << "3. View the list" << endl;
		cout << "4. Count of patients" << endl;
		cout << "5. Delete a patient" << endl;
		cout << "6. Delete the whole list" << endl;
		cout << "7. Delete double patients" << endl;
		cout << "8. Find max by Med Card" << endl;
		cout << "9. Find min by Med Card" << endl;
		cout << "10. Exit" << endl;
		
		switch (IfInt())
		{
		case 1: 
		{
			spisok = Create();
			CheckCreating = true;
			break;
		}
		case 2:
		{
			system("cls");
			if (!CheckCreating)
			{
				cout << "Create the List\n";
				system("pause");
				break;
			}
			Push_Center(spisok);
			break;
		}
		case 3:
		{
			system("cls");
			if (!CheckCreating)
			{
				cout << "Create the List\n";
				system("pause");
				break;
			}
			if (spisok->count > 0)
			{
				cout << "View of the list is: " << endl;
				ViewList(spisok);
			}
			else cout << "The list is empty" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			if (!CheckCreating)
			{
				cout << "Create the List\n";
				system("pause");
				break;
			}
			cout << "Count of elements in the list is " << GetCountOfElems(spisok) << endl;
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (!CheckCreating)
			{
				cout << "Create the List\n";
				system("pause");
				break;
			}
			if (spisok->count > 0)
				Cout_Patient(Pop_Center(spisok));
			else
				cout << "The list is empty" << endl;
			system("pause");
			break;
		}
		case 6:
		{
			if (!CheckCreating)
			{
				cout << "Create the List\n";
				system("pause");
				break;
			}
			spisok = Delete(spisok);
			spisok = Create();
			break;
		}
		case 7:
		{
			system("cls");
			if (!CheckCreating)
			{
				cout << "Create the List\n";
				system("pause");
				break;
			}
			if (spisok->count > 0)
			{
				Del_Double(spisok);
				ViewList(spisok);
			}
			else
				cout << "The list is empty" << endl;
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			if (!CheckCreating)
			{
				cout << "Create the List\n";
				system("pause");
				break;
			}
			if (spisok->count > 0)
				FindMax(spisok);
			else
				cout << "The list is empty" << endl;
			system("pause");
			break;
		}
		case 9:
		{
			system("cls");
			if (!CheckCreating)
			{
				cout << "Create the List\n";
				system("pause");
				break;
			}
			if (spisok->count > 0)
				FindMin(spisok);
			else
				cout << "The list is empty" << endl;
			system("pause");
			break;
		}
		case 10:
		{
			work = false;
			break;
		}
		default:
			system("cls");
			cout << "ERROR " << endl;
			system("pause");
			break;
		}
	}
	return 0;
}
/*
						 ( Бонус )
						  ／＞----フ
　　　　　				 | 　0 0  |
　 　　　					／ ミ_x 彡|
　　 　				   / 　 　    |
　　　				  /　 ヽ　　  ﾉ
　				 ／￣|　　 |　|　|
　				| (￣ ヽ＿_ヽ_)_)
　				 ＼二つ
		*/