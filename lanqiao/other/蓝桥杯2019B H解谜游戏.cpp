// 蓝桥杯2019B H解谜游戏
/*
	思路：
	规律 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	string s1, s2, s3;
	map<char, int> cnt;
	while(T--) {
		int flag = 0;
		cin >> s1 >> s2 >> s3;
		for(int i = 0; i < 4; i++) {
			cnt.clear();
			cnt[s1[i]]++;
			cnt[s1[i+4]]++;
			cnt[s1[i+8]]++;
			cnt[s2[i]]++;
			cnt[s2[i+4]]++;
			cnt[s3[i]]++;
			if(!(cnt['G'] == 3 && cnt['R'] == 2 && cnt['Y'] == 1)) flag = 1; 
		}
		if(flag) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
	
	return 0;
}
