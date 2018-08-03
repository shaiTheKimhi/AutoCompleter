#include<iostream>
#include "Completer.h"
#include<vector>
#include<string>
#include<Windows.h>

using namespace std;
int main(void)
{
	//getting starting program time(milisecnods)
	SYSTEMTIME time;
	GetSystemTime(&time);
	long start = (time.wSecond * 1000) + time.wMilliseconds;

	Completer c;
	vector<string> s = c.giveCompletion("angel");
	for (int i = 0; i < s.size(); i++)
		cout << s[i] << endl;
	
	GetSystemTime(&time);
	long end = (time.wSecond * 1000) + time.wMilliseconds;
	cout << "process time: " + to_string(end - start) << endl;
	system("PAUSE");
	return 0;
}