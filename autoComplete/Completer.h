#pragma once
#include<fstream>
#include<string>
#include<vector>
#include<exception>

using namespace std;
class Completer {
public:
	Completer();
	vector<string> giveCompletion(string, int);
	void addFrequent(string);
private:
	vector<string> words;
};


Completer::Completer()
{
	string line;
	ifstream file ("words.txt");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			this->words.push_back(line);
		}
		file.close();
	}
	else
	{
		throw exception("file did not open");
	}
}

//This function Checks if the string could be completed without change to this word
bool canComplete(string st, string word)
{
	int len = word.length();
	int size = st.length();
	if (size > len)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (word[i] != st[i])
			return false;
	}
	return true;
}
//Gives vector containing possible completions for the word for a certain limit of them
vector<string> Completer::giveCompletion(string word, int limit = INT_MAX)
{
	vector<string> res;
	int len = this->words.size();
	int count = 0;
	for (int i = 0; i < len && count < limit; i++)
	{
		string w = this->words[i];
		if (canComplete(word, w))
		{
			res.push_back(w);
			count++;
		}
	}

	return res;
}


//increase frequency of usage of certain words
void Completer::addFrequent(string word)
{
	//TODO : fill function
}