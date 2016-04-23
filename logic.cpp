#include "stdafx.h"
#include "headerA.h"


string Date::isDateValid(string _date)
{
	bool isValid = false;
	while (!isValid)
	{
		if ((_date.size() != 10) || (!isdigit(_date[0])) || (!isdigit(_date[1])) || (!isdigit(_date[2])) || (!isdigit(_date[3])) || (!isdigit(_date[5])) || (!isdigit(_date[6])) || (!isdigit(_date[8])) || (!isdigit(_date[9])) || (_date[4] != '-') || (_date[7] != '-'))
		{
			cout << "Ќеверный формат даты. Ќеобходимый формат: yyyy-mm-dd" << endl;
			cin >> _date;
			continue;
		}
		if ((stoi(_date.substr(5, 2)) < 1) || (stoi(_date.substr(5, 2)) > 12))
		{
			cout << "Ќеверно указан мес€ц. ћес€ц может находитьс€ только в диапазоне [1, 12]." << endl;
			cin >> _date;
			continue;
		}
		if ((stoi(_date.substr(8, 2)) < 1) || (stoi(_date.substr(8, 2)) > 31))
		{
			cout << "Ќеверно указан день. ƒень может находитьс€ только в диапазоне [1, 31]." << endl;
			cin >> _date;
			continue;
		}
		isValid = true;
	}
	return _date;
}

bool Date::isPeriodValid(struct tm date1, struct tm date2)
{
	if (date1.tm_year > date2.tm_year) return false;
	if (date1.tm_year < date2.tm_year) return true;
	if (date1.tm_mon > date2.tm_mon) return false;
	if (date1.tm_mon > date2.tm_mon) return true;
	if (date1.tm_mday > date2.tm_mday) return false;
	return true;
}

void Date::swapPeriodDates(struct tm* date1, struct tm* date2)
{
	struct tm temp;
	temp = *date1;
	date1 = date2;
	*date2 = temp;
}

void Date::dateToStr()
{
	string answer = to_string(date.tm_year + 1900) + "-";
	if (date.tm_mon < 9)
		answer += "0" + to_string(date.tm_mon + 1) + "-";
	else answer += to_string(date.tm_mon + 1) + "-";
	if (date.tm_mday < 10)
		answer += "0" + to_string(date.tm_mday);
	else answer += to_string(date.tm_mday);
	dateStr = answer;
}

string Date::dateToStr(struct tm date1)
{
	string answer = to_string(date1.tm_year + 1900) + "-";
	if (date1.tm_mon < 9)
		answer += "0" + to_string(date1.tm_mon + 1) + "-";
	else answer += to_string(date1.tm_mon + 1) + "-";
	if (date1.tm_mday < 10)
		answer += "0" + to_string(date1.tm_mday);
	else answer += to_string(date1.tm_mday);
	return answer;
}

struct tm Date::strToDate(string strDate)
{  // 2016-03-26
	struct tm tmp;
	tmp.tm_year = stoi(strDate.substr(0, 4)) - 1900;
	tmp.tm_mon = stoi(strDate.substr(5, 2)) - 1;
	tmp.tm_mday = stoi(strDate.substr(8, 2));
	return tmp;
}

struct tm Date::setTodayDate()
{
	time_t t = time(0);   // get time now
	setDate(*localtime(&t));
	return date;
}

void Date::setDate(struct tm _date)
{
	date = _date;
	dateToStr();
}

unsigned int Date::countDays(struct tm date1, struct tm date2)
{
	char buffer[11], buffer2[11];
	string buf, buf2;
	struct tm currentDate = date1;
	strftime(buffer, 11, "%Y-%m-%d", &date1);
	strftime(buffer2, 11, "%Y-%m-%d", &date2);
	buf = buffer;
	buf2 = buffer2;
	unsigned int countDays = 1;
	while (buf.compare(buf2))
	{
		++countDays;
		currentDate.tm_mday += 1;
		mktime(&currentDate);
		strftime(buffer, 11, "%Y-%m-%d", &currentDate);
		buf = buffer;
	}
	return countDays;
}



int Report::getReportType()
{
	return reportType;
}

void Report::setDate1(struct tm date)
{
	date1 = date;
}

void Report::setDate2(struct tm date)
{
	date2 = date;
}

struct tm Report::getDate1()
{
	return date1;
}

struct tm Report::getDate2()
{
	return date2;
}

void Report::clearFile()
{
	ofstream file;
	file.open(reportPath);
	file.clear();
	file.close();
}



int DayData::calculationOrders()
{
	if (menu.map_menu.size()) orders = new Position_in_kc[menu.map_menu.size()];
	else return 50;  // ошибка пустого меню
	unsigned int i = 0;
	auto it = menu.map_menu.begin();
	while (it != menu.map_menu.end())  // заполнение меню(блюдо_кол-во сделанного/оплаченного)
	{
		orders[i].posInMen.name = it->first;
		orders[i++].count = 0;
		++it;
	}

	auto it1 = kitchen.list_k.begin();
	while (it1 != kitchen.list_k.end())  // в массив добавл€ем блюда, сделанные на кухне
	{
		i = 0;
		while ((i < menu.map_menu.size()) && (it1->posInMen.name.compare(orders[i].posInMen.name)))
		{
			++i;
		}
		if (i != menu.map_menu.size()) orders[i].count += it1->count;
		++it1;
	}

	auto it2 = checks.list_ch.begin();
	while (it2 != checks.list_ch.end())  // в массиве вычитаем блюда, оплаченные по чеку
	{
		unsigned int i = 0;
		it1 = it2->list_position.begin();
		while (it1 != it2->list_position.end())
		{
			i = 0;
			while ((i < menu.map_menu.size()) && (it1->posInMen.name.compare(orders[i].posInMen.name)))
			{
				++i;
			}
			if (i < menu.map_menu.size()) orders[i].count -= it1->count;
			++it1;
		}
		++it2;
	}
	return 0;
}

double DayData::countLoses()
{
	moneyLose = 0;
	for (unsigned int i = 0; i < menu.map_menu.size(); i++)
	{
		if (!orders[i].count) continue;
		if (orders[i].count > 0)
		{
			moneyLose += orders[i].count * menu.map_menu[orders[i].posInMen.name].price;
			continue;
		}
		moneyLose += orders[i].count * (-1) * menu.map_menu[orders[i].posInMen.name].price;
	}
	return moneyLose;
}



double Checks::getSum()
{
	return sum;
}

int Checks::getCountChecks()
{
	return count_checks;
}

void Checks::report_dish_count(Node root, int spaces, string path)
{
	map <string, int> dishCount = dish_count();
	ofstream file(path, ofstream::app);
	node_out(root, dishCount, 0, &file);
}

void Checks::node_out(Node node, map <string, int> dishCount, int spacers, ofstream* file)
{
	Node nodetmp;
	string spases;

	for (int i = 0; i < spacers; i++)
	{
		spases = spases + " ";
	}


	for (auto it : node.list_pos)
	{
		printInFile(spases + it.name + " заказано:       \t" + to_string(dishCount[it.name]), file);
	}
	for (auto it : node.list_nodes)
	{

		nodetmp.countSpaces = it.countSpaces;
		nodetmp.list_nodes = it.list_nodes;
		nodetmp.list_pos = it.list_pos;
		nodetmp.name = it.name;
		printInFile(spases + nodetmp.name, file);
		node_out(nodetmp, dishCount, spacers + 3, file);
	}
}



void Cafe::theftDish()
{
	DayData tmp;
	tmp.report.setReportType();
	switch (tmp.report.getReportType())
	{
	case 1:  // за сегодн€
		dd = new DayData[1];
		dd->date.setTodayDate();

		callFunc(true);
		break;
	case 2:  // за выбранную дату
		dd = new DayData[1];
		dd->date.setDate(dd->date.strToDate(Console::getDate()));

		callFunc(true);
		break;
	case 3:
		// получение текущей даты и 6 дней до этого
		dd = new DayData[7];
		dd[6].date.setTodayDate();
		dd->report.reportPath = "reports\\theftWeekBefore" + dd->date.dateStr + ".txt";
		dd->report.clearFile();

		for (int i = 5; i >= 0; --i)
		{
			dd[i].date.setTodayDate();
			dd[i].date.date.tm_mday -= (6 - i);
			callFuncCycle(i, true);
		}
		break;
	case 4:
		tmp.report.setDate1(tmp.date.strToDate(Console::getDate())); // начало периода
		tmp.report.setDate2(tmp.date.strToDate(Console::getDate())); // конец периода
		if (!tmp.date.isPeriodValid(tmp.report.getDate1(), tmp.report.getDate2()))  // проверка правильности ввода периода
		{
			struct tm temp = tmp.report.getDate2();
			tmp.report.setDate2(tmp.report.getDate1());
			tmp.report.setDate1(temp);
		}
		tmp.report.amountDays = tmp.date.countDays(tmp.report.getDate1(), tmp.report.getDate2());
		dd = new DayData[tmp.report.amountDays];

		dd->report.reportPath = "reports\\theftPeriod" + dd->date.dateToStr(tmp.report.getDate1()) + "--" + dd->date.dateToStr(tmp.report.getDate2()) + ".txt";
		dd->report.clearFile();

		for (unsigned int i = 0; i < tmp.report.amountDays; ++i)
		{
			dd[i].date.setDate(tmp.report.getDate1());
			dd[i].date.date.tm_mday += i;
			callFuncCycle(i, true);
		}
		break;
	default:
		// unreachable point
		cout << "Ќеверный тип отчета." << endl;
		break;
	}
}

int Cafe::callFunc(bool flag)
{
	if (flag)
	{
		dd->inputData();

		dd->report.reportPath = "reports\\theft" + dd->date.dateStr + ".txt";
		dd->report.clearFile();

		if (dd->calculationOrders() == 50)
		{
			cout << "ќшибка: пустое меню за " << dd->date.dateStr << ". «аполните меню и перезапустите программу." << endl;
			return 50;
		}
		dd->countLoses();

		dd->report.printDate(dd->report.reportPath, dd->date.dateStr);
		dd->printLoses(dd->report.reportPath);
		dataThatDay[dd->date.dateStr] = dd;
	}
	else
	{
		dd->inputData();

		dd->report.reportPath = "reports\\ordersStats" + dd->date.dateStr + ".txt";
		dd->report.clearFile();

		dd->checks.report_dish_count(dd->menu.root, 0, dd->report.reportPath);
		printTotalStats();
		dataThatDay[dd->date.dateStr] = dd;
	}
	return 0;
}

int Cafe::callFuncCycle(int i, bool flag)
{
	char buffer[11];
	if (flag)
	{
		mktime(&dd[i].date.date);
		strftime(buffer, 11, "%Y-%m-%d", &dd[i].date.date);
		dd[i].date.dateStr = buffer;
		dd[i].inputData();
		if (dd[i].calculationOrders() == 50)
		{
			cout << "ќшибка: пустое меню за " << dd[i].date.dateStr << ". «аполните меню и перезапустите программу." << endl;
			return 50;
		}
		dd[i].countLoses();

		dd->report.printDate(dd->report.reportPath, dd[i].date.dateStr);
		dd[i].printLoses(dd->report.reportPath);
		dataThatDay[buffer] = dd;
	}
	else
	{
		mktime(&dd[i].date.date);
		strftime(buffer, 11, "%Y-%m-%d", &dd[i].date.date);
		dd[i].date.dateStr = buffer;
		dd[i].inputData();

		dd->report.printDate(dd->report.reportPath, dd[i].date.dateStr);
		dd->checks.report_dish_count(dd->menu.root, 0, dd->report.reportPath);
		printTotalStats();
		dataThatDay[dd[i].date.dateStr] = dd;
	}
	return 0;
}

void Cafe::ordersStats()
{
	// о сумме выручки, о количестве заказов, о величине среднего чека (средн€€ сумма заказа за указанный период), о количестве заказанных блюд -  
	// по категори€м и подкатегори€м (с учетом вложенности) с детализацией до каждого наименовани€ блюда
	ofstream file;
	DayData tmp;
	tmp.report.setReportType();
	switch (tmp.report.getReportType())
	{
	case 1:  // за сегодн€
		dd = new DayData[1];
		dd->date.setTodayDate();
		callFunc(false);
		break;
	case 2:  // за указанное число
		dd = new DayData[1];
		dd->date.setDate(dd->date.strToDate(Console::getDate()));
		callFunc(false);
		break;
	case 3:
		// получение текущей даты и 6 дней до этого
		dd = new DayData[7];
		dd[6].date.setTodayDate();

		dd->report.reportPath = "reports\\ordersStatsWeekBefore" + dd->date.dateStr + ".txt";
		dd->report.clearFile();

		for (int i = 5; i >= 0; --i)
		{
			dd[i].date.setTodayDate();
			dd[i].date.date.tm_mday -= (6 - i);
			callFuncCycle(i, false);
		}
		break;
	case 4:  // за период
		tmp.report.setDate1(tmp.date.strToDate(Console::getDate())); // начало периода
		tmp.report.setDate2(tmp.date.strToDate(Console::getDate())); // конец периода
		if (!tmp.date.isPeriodValid(tmp.report.getDate1(), tmp.report.getDate2()))  // проверка правильности ввода периода
		{
			struct tm temp = tmp.report.getDate2();
			tmp.report.setDate2(tmp.report.getDate1());
			tmp.report.setDate1(temp);
		}
		tmp.report.amountDays = tmp.date.countDays(tmp.report.getDate1(), tmp.report.getDate2());
		dd = new DayData[tmp.report.amountDays];

		dd->report.reportPath = "reports\\ordersStatsPeriod" + dd->date.dateToStr(tmp.report.getDate1()) + "--" + dd->date.dateToStr(tmp.report.getDate2()) + ".txt";
		dd->report.clearFile();
		for (unsigned int i = 0; i < tmp.report.amountDays; ++i)
		{
			dd[i].date.setDate(tmp.report.getDate1());
			dd[i].date.date.tm_mday += i;
			callFuncCycle(i, false);
		}
		break;
	default:
		// unreachable point
		cout << "Ќеверный тип отчета." << endl;
		break;
	}
}

void Cafe::menuChanges(string date2, string date1)
{
	ofstream file("reports\\menuChanges" + date1 + "--" + date2 + ".txt");
	Menu menu1, menu2;
	menu1.inputMenu(date1);
	menu2.inputMenu(date2);
	vector<string> dishNotFound;
	vector<string> newDish;
	for (auto it1 = menu1.map_menu.begin(); it1 != menu1.map_menu.end(); ++it1)
	{
		auto it2 = menu2.map_menu.begin();
		while ((it2 != menu2.map_menu.end()) && (it1->first != it2->first))
		{
			++it2;
		}
		if (it2 == menu2.map_menu.end())
		{
			dishNotFound.push_back(it1->first);
			continue;
		}
		if (it1->second.price == it2->second.price)
		{
			menu2.printSamePrice(&file, it1->first);
			continue;
		}
		if (it1->second.price > it2->second.price) menu2.printPriceReduce(&file, it1, it2);
		else menu2.printPriceIncrease(&file, it1, it2);
	}
	for (auto it2 = menu2.map_menu.begin(); it2 != menu2.map_menu.end(); ++it2)
	{
		auto it = menu1.map_menu.begin();
		while ((it != menu1.map_menu.end()) && (it->first != it2->first))
		{
			++it;
		}
		if (it == menu1.map_menu.end()) newDish.push_back(it2->first);
	}
	menu2.printDishChanges(&file, dishNotFound, newDish);
	file.close();
}

void Cafe::start()
{
	Report temp;
	Console::printStartInfo();

	temp.setReportType();
	switch (temp.getReportType())
	{
	case 1:
		Console::printInfo("об украденных блюдах.");
		theftDish();
		break;
	case 2:
		Console::printInfo("по статистике заказов.");
		ordersStats();
		break;
	case 3:
		Console::printMenuInfo();
		menuChanges(Console::getDate(), Console::getDate());
		break;
	default:
		break;
	}
}

Cafe::~Cafe()
{
	delete[] dd;
}



EveningDiscount::EveningDiscount()
{
	name = "Evening discount";
	size = 10;
}

bool EveningDiscount::applicable(OneCheck check)
{
	if ((check.hours > hours) || ((check.hours == hours) && (check.minutes >= minutes)))
	{
		return 1;
	}
	return 0;
};

void EveningDiscount::calculate(OneCheck check)
{

}

DayDishDiscount::DayDishDiscount()
{
	name = "Dish of the day discount";
}

bool DayDishDiscount::applicable()
{

}

void DayDishDiscount::calculate()
{

}

BDayDiscount::BDayDiscount()
{
	name = "Birthday discount";
	size = 20;
	addTag("именинник");
}

bool BDayDiscount::applicable()
{

}

void BDayDiscount::calculate()
{

}

LuxuryOrderDiscount::LuxuryOrderDiscount()
{
	name = "Luxury order discount";
	addCondition(5, 1500);
	addCondition(6, 2500);
	addCondition(8, 8000);
}

bool LuxuryOrderDiscount::applicable(OneCheck check)
{
	if (check.sum > condition.begin()->first) return true;
	else return false;
}

void LuxuryOrderDiscount::calculate()
{

}

