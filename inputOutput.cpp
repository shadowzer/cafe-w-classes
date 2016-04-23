#include "stdafx.h"
#include "headerA.h"


void Console::printStartInfo()
{
	cout << "������� ����� �� 1 �� 4: ��� ������������ ������." << endl;
	cout << "1. ����� �� ���������� ������." << "2. ����� �� ���������� �������." << endl;
	cout << "3. ����� �� ���������� � ����." << "4. ����� �� ���������." << endl;
}

void Console::printInfo(string variant)
{
	cout << "������� ����� �� 1 �� 4: �������� ������� " << variant << endl;
	cout << "1.	�� ��������� ���� (������� ����)" << endl << "2. �� ������������ �����(���� �������� �������������)" << endl;
	cout << "3. �� ��������� ������(������� ���� � 6 �������������� ����) � ������������ �� ����" << endl << "4. �� �������� ������(�������� ���� ������ � ���������) � ������������ �� ����" << endl;
}

void Console::printMenuInfo()
{
	cout << "������� 2 ����, �� ������� ����� �������� ����." << endl;
}

string Console::getDate()
{
	string _date;
	cout << "������� ���� � ������� yyyy-mm-dd" << endl;
	cin >> _date;
	Date date;
	return date.isDateValid(_date);
}



void Report::setReportType()
{
	string line;
	reportType = 0;
	while ((reportType != 1) && (reportType != 2) && (reportType != 3) && (reportType != 4))
	{
		cin >> line;
		try
		{
			reportType = stoi(line);
		}
		catch (invalid_argument)
		{
			cout << "��������� �������� �� �������� ������. ��������� ������� �����." << endl;
			continue;
		}
		catch (out_of_range)
		{
			cout << "������� �������� �����. �������� ���������� ��������[1; 4]. ��������� ������� �����." << endl;
			continue;
		}
		if ((reportType != 1) && (reportType != 2) && (reportType != 3) && (reportType != 4)) cout << "������� �������� �����. �������� ���������� ��������[1; 4]. ��������� ������� �����." << endl;
	}
}

void Report::printDate(string path, string date)
{
	ofstream file(path, ofstream::app);
	file << date << endl << endl;
	file.close();
}



void DayData::inputData()
{
	menu.inputMenu(date.dateStr);
	kitchen.inputKitchen(date.dateStr, menu);
	checks.inputCheck(date.dateStr, menu);
}

void DayData::printLoses(string path)
{
	ofstream file(path, ofstream::app);
	for (unsigned int i = 0; i < menu.map_menu.size(); i++)
	{
		if (!orders[i].count) continue;
		if (orders[i].count > 0)
		{
			file << "����� '" << orders[i].posInMen.name << "' ������� �� ���� �� " << orders[i].count << " ������ ������, ��� ������� �� �����. ������ = " << orders[i].count * menu.map_menu[orders[i].posInMen.name].price << " ���." << endl;
			continue;
		}
		file << "����� '" << orders[i].posInMen.name << "' ������� �� ���� �� " << (-1) * orders[i].count << " ������ ������, ��� ������� �� �����. ������ = " << orders[i].count * (-1) * menu.map_menu[orders[i].posInMen.name].price << " ���." << endl;
	}
	if (moneyLose) file << "\n\n����� ������ = " << moneyLose << " ���." << endl;
	else file << "����� �� ����." << endl;
	file << "============================" << endl;
	file.close();
	delete[] orders;
}



void Menu::printPriceReduce(ofstream* file, map <string, Position_in_menu>::iterator it1, map <string, Position_in_menu>::iterator it2)
{
	*file << "����� " << it1->first << " ���������� �� " << it1->second.price - it2->second.price << " ������(" << ((it1->second.price - it2->second.price) / it1->second.price) * 100 << "%)" << endl;
}

void Menu::printPriceIncrease(ofstream* file, map <string, Position_in_menu>::iterator it1, map <string, Position_in_menu>::iterator it2)
{
	*file << "����� " << it1->first << " ���������� �� " << it2->second.price - it1->second.price << " ������(" << ((it2->second.price - it1->second.price) / it2->second.price) * 100 << "%)" << endl;
}

void Menu::printSamePrice(ofstream *file, string dishName)
{
	*file << "�� ����� " << dishName << " ���� �������� �� ��." << endl;
}

void Menu::printDishChanges(ofstream* file, vector<string> dishNotFound, vector<string> newDish)
{
	for (auto it = dishNotFound.begin(); it != dishNotFound.end(); ++it)
	{
		*file << "����� " << *it << " ������ �� ����." << endl;
	}
	for (auto it = newDish.begin(); it != newDish.end(); ++it)
	{
		*file << "����� " << *it << " ��������� � ����." << endl;
	}
}



void Cafe::printTotalStats()
{
	ofstream file(dd->report.reportPath, ofstream::app);  // ���������
	file << "���������� �����: " << dd->checks.getCountChecks() << endl << "����� �������: " << dd->checks.getSum() << endl << "������� ��� = " << dd->checks.getSum() / dd->checks.getCountChecks() << endl;
	file << "============================================" << endl << endl;
	file.close();
}



void NameWay_countSpaces::parcel(string line)
{
	count_spaces = line.find_first_not_of(" ");
	name_way = line.substr(line.find_first_not_of(" "));
}

bool Position_in_menu::parceling_line(string line)  //0����� 1�� �����
{
	regex tmpRegex("\\s*(.+?)[\\s=]+(\\d+)[,\\.](\\d{2})[\\s*(\\d)%\\s*]*");
	smatch match;
	if (!regex_search(line, match, tmpRegex)) return 1;
	// � �����:
	//����(0) ��� ������
	//����(1) ��������
	//����(2) ����� 
	//����(3) �������
	name = match.str(1);
	rubles = stoi(match.str(2));
	kopecks = stoi(match.str(3));
	if (match.str(4) != "")
	{
		percent = stoi(match.str(4));
	}
	price = (double)rubles + (double)kopecks / 100;
	return 0;
}

void Position_in_menu::clear()
{
	name = "";
	rubles = 0;
	kopecks = 0;
	way.clear();
}

bool Position_in_kc::parcelling_string(string line, Menu m)  //0 success 1 fail
{
	regex tmpRegex("\\s*(.+?)[\\s=]+(\\d+)\\s*");
	smatch match;
	if (!regex_search(line, match, tmpRegex)) return 1;
	// � �����:
	//����(0) ��� ������
	//����(1) ��������
	//����(2) ���������� 
	posInMen = m.map_menu[match.str(1)];
	count = stoi(match.str(2));

	return 0;
}


vector<string> Menu::opredelenie_puti_po_strochke(string line)
{
	int count_spaces = line.find_first_not_of(" ");
	list<NameWay_countSpaces>::iterator iter;
	vector<string> way;
	if (!count_spaces)
	{
		kategories_list.clear();
		return way;
	}
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

int Menu::inputMenu(string date)
{
	std::list<Node>::iterator it;
	NameWay_countSpaces tmpNameCategoryCountSpaces;
	Node tmpNode;
	root.countSpaces = 0;
	root.root = NULL;
	Node* current = &root;
	string name_dish;
	name_dish = "menu" + date + ".txt";
	ifstream fin(name_dish);
	Position_in_menu positionTmp;
	if (!fin.is_open())//���� ���� ��� ���� 
	{
		cout << "File " << name_dish << " is not found." << endl;
		system("pause");
		exit(-1);
	}
	while (!fin.eof())//������ �������
	{
		getline(fin, name_dish);
		positionTmp.clear();
		if (!(positionTmp.parceling_line(name_dish)))//0-parcelling success 1-not success
		{
			while ((name_dish.find_first_not_of(" ") <= current->countSpaces) && (current->root != NULL))
			{
				current = current->root;
			}
			current->list_pos.push_front(positionTmp);

			map_menu[positionTmp.name] = positionTmp;
			continue;
		}
		//���� ������� �� ���� �������� ����...
		regex tmpRegex("\\s*.+\\s*");
		smatch match;
		if (!regex_search(name_dish, match, tmpRegex)) return 10;  //������ �10:������ � ���� �� �������� ��� �������� �� ��������� �� ����� ����
		// ���� ������ �o������ ��� �������� ���������
		tmpNameCategoryCountSpaces.parcel(name_dish);
		tmpNode.countSpaces = tmpNameCategoryCountSpaces.count_spaces;
		tmpNode.name = tmpNameCategoryCountSpaces.name_way;
		tmpNode.root = current;

		while ((tmpNode.countSpaces <= current->countSpaces) && (current->root != NULL))
		{
			current = current->root;
		}

		current->list_nodes.push_front(tmpNode);
		it = current->list_nodes.begin();
		current = &(*it);
	}
}



void Kitchen::inputKitchen(string data, Menu menu)
{
	string line;
	ifstream fin;
	Position_in_kc one_pos;
	line = "kitchen" + data + ".txt";
	fin.open(line);
	if (!fin.is_open())
	{
		cout << "File " << line << " is not found." << endl;
		system("pause");
		exit(-1);
	}
	while (!fin.eof())
	{
		getline(fin, line);
		if (one_pos.parcelling_string(line, menu))
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

void Checks::inputCheck(string data, Menu menu)
{
	Discount* saleTmp;
	count_checks = 0;
	sum = 0;
	string line;
	Position_in_kc positionTmp;
	OneCheck tmpCheck;
	line = "check" + data + ".txt";
	ifstream fin(line);
	if (!fin.is_open())
	{
		cout << "File " << line << " is not found." << endl;
		system("pause");
		exit(-1);
	}
	tmpCheck.clear();
	while (!fin.eof())
	{
		getline(fin, line);
		regex tmpRegex(".+�\\s*([0-9]+)\\s+([0-9]+):([0-9]+)");
		smatch match;
		if (regex_search(line, match, tmpRegex))
		{
			tmpCheck.number = stoi(match.str(1));
			tmpCheck.hours = stoi(match.str(2));
			tmpCheck.minutes = stoi(match.str(3));
			continue;
		}
		tmpRegex = "�����:\\s*([0-9]+)[.,]([0-9]+)";
		if (regex_search(line, match, tmpRegex))
		{
			tmpCheck.sum_rubles = stoi(match.str(1));
			tmpCheck.sum_kopecks = stoi(match.str(2));
			tmpCheck.sum = (double)tmpCheck.sum_rubles + ((double)tmpCheck.sum_kopecks / 100);
			continue;
		}
		if (!positionTmp.parcelling_string(line, menu))  //0 success 1 fail
		{
			tmpCheck.list_position.push_back(positionTmp);
			continue;
		}

		if (line.find("======") == -1)
		{
			cout << "error in line:" << endl << line << endl << "can't read" << endl;
			exit(-1);
		}
		saleTmp = new EveningDiscount;
		if (saleTmp->applicable(tmpCheck))
		{

		}

		list_ch.push_back(tmpCheck);
		count_checks++;
		sum = sum + tmpCheck.sum;
		tmpCheck.clear();
	}
}


map <string, int> Checks::dish_count()
{
	map <string, int> dishCount;
	int count = 0;
	for (auto it : list_ch)
	for (auto iter : it.list_position)
	{
		if (dishCount.find(iter.posInMen.name) == dishCount.end())
		{
			dishCount[iter.posInMen.name] = iter.count;
			continue;
		}

		count = dishCount[iter.posInMen.name];
		dishCount[iter.posInMen.name] = iter.count + count;

	}
	return dishCount;
}

void Checks::printInFile(string line, std::ofstream* file)
{
	*file << line << endl;
}

void EveningDiscount::setTime()
{
	cout << "������� �����, ����� ������� ���������� ����� �������� �������� ������." << endl;
	string Tmp;
	cin >> Tmp;
	regex tmpRegex("(\\d+)[:](\\d+)");
	smatch match;
	bool flag = regex_search(Tmp, match, tmpRegex);
	while (!flag)
	{
		cout << "Incorrent input" << endl;
		cin >> Tmp;
		if (flag = regex_search(Tmp, match, tmpRegex))
		{
			hours = stoi(match.str(1));
			minutes = stoi(match.str(2));
			if (hours < 24 && minutes < 60)
			{
				flag = 1;
			}
			else
			{
				flag = 0;
			}
		}

	}
}

void LuxuryOrderDiscount::addCondition(double price, int discSize)
{
	condition[price] = discSize;
}

void LuxuryOrderDiscount::removeCondition(double price) // �� ����
{
	condition.erase(price);
}

void LuxuryOrderDiscount::removeCondition(int discSize) // �� ������� ������
{
	auto it = condition.begin();
	while (it->second != discSize)
	{
		++it;
	}
	condition.erase(it);
}