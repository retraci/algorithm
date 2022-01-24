// 区间内的素数
/*
	[a,b) 的素数最大值 小于 sqrt(b)
	所以用 [2,sqrt(b)) 来筛选 [a,b)

	由于 a，b 都很大
	is_prime 数组只存放 [a,b) 0代表 a

	思路：
	用两个数组，先筛选 [2,sqrt(2))
	再用筛选过的再次筛选
*/

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e6+1;

bool is_prime1[maxn];
bool is_prime2[maxn];

long long sieve(long long a, long long b) {
	long long res = b-a-1;

	for(int i=2; i<sqrt(b); i++) is_prime1[i] = true;
	for(int i=2; i<=b-a; i++) is_prime2[i] = true;
	
	for(int i=2; i<sqrt(b); i++) {
		if(is_prime1[i]) {
			for(int j=2*i; j<sqrt(b); j+=i) {
				if(is_prime1[j]) {
					is_prime1[j] = false;
				}
			}

			long long k = a/i+1;
			k = k>2?k:2;
			k *= i;
			for(long long j=k; j<b; j+=i) {
				if(is_prime2[j-a]) {
					is_prime2[j-a] = false;
					res--;
				}
			}
		}
	}

	return res;
}

int main() {
	long long a, b;
	a = 22801763489;
	b = 22801787297;
	cout << sieve(a,b);

	return 0;
}
