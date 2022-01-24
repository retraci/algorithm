// 莞工oj ZOJ问题 
/*
	思路：
	 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	unordered_map<char, int> cnt;
	string s;
	while(cin >> s) {
		cnt.clear();
		for(char ch: s) {
			cnt[ch]++;
		}
		if(cnt['z'] != 1 || cnt['j'] != 1) {
			cout << "Wrong Answer" << endl;
			continue;
		}
		if(cnt['o'] % 4 != 1 && cnt['o'] % 2 != 1) {
			cout << "Wrong Answer" << endl;
			continue;
		}
		
		int idx1 = s.find('z');
		int idx2 = s.find('j');
		
		if(idx2 < idx1) {
			cout << "Wrong Answer" << endl;
			continue;
		}
		
		int mid = idx2 - idx1 - 1;
		printf("%d %d %d\n", idx1, idx2, mid);
		
		if(mid == 1 && idx1*2+3 == s.size()) {
			cout << "Accepted" << endl;
			continue;
		}
		if(mid == idx1+1 && idx1*4+3 == s.size()) {
			cout << "Accepted" << endl;
			continue;
		}
		cout << "Wrong Answer" << endl;
	} 
	
	return 0;
} 
