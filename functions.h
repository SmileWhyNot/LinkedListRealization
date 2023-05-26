#pragma once

#include <stdio.h>
#include <iostream>
#include <Windows.h>
using namespace std;

struct Patient                // Данные пациента
{
	string surname;
	string name;
	string patronymic;
	string homeAddress;
	unsigned houseNumber;
	unsigned medCard;
	unsigned Policy;
};

struct Node                   // Структура записи
{
	Patient info;
	Node* next;
	Node* prev;
};

struct List                  // Структура списка
{
	Node* first;
	Node* last;
	int count;
};

int IfInt();
void Cout_Patient(Patient);
Patient Cin_Patient();
void Push_Back(List* const, const Patient);
void Push_Front(List* const, const Patient);
Patient Pop_Front(List* const);
Patient Pop_Back(List* const);
List* Create();
List* Delete(List*);
void ViewList(const List* const);
int GetCountOfElems(const List* const);
void Push_Center(List* const);
Patient Pop_Center(List* const);
void Del_Double(List* const);
void FindMax(List* const);
void FindMin(List* const);
