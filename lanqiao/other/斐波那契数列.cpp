// 斐波那契数列
/*
	利用矩阵快速幂解决
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;
typedef long long ll;

const int MOD = 1e4;

int n;

// A * B
mat mul(mat &A, mat &B) {
	mat res(A.size(), vec(B[0].size()));
	for(int i = 0; i < A.size(); i++) {
		for(int j = 0; j < B[0].size(); j++) {
			for(int k = 0; k < B.size(); k++) {
				res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % MOD;
			}
		}
	}
	return res;
}

mat pow(mat A, ll n) {
	mat res(A.size(), vec(A.size()));
	for(int i = 0; i < A.size(); i++) {
		res[i][i] = 1;
	}

	while(n) {
		if(n & 1) {
			res = mul(A, res);
		}
		A = mul(A ,A);
		n >>= 1;
	}
	return res;
}

int main() {
	n = 10;
	mat M(2, vec(2));
	mat F(2, vec(1));
	M[0][0] = 1;
	M[0][1] = 1;
	M[1][0] = 1;
	M[1][1] = 0;
	M = pow(M, n-1);
	F[0][0] = 1;
	F[1][0] = 1;
	F = mul(M, F);
	printf("%lld\n", F[1][0]);

	return 0;
}
