#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int maxk = 55;
const int MOD = 20211114;

struct matrix {
    int r, c;
    ll s[maxk][maxk];

    matrix(int r = 0, int c = 0) : r(r), c(c) {
        memset(s, 0, sizeof s);
    }
};

ll n, k;

matrix xi;
matrix f;

matrix operator*(const matrix &a, const matrix &b) {
    matrix c = matrix(a.r, b.c);
    for (int i = 0; i < c.r; i++) {
        for (int j = 0; j < c.c; j++) {
            for (int k = 0; k < a.c; k++) {
                c.s[i][j] += a.s[i][k] * b.s[k][j];
            }
            c.s[i][j] %= MOD;
        }
    }
    return c;
}

matrix power(matrix a, ll b) {
    matrix res = a;
    b--;
    while (b) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void init() {
    xi = matrix(k, k);

    for (int i = 0; i < k; i++) {
        xi.s[0][i] = 1;
    }
    for (int i = 1; i < k; i++) {
        xi.s[i][i - 1] = 1;
    }
}

void print() {
    for (int i = 0; i < f.c; i++) {
        for (int j = 0; j < f.r; j++) {
            cout << f.s[i][j] << " ";
        }
        cout << endl;
    }
}

void solve() {
    init();
    f = matrix(k, 1);
    f.s[0][0] = 1;

    xi = power(xi, n);
    f = xi * f;

    cout << f.s[0][0] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    solve();

    return 0;
}