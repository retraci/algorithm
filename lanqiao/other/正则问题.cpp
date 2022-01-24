// 蓝桥杯 正则问题
/*
	思路：
	dfs 层次模拟 
	括号看作一个数 
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string s;
int n;
int vis[110];

int dfs(int x) {
	if(x >= n) return 0;
	// 当前层数 
	int k = 0;
	// 当前层最大值 
	int sum = 0;

	for(int i = x; i < n; i++) {
		if(s[i] == '(') {
			k++;						// 层数 + 1 
			sum += dfs(i+1);			// 下一层计数 
		} else if(s[i] == ')') {
			k--;						// 层数 - 1 
			if(k < 0) return sum;		// k < 0 意味着层数返回上一层 
		} else if(s[i] == '|') {
			sum = max(sum, dfs(i+1));	// 同个层次 | 一下 那就直接左 | 右即可 
		}  else if(s[i] == 'x' && !vis[i] && k == 0) {
			vis[i] = 1;					// 由于下一层可能会先访问过 x  
			sum++;
		}
	}

	return sum;
}

int main() {
	cin >> s;
	n = s.length();
	cout << dfs(0) << endl;

	return 0;
}
