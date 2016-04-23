#include "stdafx.h"
#include "headerN.h"

class Console
{
public:
	static void printStartInfo();
	static void printInfo(string);
	static void printMenuInfo();
	static string getDate();
};

class Date
{
public:
	struct tm date;
	string dateStr;
private:
	void dateToStr();
public:
	string isDateValid(string);
	bool isPeriodValid(struct tm, struct tm);
	void swapPeriodDates(struct tm*, struct tm*);
	string dateToStr(struct tm);
	struct tm strToDate(string);
	struct tm setTodayDate();
	void setDate(struct tm);
	unsigned int countDays(struct tm, struct tm);
};

class Report
{
private:
	int reportType; // [1..4]
	struct tm date1;
	struct tm date2;
public:
	unsigned int amountDays;
	string reportPath;
public:
	void setReportType();
	int getReportType();
	void setDate1(struct tm);
	struct tm getDate1();
	void setDate2(struct tm);
	struct tm getDate2();
	void clearFile();
	void printDate(string path, string date);
};

class DayData
{
private:
	Position_in_kc* orders;
public:
	Menu menu;
	Checks checks;
	Kitchen kitchen;
	Date date;
	Report report;
	double moneyLose;
public:
	void inputData();
	int calculationOrders();
	double countLoses();
	void printLoses(string);
};

class Cafe
{
private:
	DayData* dd;
public:
	map<string, DayData*> dataThatDay;
public:
	~Cafe();
	void start();
	void theftDish();
	int callFunc(bool flag);
	int callFuncCycle(int i, bool flag);  // flag = true if вызван отчет по кражам, false if статистика по заказам
	void ordersStats();
	void printTotalStats();
	void menuChanges(string, string);
};