#include "functions.h"

/*Проверка на int*/
int IfInt()
{
	int a;
	while (!(cin >> a))
	{
		cin.clear(); 
		while (!cin.get());
		cout << "Error. Write a number" << endl;
	}

	return a;
}

/*Вывод пациента*/
void Cout_Patient(Patient a)
{
	cout << a.surname << " " << a.name << " " << a.patronymic << endl;
	cout << a.homeAddress << " " << a.houseNumber << endl;
	cout << "Med card number: " << a.medCard << endl;
	cout << "Policy number: " << a.Policy << endl;
}

/*Ввод данных о пациенте*/
Patient Cin_Patient()
{
	Patient a;
	cout << "Write your surname: " << endl;
	cin >> a.surname;
	cout << "Write your name: " << endl;
	cin >> a.name;
	cout << "Write your patronymic: " << endl;
	cin >> a.patronymic;
	cout << "Write your home address(Panch 80): " << endl;
	cin >> a.homeAddress;
	cin >> a.houseNumber;
	cout << "Write your med card number(1111): " << endl;
	cin >> a.medCard;
	cout << "Write your policy number(2222): " << endl;
	cin >> a.Policy;
	return a;
}

/*Добавить в конец списка*/
void Push_Back(List* const spisok, const Patient value)         // spisok - константный указатель на List           // value - констата Patient
{
	if (spisok == NULL) // Если не была выделена память под список 
	{
		return;
	}
	if (spisok->count == 0) // Если список пуст
	{
		Node* patient = new Node; // Данные о пациенте. Выделение памяти
		spisok->first = patient;  // Первым и последним элементом списка является вновь добавленный элемент
		spisok->last = patient;
		patient->info = value;    // В инфо о пациенте кладется переданное в функцию value
		patient->next = NULL;     // Следующий и предыдущих элементов не существует - NULL
		patient->prev = NULL;
		spisok->count++;          // Количество пациентов увеличивается на 1
		return;
	}//  
	else
	{
		Node* patient = new Node;
		spisok->last->next = patient; // Новый пациент - next после того, который был last
		patient->prev = spisok->last; // После добавления предыдущим стал тот, который был last
		spisok->last = patient;       // last стал новый пациент
		patient->next = NULL;         // Следующего нет
		patient->info = value;
		spisok->count++;
	}
}

/*Добавить в начало списка*/
void Push_Front(List* const spisok, const Patient value)
{
	if (spisok == NULL)
		return;
	if (spisok->count == 0)
	{
		Node* patient = new Node;
		spisok->first = patient;
		spisok->last = patient;
		patient->info = value;
		patient->next = NULL;
		patient->prev = NULL;
		spisok->count++;
		return;
	}
	else
	{
		Node* patient = new Node;
		spisok->first->prev = patient; // Предыдущий перед изначально первым пациентом - новый пациент
		patient->next = spisok->first; // Следующий после добавленного пациента - изначально первый пациент (до добавления нового)
		spisok->first = patient; // Мы связали нового пациента и изначально первого - можно сказать, что первый пациент - тот которого добавили
		patient->prev = NULL;   // Предыдущий перед добавленным не существует
		patient->info = value; // Записываем значение в нового пациента
		spisok->count++;
	}
}

/*Добавление в центр*/
void Push_Center(List* const spisok)
{
	if (spisok == NULL)
		return;
	if (spisok->count == 0)
	{
		Patient value = Cin_Patient();
		Node* patient = new Node;  // Если добавляется первый пациент - он становится первым, последним
		spisok->first = patient;
		spisok->last = patient;
		spisok->count++;
		patient->info = value;
		patient->next = NULL;  // Предыдущего и последующего не существует - указываем на Nullptr
		patient->prev = NULL;
		return;
	}
	else
	{
		ViewList(spisok);
		cout << endl << "Choose an elem after which you want to add a person: " << endl;
		cout << "Write -1 to add the first" << endl;
		cout << "Write -2 to add the last" << endl;
		int number;
		cin >> number;
		if (number == -1)
		{
			Push_Front(spisok, Cin_Patient());
			return;
		}
		else if (number == -2 || number == spisok->count)
		{
			Push_Back(spisok, Cin_Patient());
			return;
		}
		else
		{
			Patient value = Cin_Patient();
			Node* choice = spisok->first;    // нужно найти пациента, после которого будет вставлен новый
			for (int i = 1; i < number; i++)
			{
				choice = choice->next;   // цикл поиска нужного пациента
			}
			Node* patient = new Node;   // выделение памяти под нового пациента
			patient->info = value;      // в инфо о нем кладутся данные value
			patient->next = choice->next;  // Процесс связи. Следующий после нового Пац. - тот, который был след. после choice
			choice->next->prev = patient;  // Предыдущий перед choice.next - вновь добавленный пациент
			patient->prev = choice;        // Предыдущий перед вновь добавленным - choice
			choice->next = patient;        // Новый choice.next - вновь добавленный пациент
			spisok->count++;
			return;
		}
	}
}

/*Удалить 1го пациента*/
Patient Pop_Front(List* const spisok)
{
	if (spisok == NULL || spisok->count == 0) // Если список пуст, структура обнуляется и возвращается на консоль
	{
		Patient t;
		t.surname = "";
		t.name = "";
		t.patronymic = "";
		t.homeAddress = "";
		t.medCard = 0;
		t.Policy = 0;
		return t;
	}
	if (spisok->count == 1)  // если только 1 запись
	{
		Patient result = spisok->first->info; // В переменную result типа Patient кладутся данные первого пациента
		delete spisok->first;  // удаляется память под первого 
		spisok->first = NULL;
		spisok->last = NULL;
		spisok->count--;
		return result;
	}
	else
	{
		Node* patient = spisok->first;
		spisok->first = patient->next; // маркер первого пациента передается на следующего (тк первый удаляется - следующий становится первым)
		spisok->first->prev = NULL;  // Указатель на предыдущего перед первым никуда не указывает
		Patient result = patient->info; // В переменную result типа Patient кладутся данные первого пациента 
		delete patient; // удаляется память под этого пациента
		spisok->count--;
		return result;
	}
}

/*Удалить последнего пациента*/
Patient Pop_Back(List* const spisok)
{
	if (spisok == NULL || spisok->count == 0) // Если список пуст, структура обнуляется и возвращается на консоль
	{
		Patient t;
		t.surname = "";
		t.name = "";
		t.patronymic = "";
		t.homeAddress = "";
		t.medCard = 0;
		t.Policy = 0;
		return t;
	}
	if (spisok->count == 1)  // если только 1 запись
	{
		Patient result = spisok->first->info; // В переменную result типа Patient кладутся данные первого пациента
		delete spisok->first;  // удаляется память под первого 
		spisok->first = NULL;
		spisok->last = NULL;
		spisok->count--;
		return result;
	}
	else
	{
		Node* patient = spisok->last;  // выделение памяти под переменную пациента, которого удаляют
		spisok->last = patient->prev;  // указатель последнего члена списка надо сместить на предпоследнего
		spisok->last->next = NULL;     // следующий после нового последнего члена списка - NULL (тк его удаляют)
		Patient result = patient->info;  // функция вернет данные о пациенте, которого удаляют => создается result, туда кладутся данные
		delete patient; // освобождение памяти под удаляемого пациента
		spisok->count--;
		return result;
	}
}

/*Удаление элемента*/
Patient Pop_Center(List* const spisok)
{
	if (spisok == NULL || spisok->count == 0) // Если список пуст, структура обнуляется и возвращается на консоль
	{
		Patient t;
		t.surname = "";
		t.name = "";
		t.patronymic = "";
		t.homeAddress = "";
		t.medCard = 0;
		t.Policy = 0;
		return t;
	}
	if (spisok->count == 1)  // если только 1 запись
	{
		Patient result = spisok->first->info; // В переменную result типа Patient кладутся данные первого пациента
		delete spisok->first;  // удаляется память под первого 
		spisok->first = NULL;
		spisok->last = NULL;
		spisok->count--;
		return result;
	}
	else
	{
		unsigned choice;
		cout << "Print the number of a patient to delete: " << endl;
		ViewList(spisok);
		cin >> choice;
		system("pause");
		system("cls");
		if (choice == 1)
		{
			Patient result;
			result = Pop_Front(spisok);
			return result;
		}
		else if (choice == spisok->count)
		{
			Patient result;
			result = Pop_Back(spisok);
			return result;
		}
		else
		{
			cout << "Erased value is ";
			Node* patient = spisok->first;
			for (unsigned i = 1; i < choice; i++)
			{
				patient = patient->next;         // цикл поиска пациента для удаления
			}
			Patient result = patient->info;      // фун-ция возвращает инфу о пациенте, которого удаляют
			patient->prev->next = patient->next;  // следующ после предыдущего перед delpatient - тот который next после delpatient
			patient->next->prev = patient->prev; // предыдущий перед тем, кот после delpat - тот который предыдущий перед delpat
			patient->prev = NULL; // тк delpat будет удален - его указатели на предыдущего и следующего nullptr
			patient->next = NULL;
			spisok->count--;
			delete patient;  // освобождение памяти
			return result;
		}
	}
}

/*Создать список*/
List* Create()
{
	List* spisok = new List;
	if (spisok == NULL)
	{
		cout << "No memmorry to create a list";
		return 0;
	}
	spisok->count = 0;
	spisok->first = NULL;
	spisok->last = NULL;
	return spisok;
}

/*Удалить весь список*/
List* Delete(List* a)
{
	if (a == NULL)
		return NULL;
	else
	{
		while (a->count != 0)
		{
			Pop_Back(a);
		}
		delete a;
		return NULL;
	}
}

/*Вывести весь список*/
void ViewList(const List* const spisok)
{
	if (spisok == NULL)
		return;
	else
	{
		Node* patient = spisok->first;
		unsigned number = 1;
		while (patient != NULL)
		{
			cout << number << ") ";
			number += 1;
			Cout_Patient(patient->info);
			patient = patient->next;
		}
	}
}

/*Вывести количество пациентов в базе*/
int GetCountOfElems(const List* const spisok)
{
	if (spisok == NULL)
		return 0;
	else
	{
		return spisok->count;
	}
}

/*Удаление повторяющихся*/
void Del_Double(List* const spisok)
{
	if (spisok->count == 0)
		cout << "List is empty"; 
	else
	{
		Node* CurClient = spisok->first;  
		while (CurClient != NULL) 
		{
			Node* temp = CurClient->next; 
			while (temp != NULL)
			{
				if ((CurClient->info.Policy == temp->info.Policy ) && (CurClient->info.medCard == temp->info.medCard))
				{
					
					if (spisok->last == temp)  // 1 2 3 2 4 2 5 6 null
					{
						spisok->last = temp->prev;
						temp->prev->next = NULL;
					}
					else
					{
						temp->next->prev = temp->prev;
						temp->prev->next = temp->next;
					}
					temp->next = temp->prev = NULL;
					delete temp;
					spisok->count--;
					break;
				}
				else
				{
					temp = temp->next;
				}
			}
			CurClient = CurClient->next; 
		}
	}
}

/*Поиск максимума*/
void FindMax(List* const spisok)
{
	Node* Finder = spisok->first;
	int maxi = Finder->info.medCard;
	while (Finder != NULL)
	{
		if (maxi < Finder->info.medCard)
		{
			maxi = Finder->info.medCard;
		}
		Finder = Finder->next;
	}
	Finder = spisok->first;
	while (Finder->info.medCard != maxi)
		Finder = Finder->next;
	Cout_Patient(Finder->info);
}

/*Поиск максимума*/
void FindMin(List* const spisok)
{
	
	Node* Finder = spisok->first;
	int mini = Finder->info.medCard;
	while (Finder != NULL)
	{
		if (mini > Finder->info.medCard)
		{
			mini = Finder->info.medCard;
		}
		Finder = Finder->next;
	}
	Finder = spisok->first;
	while (Finder->info.medCard != mini)
		Finder = Finder->next;
	Cout_Patient(Finder->info);
}