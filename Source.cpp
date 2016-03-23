#include "stdafx.h"
#include "headerA.h"

void Console::printStartInfo()
{
	cout << "Введите число от 1 до 4: варианты отчетов об украденных блюдах." << endl;
	cout << "1.	За последний день (текущая дата)" << endl << "2. За определенные сутки(дата задается пользователем)" << endl;
	cout << "3. За последнюю неделю(текущая дата и 6 предшествующих дней) с детализацией по дням" << endl << "4. За заданный период(задаются даты начала и окончания) с детализацией по дням" << endl;
}

string Console::getDate()
{
	string date;
	cout << "Введите дату в формате dd.mm.yyyy" << endl;
	cin >> date;
	//while () // проверка формата даты
	//{
	//	cin >> date;
	//	if (date.size() != 10) cout << "Неверный формат даты." << endl;
	//}
	return date;
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
			cout << "Введенный аргумент не является числом." << endl;
			continue;
		}
		catch (out_of_range)
		{
			cout << "Введено неверное число. [1; 4]" << endl;
			continue;
		}
		if ((reportType != 1) && (reportType != 2) && (reportType != 3) && (reportType != 4)) cout << "Введено неверное число. [1; 4]" << endl;
	}
}

int Report::getReportType()
{
	return reportType;
}

void Report::setDate1(string date)
{
	date1 = date;
}

void Report::setDate2(string date)
{
	date2 = date;
}

string Report::getDate1()
{
	return date1;
}

string Report::getDate2()
{
	return date2;
}

void Cafe::start()
{
	Console* temp = new Console[];
	temp->printStartInfo();

	auto tmp = new Report[];
	tmp->setReportType();
	switch (tmp->getReportType)
	{
	case 1:
		// получение текущей даты
		break;
	case 2:
		tmp->setDate1(temp->getDate());
		break;
	case 3:
		// получение текущей даты и 6 дней до этого
		break;
	case 4:
		tmp->setDate1(temp->getDate());
		tmp->setDate2(temp->getDate());
		break;
	default:
		// unreachable point
		cout << "Неверный тип отчета." << endl;
		break;
	}

	delete temp;
	delete tmp;
}