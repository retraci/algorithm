// 神奇的排序
/*

*/

#include <bits/stdc++.h>

using namespace std;

string str;

int main() {
	cin >> str;
	
	int pos = 0;
	for(int k = 0; k < 4; k++) {
		for(int i = pos; i < str.size(); i++) {
			if(str[i] == 'a'+k) {
				swap(str[i], str[pos++]);
			}
		}
	}
	
	cout << str << endl;
	
	return 0;
}
