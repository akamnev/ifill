#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <iostream>
#include <exception>
    
using namespace std;

struct object
{
	string value;
	string dtype;
	bool optional;
	bool assined;
	object(string _value="", string _dtype="", bool _optional=true, bool _assined=false):
		value(_value),
		dtype(_dtype),
		optional(_optional),
		assined(_assined)
	{}
};

struct getopt_data
{
	string val1;
	int val2;
	float val3;
	bool val4;
};

vector<string> opt_split(string str, string delimiter)
{
	size_t pos = 0;
	vector<string> sub_str;
	while ((pos = str.find(delimiter)) != string::npos) 
	{
		if(pos > 0)
			sub_str.push_back(str.substr(0, pos));
		str.erase(0, pos + delimiter.length());
	}
	if(str.size() > 0)
		sub_str.push_back(str);
	return sub_str;
}

inline void opt_replace(string& str)
{
	// replace '=' -> ' '
	size_t pos = 0;
	while ((pos = str.find("=")) != string::npos) 
		str.replace(pos, 1, " ");
}

inline void print_params(map<string, object>& m)
{
	cout << "getopt ";
	for(auto it =m.begin(); it != m.end(); ++it){
		string s = "--" + it->first;
		if(it->second.dtype != "bool")
			s += "=<" + it->second.dtype + ">";
		if(it->second.optional)
			s = "[" + s + "]";
		cout << s << " ";
	}
	cout << endl;
}

getopt_data Q3(string str)
{
	// если строчка начинается с пробелов, удаляем их
	while(str[0] == ' ')
		str.erase(0, 1);

	vector<string> sub_str = opt_split(str, "--");
	// map
	map<string, object> m;
	m["val1"] = object("", "string", false);
	m["val2-opt"] = object("", "int", false);
	m["val3-opt"] = object("1.0", "float");
	m["val4-bool"] = object("0", "bool");

	for(auto it = sub_str.begin(); it != sub_str.end(); ++it)
	{
		// '=' -> ' '
		opt_replace(*it);
		// split by ' '
		vector<string> s = opt_split(*it, " ");
		// chekc parameter name. it must be some value name or help
		if(s[0] == "help" && s.size() == 1){
			print_params(m);
			continue;
		}
		auto item = m.find(s[0]);
		if(item == m.end())
			throw exception();

		switch (s.size())
		{
		case 1:
			item->second.value = "1";
			item->second.assined = true;
			break;
		case 2:
			item->second.value = s[1];
			item->second.assined = true;
			break;
		default:
			break;
		}
	}
	// проверка определенности всех необходимых параметров
	bool b = true;
	for(auto it = m.begin(); it != m.end(); ++it)
		b &= it->second.assined | it->second.optional;
	if(!b) throw exception();
	// заполняем структуру данных
	getopt_data res;
	res.val1 = m["val1"].value;
	res.val2 = atoi(m["val2-opt"].value.c_str());
	res.val3 = (float)atof(m["val3-opt"].value.c_str());
	res.val4 = m["val4-bool"].value != "0";

	return res;
}

int main()
{
    cout << endl << "Question #3" << endl;
	//string getopt_in_str = "--val1 hello_world --val2-opt = 1 --val3-opt 1.23   --val4-bool --help";
	string getopt_in_str = "--val1 hello_world --val2-opt = 1 --val3-opt 1.23   ";
	cout << getopt_in_str << endl;
	getopt_data r3 = Q3(getopt_in_str);
	cout << "val1 = " << r3.val1 << " val2 = " << r3.val2 << " val3 = " << r3.val3 << " val4 = " << r3.val4 << endl;
    return 0;
}