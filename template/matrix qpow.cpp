#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 110;
const ll MOD = 1e9 + 7;

struct matrix {
    int r, c;
    ll s[N][N];

    matrix(int r = 0, int c = 0) : r(r), c(c) {
        memset(s, 0, sizeof s);
    }
};

matrix operator*(const matrix &a, const matrix &b) {
    matrix c = matrix(a.r, b.c);
    for (int i = 0; i < c.r; i++) {
        for (int j = 0; j < c.c; j++)
            for (int k = 0; k < a.c; k++)
                c.s[i][j] = (c.s[i][j] + a.s[i][k] * b.s[k][j] % MOD) % MOD;
    }
    return c;
}

// 默认 b >= 1
matrix qpow(matrix a, int b) {
    matrix res = a;
    b--;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }

    return res;
}
