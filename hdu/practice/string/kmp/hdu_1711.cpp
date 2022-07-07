// HDU 1711 Number Sequence 
/*
	Ë¼Â·£º
	KMP 
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

const int maxn = 1000010;

int n, m;
int a[maxn], b[maxn];
int nxt[maxn];

void get_next() {
	int i = 0, j = -1;
	nxt[0] = -1;
	while(i < n) {
		if(j == -1 || b[i]==b[j]) {
			nxt[++i] = ++j;
		} else {
			j = nxt[j];
		}
	}
}

int kmp() {
	get_next();
	int i = 0, j = 0;
	while(i < n) {
		if(j == -1 || a[i]==b[j]) {
			i++; j++;
		} else {
			j = nxt[j];
		}
		if(j == m) {
			return i-m+1;
		}
	}
	return -1;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> n >> m;
		for(int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		for(int i = 0; i < m; i++) {
			scanf("%d", &b[i]);
		}
		cout << kmp() << endl;
	}
	
	return 0;
} 
