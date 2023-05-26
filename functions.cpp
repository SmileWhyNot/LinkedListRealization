#include "functions.h"

/*�������� �� int*/
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

/*����� ��������*/
void Cout_Patient(Patient a)
{
	cout << a.surname << " " << a.name << " " << a.patronymic << endl;
	cout << a.homeAddress << " " << a.houseNumber << endl;
	cout << "Med card number: " << a.medCard << endl;
	cout << "Policy number: " << a.Policy << endl;
}

/*���� ������ � ��������*/
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

/*�������� � ����� ������*/
void Push_Back(List* const spisok, const Patient value)         // spisok - ����������� ��������� �� List           // value - �������� Patient
{
	if (spisok == NULL) // ���� �� ���� �������� ������ ��� ������ 
	{
		return;
	}
	if (spisok->count == 0) // ���� ������ ����
	{
		Node* patient = new Node; // ������ � ��������. ��������� ������
		spisok->first = patient;  // ������ � ��������� ��������� ������ �������� ����� ����������� �������
		spisok->last = patient;
		patient->info = value;    // � ���� � �������� �������� ���������� � ������� value
		patient->next = NULL;     // ��������� � ���������� ��������� �� ���������� - NULL
		patient->prev = NULL;
		spisok->count++;          // ���������� ��������� ������������� �� 1
		return;
	}//  
	else
	{
		Node* patient = new Node;
		spisok->last->next = patient; // ����� ������� - next ����� ����, ������� ��� last
		patient->prev = spisok->last; // ����� ���������� ���������� ���� ���, ������� ��� last
		spisok->last = patient;       // last ���� ����� �������
		patient->next = NULL;         // ���������� ���
		patient->info = value;
		spisok->count++;
	}
}

/*�������� � ������ ������*/
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
		spisok->first->prev = patient; // ���������� ����� ���������� ������ ��������� - ����� �������
		patient->next = spisok->first; // ��������� ����� ������������ �������� - ���������� ������ ������� (�� ���������� ������)
		spisok->first = patient; // �� ������� ������ �������� � ���������� ������� - ����� �������, ��� ������ ������� - ��� �������� ��������
		patient->prev = NULL;   // ���������� ����� ����������� �� ����������
		patient->info = value; // ���������� �������� � ������ ��������
		spisok->count++;
	}
}

/*���������� � �����*/
void Push_Center(List* const spisok)
{
	if (spisok == NULL)
		return;
	if (spisok->count == 0)
	{
		Patient value = Cin_Patient();
		Node* patient = new Node;  // ���� ����������� ������ ������� - �� ���������� ������, ���������
		spisok->first = patient;
		spisok->last = patient;
		spisok->count++;
		patient->info = value;
		patient->next = NULL;  // ����������� � ������������ �� ���������� - ��������� �� Nullptr
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
			Node* choice = spisok->first;    // ����� ����� ��������, ����� �������� ����� �������� �����
			for (int i = 1; i < number; i++)
			{
				choice = choice->next;   // ���� ������ ������� ��������
			}
			Node* patient = new Node;   // ��������� ������ ��� ������ ��������
			patient->info = value;      // � ���� � ��� �������� ������ value
			patient->next = choice->next;  // ������� �����. ��������� ����� ������ ���. - ���, ������� ��� ����. ����� choice
			choice->next->prev = patient;  // ���������� ����� choice.next - ����� ����������� �������
			patient->prev = choice;        // ���������� ����� ����� ����������� - choice
			choice->next = patient;        // ����� choice.next - ����� ����������� �������
			spisok->count++;
			return;
		}
	}
}

/*������� 1�� ��������*/
Patient Pop_Front(List* const spisok)
{
	if (spisok == NULL || spisok->count == 0) // ���� ������ ����, ��������� ���������� � ������������ �� �������
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
	if (spisok->count == 1)  // ���� ������ 1 ������
	{
		Patient result = spisok->first->info; // � ���������� result ���� Patient �������� ������ ������� ��������
		delete spisok->first;  // ��������� ������ ��� ������� 
		spisok->first = NULL;
		spisok->last = NULL;
		spisok->count--;
		return result;
	}
	else
	{
		Node* patient = spisok->first;
		spisok->first = patient->next; // ������ ������� �������� ���������� �� ���������� (�� ������ ��������� - ��������� ���������� ������)
		spisok->first->prev = NULL;  // ��������� �� ����������� ����� ������ ������ �� ���������
		Patient result = patient->info; // � ���������� result ���� Patient �������� ������ ������� �������� 
		delete patient; // ��������� ������ ��� ����� ��������
		spisok->count--;
		return result;
	}
}

/*������� ���������� ��������*/
Patient Pop_Back(List* const spisok)
{
	if (spisok == NULL || spisok->count == 0) // ���� ������ ����, ��������� ���������� � ������������ �� �������
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
	if (spisok->count == 1)  // ���� ������ 1 ������
	{
		Patient result = spisok->first->info; // � ���������� result ���� Patient �������� ������ ������� ��������
		delete spisok->first;  // ��������� ������ ��� ������� 
		spisok->first = NULL;
		spisok->last = NULL;
		spisok->count--;
		return result;
	}
	else
	{
		Node* patient = spisok->last;  // ��������� ������ ��� ���������� ��������, �������� �������
		spisok->last = patient->prev;  // ��������� ���������� ����� ������ ���� �������� �� ��������������
		spisok->last->next = NULL;     // ��������� ����� ������ ���������� ����� ������ - NULL (�� ��� �������)
		Patient result = patient->info;  // ������� ������ ������ � ��������, �������� ������� => ��������� result, ���� �������� ������
		delete patient; // ������������ ������ ��� ���������� ��������
		spisok->count--;
		return result;
	}
}

/*�������� ��������*/
Patient Pop_Center(List* const spisok)
{
	if (spisok == NULL || spisok->count == 0) // ���� ������ ����, ��������� ���������� � ������������ �� �������
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
	if (spisok->count == 1)  // ���� ������ 1 ������
	{
		Patient result = spisok->first->info; // � ���������� result ���� Patient �������� ������ ������� ��������
		delete spisok->first;  // ��������� ������ ��� ������� 
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
				patient = patient->next;         // ���� ������ �������� ��� ��������
			}
			Patient result = patient->info;      // ���-��� ���������� ���� � ��������, �������� �������
			patient->prev->next = patient->next;  // ������� ����� ����������� ����� delpatient - ��� ������� next ����� delpatient
			patient->next->prev = patient->prev; // ���������� ����� ���, ��� ����� delpat - ��� ������� ���������� ����� delpat
			patient->prev = NULL; // �� delpat ����� ������ - ��� ��������� �� ����������� � ���������� nullptr
			patient->next = NULL;
			spisok->count--;
			delete patient;  // ������������ ������
			return result;
		}
	}
}

/*������� ������*/
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

/*������� ���� ������*/
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

/*������� ���� ������*/
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

/*������� ���������� ��������� � ����*/
int GetCountOfElems(const List* const spisok)
{
	if (spisok == NULL)
		return 0;
	else
	{
		return spisok->count;
	}
}

/*�������� �������������*/
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

/*����� ���������*/
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

/*����� ���������*/
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