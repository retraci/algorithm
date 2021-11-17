// POJ 2752 Seek the Name,Seek the Fame
// 即是前缀，又是后缀的各串长度 
#include <iostream>
#include <cstdio>
#include <string>
#include <stack>
using namespace std;

const int maxn = 400010;
int len;
int nxt[maxn];
string str;

void get_next() {
	int i=0,j=-1;
	nxt[0] = -1;
	while(i<len) {
		if(j>=0 && str[i]!=str[j]) {
			j = nxt[j];
		} else {
			nxt[++i] = ++j;
		}
//		cout << len;
	}
}

int main() {
	while(cin >> str) {
		len = str.length();
		get_next();
		stack<int> s;
//		for(int i=0;i<=len;i++) {
//			cout << nxt[i] << " ";
//		}

		// [ 0,nxt[len]-1 ] == [ len-nxt[len],len-1 ]
		int i=nxt[len];
		while(i>0) {
			s.push(i);
			// 在已经相同的 [ 0,nxt[len]-1 ] 里找公共前后缀 
			i = nxt[i];
		}
		
		while(!s.empty()) {
			cout << s.top() << " ";
			s.pop();
		}
		cout << len << endl;
	}
		
	return 0;
}

