// HDU 1358 period
// 字符串周期
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

const int maxn = 1e6+10;
string s;
int n;
int nxt[maxn];

// 下标表示长度
// 第二个周期才会开始累加
void get_next() {
	int i=0,j=-1;
	nxt[0] = -1;
	while(i<n) {
		if(j!=-1 && s[i]!=s[j]) j = nxt[j];
		else nxt[++i] = ++j;
	}
}

int main() {
	int tot = 1;
	while(cin >> n) {
		if(n == 0) break;
		cin >> s;
		get_next();
//		cout << endl;
//		for(int i=0;i<=n;i++)
//			cout << nxt[i] << " ";
//		cout << endl << endl ;
		cout << "Test case #" << tot++ << endl;
		for(int len = 2; len<=n; len++) {
			// len-nxt[len] 去掉了除第一个周期之外的，结果就是第一个周期的长度
			if(nxt[len] > 0 && (len % (len-nxt[len])) == 0) {
				cout << len << " " << len/(len-nxt[len]) << endl;
			}
		}
		cout << endl;
	}
	return 0;
}

