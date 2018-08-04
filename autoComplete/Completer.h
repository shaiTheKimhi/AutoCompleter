#pragma once
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<exception>

using namespace std;
class Completer {
public:
	Completer();
	vector<string> giveCompletion(string, int);
	void addFrequent(string);
private:
	map<string, int> fwords;
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
//Sperates string into vector of strings
vector<string> split(string str, char delimiter)
{
	vector<string> res;
	int len = str.length();
	string part = "";
	for (int i = 0; i < len; i++)
	{
		
		if (str[i] == delimiter)
		{
			if (part != "")
				res.push_back(part);
			part = "";
		}
		else
			part += str[i];
	}
	if(part!="")
		res.push_back(part);
	return res;
}

//increase frequency of usage of certain words
void Completer::addFrequent(string word)
{
	ofstream file;
	//loading dictionary of words by frequency key
	map<string, int> wordsDict;
	ifstream infile("fwords.txt");
	string line;
	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			vector<string> parts = split(line, ':');
			wordsDict.insert(pair<string, int>(parts[0], stoi(parts[1])));
		}
		infile.close();
	}
	file.open("fwords.txt");
	map<string, int>::iterator it = wordsDict.find(word);
	if (it != wordsDict.end())
		it->second++;
	else
		wordsDict.insert(pair<string, int>(word, 1));

	//Write map to file
	for (map<string, int>::iterator i = wordsDict.begin(); i != wordsDict.end(); i++)
	{
		file << i->first << ":" << i->second << endl;
	}
	file.close();
	

	
}