// 素数的个数
/*
	判断 n 之内有多少个素数

	埃氏筛法
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath> 

using namespace std;

const int maxn = 1e6+1;

bool is_prime[maxn];

int sieve(int n) {
	int res = n-1;
	for(int i=2; i<=n; i++) is_prime[i] = true;
	
	for(int i=2; i<=sqrt(n); i++) {
		for(int j=2*i; j<=n; j+=i) {
			if(is_prime[j]) {
				is_prime[j] = false;
				res--;
			}
		}
	}
	return res;
}

int main() {
	int n;
	n = 1e6;
	cout << sieve(n) << endl;
//	for(int i=2; i<=n; i++) if(is_prime[i])printf("%d ", i);

	return 0;
}
