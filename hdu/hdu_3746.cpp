// HDU 3746 Cyclic Nacklace
// 循环串
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const int maxn = 100010;
string s;
int len;
int nxt[maxn];

// nxt[k]数组表示 [0,k-1]位置相同前后缀的长度 (少一个周期 
// 即s[ 0,nxt[k]-1 ] == s[ k-nxt[k],k-1 ]
// 所以 len-nxt[len] 为一个周期的长度 
void get_next() {
	int i=0,j=-1;
	nxt[0] = -1;
	while(i<len) {
		if(j>-1 && s[i] != s[j]) {
			j = nxt[j];
		} else {
			nxt[++i] = ++j;
		}
	}
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> s;
		len = s.length();
		get_next();
		int cnt = len/(len-nxt[len]);
		if(len%(len-nxt[len])==0 && nxt[len] != 0) {
			cout << 0 << endl;
		} else {
			cout << (cnt+1)*(len-nxt[len])-len << endl;
		}
	}
	return 0;
}

