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

    matrix operator*(const matrix &that) const {
        matrix res = matrix(r, that.c);
        for (int i = 1; i <= res.r; i++) {
            for (int j = 1; j <= res.c; j++) {
                for (int k = 1; k <= c; k++) {
                    res.s[i][j] = (res.s[i][j] + s[i][k] * that.s[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }
};

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
