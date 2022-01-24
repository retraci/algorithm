// 201709-3 JSON查询
/*
	思路：
	找开头的标志 
*/

#include <bits/stdc++.h>

using namespace std;

int n, m;
string str, line;
map<string, string> mp1, mp2;

string get_s(int& i) {
	i++;
	string res = "";
	while(1) {
		if(line[i] == '"') break;

		if(line[i] == '\\') {
			res.push_back(line[i+1]);
			i++;
		} else {
			res.push_back(line[i]);
		}

		i++;
	}

	return res;
}

void solve() {
	string up = "";
	string key = "", val = "";
	int len = line.length();

	for(int i = 1; i < len-1; i++) {
		if(line[i]==' ' || line[i]==',') {
			continue;
		} else if(line[i] == '}') {
			up = mp2[up];
		} else if(line[i] == '"') {
			key = get_s(i);
		} else if(line[i] == ':') {
			i++;
			while(line[i] == ' ') i++;
			
			if(line[i] == '"') {
				val = get_s(i);
				mp1[up+"."+key] = val;
			} else if(line[i] == '{') {
				mp1[up+"."+key] = "OBJECT";
				mp2[up+"."+key] = up;
				up = up+"."+key;
			}
		}
	}
	
	while(m--) {
		getline(cin, str);
		str = "."+str;
		
		if(mp1.count(str)) {
			if(mp1[str] == "OBJECT")
				cout << mp1[str] << endl;
			else
				cout << "STRING " << mp1[str] << endl;
		} else {
			cout << "NOTEXIST" << endl;
		}
	}
}

int main() {
	cin >> n >> m;
	
	getline(cin, str);
	for(int i = 0; i < n; i++) {
		getline(cin, str);
		line += str;
	}
	solve();

	return 0;
}
