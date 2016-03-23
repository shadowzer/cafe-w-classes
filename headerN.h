#include "stdafx.h"
#include <iostream>
#include "fstream"
#include "regex"
#include <vector>
#include <string>
#include <list>
//#include "inputN.cpp"

using namespace std;

class NameWay_countSpaces
{
public:
	string name_way;
	int count_spaces;

	void parcel(string line);
};

class Position_in_menu
{
public:
	string name;
	int rubles;
	int kopecks;
	vector<string> way;

	bool parceling_line(string line);
	void clear();
};

class Position_in_kc
{
public:
	string name_dish;
	int count;

	bool parcelling_string(string line);
};

class Menu
{
private:
	list<NameWay_countSpaces> kategories_list;
public:
	list<Position_in_menu> list_position;

	vector<string> opredelenie_puti_po_strochke(string line);
	int inputMenu();
};

class Kitchen
{
public:
	list<Position_in_kc> list_k;
	int inputKitchen();
};

class OneCheck
{
public:
	int number;
	list <Position_in_kc> list_position;
	int sum_rubles;
	int sum_kopecks;

	void clear();
};

class Checks
{
public:
	list <OneCheck> list_ch;

	int inputCheck();
}; 
