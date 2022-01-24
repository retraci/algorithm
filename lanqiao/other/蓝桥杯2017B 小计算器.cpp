// 蓝桥杯2017B 小计算器 
/*
	思路：
	转 10 进制运算
	转 k 进制输出 
*/

#include <bits/stdc++.h>

using namespace std;

int base = 10;
long long num;

void print() {
	if(base == 10) {
		cout << num << endl;
		return;
	}
	if(num == 0) {
		cout << 0 << endl;
		return;
	}
	
	long long x = num;
	string s;
	while(x) {
		int cur = x % base;
		if(cur <= 9) {
			s.push_back(cur+'0');
		} else {
			s.push_back(cur-10+'A');
		}
		x /= base;
	}
	
	for(int i = s.size()-1; i >= 0; i--) {
		cout << s[i];
	}
	cout << endl;
}

long long get_num() {
	string s;
	cin >> s;
	long long res = 0;
	for(int i = 0; i < s.size(); i++) {
		long long temp;
		if(s[i]>='0' && s[i]<='9') temp = s[i]-'0';
		else temp = s[i]-'A'+10;
		res *= base;
		res += temp;
	}
	return res;
}

int main() {
	string op = "";
	int opi = 0;
	int n;
	cin >> n;
	
	while(n--) {
		cin >> op;
		if(op == "CLEAR") num = opi = 0;
		else if(op == "EQUAL") print();
		else if(op == "ADD") opi = 1;
		else if(op == "SUB") opi = 2;
		else if(op == "MUL") opi = 3;
		else if(op == "DIV") opi = 4;
		else if(op == "MOD") opi = 5;
		else if(op == "CHANGE") cin >> base;
		else if(op == "NUM") {
			if(opi == 0) num = get_num();
			else if(opi == 1) num += get_num();
			else if(opi == 2) num -= get_num();
			else if(opi == 3) num *= get_num();
			else if(opi == 4) num /= get_num();
			else if(opi == 5) num %= get_num();
		}
		//cout << num << endl;
	}
	
	return 0;
} 
