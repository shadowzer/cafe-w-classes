#include "stdafx.h"
#include "headerA.h"

void NameWay_countSpaces::parcel(string line)
{
	count_spaces = line.find_first_not_of(" ");
	name_way = line.substr(line.find_first_not_of(" "));
}

bool Position_in_menu::parceling_line(string line)  //0успех 1не успех
{
	regex tmpRegex("\\s*(.+?)[\\s=]+(\\d+)[,\\.](\\d{2})");
	smatch match;
	if (!regex_search(line, match, tmpRegex)) return 1;
	// в матче:
	//матч(0) вся строка
	//матч(1) название
	//матч(2) рубли 
	//матч(3) копейки
	name = match.str(1);
	rubles = stoi(match.str(2));
	kopecks = stoi(match.str(3));
	cout << match.str(0) << endl;
	cout << match.str(1) << endl;
	cout << match.str(2) << endl;
	cout << match.str(3) << endl;
	return 0;
}

void Position_in_menu::clear()
{
	name = "";
	rubles = 0;
	kopecks = 0;
	way.clear();
}

bool Position_in_kc::parcelling_string(string line)  //0 success 1 fail
{
	regex tmpRegex("\\s*(.+?)[\\s=]+?(\\d+)\\s*");
	smatch match;
	if (!regex_search(line, match, tmpRegex)) return 1;
	// в матче:
	//матч(0) вся строка
	//матч(1) название
	//матч(2) количество 
	name_dish = match.str(1);
	count = stoi(match.str(2));
	return 0;
}


vector<string> Menu::opredelenie_puti_po_strochke(string line)
{
	int count_spaces = line.find_first_not_of(" ");
	list<NameWay_countSpaces>::iterator iter;
	vector<string> way;
	way.clear();
	iter = kategories_list.end();
	--iter;
	while (count_spaces <= iter->count_spaces)
	{
		iter--;
		kategories_list.pop_back();
	}
	for (iter = kategories_list.begin(); iter != kategories_list.end(); ++iter)
	{
		way.push_back(iter->name_way);
	}
	return way;
}

int Menu::inputMenu()
{
	NameWay_countSpaces tmpWay;
	vector<string> way_now;
	bool flag;  //парсельнулась ли строчка?
	Position_in_menu positionTmp;
	string name_dish;
	int count;
	double price;
	cout << "Enter name of 'menu' file." << endl;
	cin >> name_dish;
	ifstream fin(name_dish);
	if (!fin.is_open())
	{
		cout << "menu file is not found." << endl;
		system("pause");
		exit(-1);
	}
	while (!fin.eof())//чтение менюшки
	{
		getline(fin, name_dish);
		positionTmp.clear();
		flag = positionTmp.parceling_line(name_dish);  //0успех 1не успех
		if (!flag)
		{
			positionTmp.way = opredelenie_puti_po_strochke(name_dish);
			list_position.push_back(positionTmp);
			continue;
		}
		//если строчка не вида название цена...
		regex tmpRegex("\\s*.+\\s*");
		smatch match;
		if (!regex_search(name_dish, match, tmpRegex)) return 10;  //ОШИБКА №10:СТРОКА В МЕНЮ НЕ ПОДХОДИТ ПОД ОПИСАНИЕ НИ КАТЕГОРИИ НИ БЛЮДО ЦЕНА
		// если строка пoдходит под описание категории
		tmpWay.parcel(name_dish);
		list <NameWay_countSpaces>::iterator iter = kategories_list.end();
		if (kategories_list.size() > 0)
		{
			iter--;
			while ((kategories_list.size() > 0) && (tmpWay.count_spaces <= iter->count_spaces))
			{
				if (kategories_list.size() > 1)
				{
					iter--;
				}
				kategories_list.pop_back();
			}
			kategories_list.push_back(tmpWay);
		}
		else
		{
			kategories_list.push_back(tmpWay);
		}
	}
}


int Kitchen::inputKitchen()
{
	string line;
	ifstream fin;
	Position_in_kc one_pos;
	cout << "Enter name of 'kitchen' file." << endl;
	cin >> line;
	fin.open(line);
	if (!fin.is_open())
	{
		cout << "Kitchen file is not found." << endl;
		system("pause");
		exit(-1);
	}
	while (!fin.eof())
	{
		getline(fin, line);
		if (one_pos.parcelling_string(line))
		{
			cout << "error in line:" << line << endl;
			exit(-1);
		}
		else                                                      //0success 1 fail
			list_k.push_back(one_pos);
	}
}

void OneCheck::clear()
	{
		number = 0;
		list_position.clear();
		sum_kopecks = 0;
		sum_rubles = 0;
	}

int Checks::inputCheck()
{
	string line;
	Position_in_kc positionTmp;
	OneCheck tmpCheck;
	cout << "Enter name of 'check' file." << endl;
	cin >> line;
	ifstream fin(line);
	if (!fin.is_open())
	{
		cout << "Check file is not found." << endl;
		system("pause");
		exit(-1);
	}
	tmpCheck.clear();
	while (!fin.eof())
	{
		getline(fin, line);
		regex tmpRegex(".+№\\s*([0-9]+)\\s*");
		smatch match;
		if (regex_search(line, match, tmpRegex))
		{
			tmpCheck.number = stoi(match.str(1));
			continue;
		}
		tmpRegex = "итого:\\s*([0-9]+)[.,]([0-9]+)";
		if (regex_search(line, match, tmpRegex))
		{
			tmpCheck.sum_rubles = stoi(match.str(1));
			tmpCheck.sum_kopecks = stoi(match.str(2));
			continue;
		}
		if (!positionTmp.parcelling_string(line))  //0 success 1 fail
		{
			tmpCheck.list_position.push_back(positionTmp);
			continue;
		}

		if (line.find("======") == -1)
		{
			cout << "error in line:" << endl << line << endl << "can't read" << endl;
			exit(-1);
		}
			list_ch.push_back(tmpCheck);
			tmpCheck.clear();
	}
}
