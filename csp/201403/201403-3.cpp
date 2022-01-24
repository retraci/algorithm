// 命令行选项 - 201403-3
/*
	
*/

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>

using namespace std;

struct cmd {
	string op, arg;
	bool operator < (const cmd &rhs) const {
		return op < rhs.op;
	}
};

const int maxn = 60;

string format;
set<cmd> ans;

int main() {
	int T;
	cin >> format >> T;
	cmd con;
	for(int i = 1; i <= T; i++) {
		ans.clear();
		string str;
		cin >> str;
		getline(cin, str);
		stringstream ss(str);
		
		while(ss >> str) {
			int pos = 0;
			if(str.length() == 2 && str[0] == '-' && ((pos = format.find(str[1])) != string::npos)) {
				con.op = str;
				if((pos+1) < format.length() && format[pos+1] == ':') {
					ss >> con.arg;
					if(con.arg == "") break;
					set<cmd>::iterator it = ans.find(con);
					if(it != ans.end()) ans.erase(it);
				} else {
					con.arg = "";
				}
				ans.insert(con);
			} else {
				break;
			}
		}
		
		printf("Case %d: ", i);
		for(set<cmd>::iterator it = ans.begin(); it != ans.end(); it++) {
			cout << (*it).op << ((*it).arg == "" ? "":" ") << (*it).arg << " ";
		}
		printf("\n");
	}

	return 0;
}
