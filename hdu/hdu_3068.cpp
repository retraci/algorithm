// HDU 3068  最长回文
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 3e5;
char s[MAXN],str[MAXN];
int len1,len2,p[MAXN],ans;

void init() {
	str[0] = '$';
	str[1] = '#';

	for(int i=0; i<len1; i++) {
		str[i*2+2] = s[i];
		str[i*2+3] = '#';
	}
	len2 = len1*2+2;
	str[len2] = '*';
}

void manacher() {
	int id=0,mx=0;

	for(int i=1; i<len2; i++) {
		if(mx>i) p[i] = min(p[2*id-i],mx-i);				// mx 内寻找对称
		else p[i] = 1;
		
		for(; str[i+p[i]]==str[i-p[i]]; p[i]++);			// 暴力匹配
		
		if(mx<i+p[i]) {										// 维护 id 与 mx
			id = i;
			mx = i+p[i];
		}
	}
}

int main() {	
	while(scanf("%s",s)!=EOF) {
		len1 = strlen(s);
		init();
		manacher();
		ans = 0;
		for(int i=0; i<len2; i++)
			ans = p[i]>ans?p[i]:ans;
		
		cout << ans-1 << endl;
	}

	return 0;
}

