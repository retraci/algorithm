// POJ 1704 Georgia and Bob
/*
	思路：
	如果 n 为偶数，则把相邻的棋子之间的间隔为石子数
	如果 n 为奇数，则对第一个石子单独处理
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 1010; 

int main() {
	int T, n, temp;
	int a[maxn];
	cin >> T;
	while(T--) {
		int x = 0;
		memset(a, 0, sizeof(a));
		
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		
		if(n&1) a[n++] = 0;
		sort(a, a+n);
		for(int i = 0; i < n-1; i+=2) {
			temp = a[i+1]-a[i]-1;
			x ^= temp;
		}
		
		if(x) {
			puts("Georgia will win");
		} else {
			puts("Bob will win");
		}
	}
	
	return 0;
}
