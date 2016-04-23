#include "stdafx.h"
#include <iostream>
#include "fstream"
#include "regex"
#include <vector>
#include <string>
#include <list>
#include <map>


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
private:
	int rubles;
	int kopecks;
	int percent;
public:
	string name;
	double price;
	vector<string> way;

	bool parceling_line(string line);
	void clear();
};



class Node
{
public:
	int countSpaces;

	list<Position_in_menu> list_pos;
	list<Node> list_nodes;

	Node* root;
	string name;
};

class Menu
{
private:
	list<NameWay_countSpaces> kategories_list;
public:
	Node root;
	map <string, Position_in_menu> map_menu;
public:
	vector<string> opredelenie_puti_po_strochke(string line);
	int inputMenu(string data);
	void printPriceReduce(ofstream* file, map <string, Position_in_menu>::iterator it1, map <string, Position_in_menu>::iterator it2);
	void printPriceIncrease(ofstream* file, map <string, Position_in_menu>::iterator it1, map <string, Position_in_menu>::iterator it2);
	void printSamePrice(ofstream* file, string dishName);
	void printDishChanges(ofstream* file, vector<string> dishNotFound, vector<string> newDish);
};

class Position_in_kc//:public Position_in_menu
{
public:
	Position_in_menu posInMen;
	int count;

	bool parcelling_string(string line, Menu m);
};

class Kitchen
{
public:
	list<Position_in_kc> list_k;
public:
	void inputKitchen(string data, Menu menu);
};

class OneCheck
{
public:
	int number;
	int minutes;
	int hours;
	list <Position_in_kc> list_position;
	double sum;
	int sum_rubles;
	int sum_kopecks;

public:
	void clear();
};

class Discount
{
public:
	string name;
	int size;
public:
	virtual void calculate(OneCheck check) = 0;
	virtual bool applicable(OneCheck check) = 0;
};

class DayDishDiscount : public Discount
{
public:
	map<string, int> dishDisc;
public:
	DayDishDiscount();
	virtual void calculate();
	virtual bool applicable();
};

class EveningDiscount : public Discount
{
private:
	int hours;
	int minutes;
public:
	EveningDiscount();
	void setTime();
	virtual void calculate(OneCheck check);
	virtual bool applicable(OneCheck check);
};

class BDayDiscount : public Discount
{
public:
	vector<string> tag;
public:
	BDayDiscount();
	void addTag(string);
	void removeTag();
	virtual void calculate();
	virtual bool applicable();
};

class LuxuryOrderDiscount : public Discount
{
public:
	map<double, int> condition;
public:
	LuxuryOrderDiscount();
	void addCondition(double, int);
	void removeCondition(double); // по цене
	void removeCondition(int); // по размеру скидки
	virtual void calculate();
	virtual bool applicable(OneCheck check);
};

class Checks
{
private:
	double sum;
	int count_checks;

public:
	list <OneCheck> list_ch;
	void inputCheck(string data, Menu menu);
	double getSum();
	int getCountChecks();
	map <string, int> dish_count();
	void report_dish_count(Node root, int spaces, string path);
	void node_out(Node node, map <string, int> dishCount, int spacers, ofstream* file);
	void printInFile(string line, std::ofstream* file);
};


class Sales
{
public:
	vector<Discount*> disc;
public:
	string choseOptimum();
};