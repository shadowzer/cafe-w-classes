#include "stdafx.h"
#include "headerA.h"

void Console::printStartInfo()
{
	cout << "������� ����� �� 1 �� 4: �������� ������� �� ���������� ������." << endl;
	cout << "1.	�� ��������� ���� (������� ����)" << endl << "2. �� ������������ �����(���� �������� �������������)" << endl;
	cout << "3. �� ��������� ������(������� ���� � 6 �������������� ����) � ������������ �� ����" << endl << "4. �� �������� ������(�������� ���� ������ � ���������) � ������������ �� ����" << endl;
}

string Console::getDate()
{
	string date;
	cout << "������� ���� � ������� dd.mm.yyyy" << endl;
	cin >> date;
	//while () // �������� ������� ����
	//{
	//	cin >> date;
	//	if (date.size() != 10) cout << "�������� ������ ����." << endl;
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
			cout << "��������� �������� �� �������� ������." << endl;
			continue;
		}
		catch (out_of_range)
		{
			cout << "������� �������� �����. [1; 4]" << endl;
			continue;
		}
		if ((reportType != 1) && (reportType != 2) && (reportType != 3) && (reportType != 4)) cout << "������� �������� �����. [1; 4]" << endl;
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
		// ��������� ������� ����
		break;
	case 2:
		tmp->setDate1(temp->getDate());
		break;
	case 3:
		// ��������� ������� ���� � 6 ���� �� �����
		break;
	case 4:
		tmp->setDate1(temp->getDate());
		tmp->setDate2(temp->getDate());
		break;
	default:
		// unreachable point
		cout << "�������� ��� ������." << endl;
		break;
	}

	delete temp;
	delete tmp;
}