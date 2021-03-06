// 出现次数最多的数 - 201312-1
/*
	问题描述
	　　给定n个正整数，找出它们中出现次数最多的数。如果这样的数有多个，请输出其中最小的一个。
	输入格式
	　　输入的第一行只有一个正整数n(1 ≤ n ≤ 1000)，表示数字的个数。
	　　输入的第二行有n个整数s1, s2, …, sn (1 ≤ si ≤ 10000, 1 ≤ i ≤ n)。相邻的数用空格分隔。
	输出格式
	　　输出这n个次数中出现次数最多的数。如果这样的数有多个，输出其中最小的一个。
	样例输入
	6
	10 1 10 20 30 20
	样例输出
	10
*/

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 10010;

int n;
int cnt[maxn];

int main() {
	int t;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &t);
		cnt[t]++;
	}
	int ans = 0, max_num = 0;
	for(int i = 0; i < maxn; i++) {
		if(cnt[i] > max_num) {
			max_num = cnt[i];
			ans = i;
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
