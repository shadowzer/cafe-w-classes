#include "stdafx.h"
#include "headerN.h"

class Cafe
{
public:
	Menu menu;
	Checks checks;
	Kitchen kitchen;

	void start();
};

class Console
{
public:
	void printStartInfo();
	string getDate();
};

class Report
{
private:
	int reportType; // 1-4
	string date1;
	string date2;
public:
	void setReportType();
	int getReportType();
	void setDate1(string);
	string getDate1();
	void setDate2(string);
	string getDate2();
};