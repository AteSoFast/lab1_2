#include<iostream>0
#include<string>
#include<fstream>
#include<sstream>
#include<stack>
using namespace std;
//list keyword
string keyword[32] = {
	"auto","break","case","char","const","continue","default","double","do","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"
};
//variables	
int keyword_num = 0;
int switch_num = 0;
int case_num[100] = {0};
int ifelse_num = 0;
int if_elseif_else_num = 0;
int mark = 0;
//functions
int Verify(string str, string keyword1);			
void level1(string word);		
void level2(string word);		
void level34(string word);	 
int main ()
{
	string file_name;
	int level;
	string temp;
	cout << "Please enter the address of the file: ";	
	cin >> file_name;
	cout << "Please enter the level: ";
	cin >> level;
	//Read the file and input to the stream and judge which function should be used
	ifstream file(file_name.c_str(), ios::in);		
	while(getline(file, temp))	
	{
		istringstream is(temp);	
		string s;
		if(level >= 3)                    
			level34(temp);
		while(is >> s){	
			if(level >= 1)
				level1(s);
			if(level >= 2)
				level2(s);
		}
	}
//Judge which output form should be used(if level bigger than n, the level lower than n should be used)
	if(level >= 1){
		cout << endl << "total num:" << keyword_num;
	}
	if(level >= 2){
		cout << endl << "switch num:" << switch_num ;
		cout << endl << "case num:";
		for(int j = 1; j <= switch_num; j++)
			cout  << case_num[j] <<" ";
	}
	if(level >= 3){
		cout << endl << "if-else num:" << ifelse_num ;
	}
	if(level >= 4){
		cout << endl << "if-elseif-else num:" << if_elseif_else_num;
	}
}
//Define verify function to use in the future(input the keyword that should be searched later make the code more clear and easily to use and debug)
int Verify(string str, string keyword1)	
{
	int location = str.find(keyword1, 0);
	int len = keyword1.length();	
	if(location != string::npos)
		return 1;
	else
		return 0;
}
//Define every function should be used in various level and use verify function to search keyword when the keyword be searched the calculator should plus one
void level1(string word)		
{
	for(int j = 0; j < 32; j++)			
	{
		if(Verify(word, keyword[j])){
			keyword_num++;
			break;
		}
	}
}
void level2(string word)
{
	if(Verify(word, "switch") == 1)	{
		switch_num++;
	}
	if(Verify(word, "case") == 1){
		case_num[switch_num]++;
	}
}
void level34(string word)		
{
	if(Verify(word, "else if")){
		mark = 2;
	}
	else
	{
		if(Verify(word, "if")){
			mark = 1;
		}
		if(Verify(word, "else"))
		{
			if(mark == 1){
				ifelse_num++;
			}
			else	
			{
				if(mark == 2){
					if_elseif_else_num++;
				}
			}
		}
	}
}
