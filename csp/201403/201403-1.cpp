// 相反数 - 201403-1 
/*
问题描述
　　有 N 个非零且各不相同的整数。请你编一个程序求出它们中有多少对相反数(a 和 -a 为一对相反数)。
输入格式
　　第一行包含一个正整数 N。(1 ≤ N ≤ 500)。
　　第二行为 N 个用单个空格隔开的非零整数,每个数的绝对值不超过1000,保证这些整数各不相同。
输出格式
　　只输出一个整数,即这 N 个数中包含多少对相反数。
样例输入
5
1 2 3 -1 -2
样例输出
2
*/ 

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 2010;

int n, cnt[maxn];

int main() {
	scanf("%d", &n);
	
	int t, ans = 0;
	for(int i = 0; i < n; i++) {
		scanf("%d", &t);
		t += 1000;
		cnt[t]++;
	}
	for(int i = 1; i <= 1000; i++) {
		ans += min(cnt[1000+i], cnt[1000-i]);
	}
	printf("%d\n", ans);
	return 0;
}
