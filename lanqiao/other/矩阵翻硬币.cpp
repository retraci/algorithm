// 蓝桥杯 矩阵翻硬币
/*
	思路：
	大数开方 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string n, m;

//void solve() {
//	for(int i = 1; i <= n; i++)
//		for(int j = 1; j <= m; j++)
//			G[i][j] = 1;
//
//	for(int i = 1; i <= n; i++) {
//		for(int j = 1; j <= m; j++) {
//			for(int p = 1; p <= n; p++) {
//				if(i*p > n) break;
//				for(int q = 1; q <= m; q++) {
//					if(j*q > m) break;
//					G[i*p][j*q] = !G[i*p][j*q];
//				}
//			}
//		}
//	}
//
//	int cnt = 0;
//	for(int i = 1; i <= n; i++) {
//		for(int j = 1; j <= m; j++) {
//			printf("%d ", G[i][j]);
//			if(G[i][j] == 0) cnt++;
//		}
//		cout << endl;
//	}
//	cout << cnt << endl;
//}

string mult(string s1, string s2) {
	if(s1 == "0" || s2 == "0") return "0";
	int n1 = s1.length(), n2 = s2.length();
	vector<int> num(n1+n2, 0);
	for(int i = n1-1; i >= 0; i--) {
		for(int j = n2-1; j >= 0; j--) {
			int a = s1[i] - '0';
			int b = s2[j] - '0';
			int sum = a * b + num[i+j+1];
			num[i+j+1] = sum % 10;
			num[i+j] += sum / 10;
		}
	}
	while(num.size() > 1 && num[0] == 0) {
		num.erase(num.begin());
	}
	string res;
	for(int i = 0; i < num.size(); i++) {
		res += num[i] + '0';
	}
	return res;
}

int compare(string s1, string s2, int cnt) {
	int n1 = s1.length(), n2 = s2.length();
	if(n1 > n2+cnt) {
		return 1;
	}
	else if(n1 < n2+cnt) {
		return -1;
	}
	else {
		for(int i = 0; i < n1; i++) {
			if(s1[i]-s2[i] > 0) return 1;
			else if(s1[i]-s2[i] < 0) return -1;
		}
	}
	return 1;
}

string get_sqrt(string s) {
	int n = s.length();
	int num;
	string res = "";
	if(n & 1) num = n / 2 + 1;
	else num = n / 2;
	
	// 加多一位将最后的位加上去 
	for(int i = 0; i < num+1; i++) {
		res += '0';
		for(int k = 1; k <= 9; k++) {
			res[i] = k+'0';
			int flag = compare(s, mult(res, res), 2*(num-i));
			// res > s
			if(flag == -1) {
				k--;
				res[i] = k+'0';
				break;
			}
		}
	}
	return res;
}

void solve2() {
	string x = get_sqrt(m);
//	cout << x;
	string y = get_sqrt(n);
	cout << mult(x, y) << endl;
}

int main() {
	cin >> n >> m;
	solve2();

	return 0;
}
