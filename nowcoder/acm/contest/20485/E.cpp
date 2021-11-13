#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 51;
const ll MOD = 1e9 + 7;

struct matrix {
    int r, c;
    ll s[N][N];

    matrix(int r = 0, int c = 0) : r(r), c(c) {
        memset(s, 0, sizeof s);
    }
};

int n, x, m;
ll va[N];
matrix xi1, xi2, xi, ma;

matrix operator*(const matrix &a, const matrix &b) {
    matrix c = matrix(a.r, b.c);
    for (int i = 0; i < c.r; i++) {
        for (int j = 0; j < c.c; j++)
            for (int k = 0; k < a.c; k++)
                c.s[i][j] = (c.s[i][j] + a.s[i][k] * b.s[k][j] % MOD) % MOD;
    }
    return c;
}

matrix power(matrix a, int b) {
    matrix res = a;
    b--;
    for (; b; b >>= 1) {
        if (b & 1)
            res = res * a;
        a = a * a;
    }
    return res;
}

void print(matrix &tt) {
    for (int i = 0; i < tt.r; i++) {
        for (int j = 0; j < tt.c; j++) {
            cout << tt.s[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void init() {
    xi1 = matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            xi1.s[i][j] = 1;
        }
    }

    xi2 = matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            xi2.s[i][j] = 1;
        }
    }

    xi = xi1 * xi2;
}

void solve() {
    init();

    int k = m / x + 1;

    int c = k / 2, rem = k & 1;
    sort(va, va + n, greater<>());
    ma = matrix(1, n);
    for (int i = 0; i < n; i++) ma.s[0][i] = va[i];

    if (c > 0) ma = ma * power(xi, c);
    if (rem) {
        ma = ma * xi1;
        cout << ma.s[0][n - 1] << endl;
    } else {
        cout << ma.s[0][0] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> x >> m;
        for (int i = 0; i < n; i++) {
            cin >> va[i];
        }
        solve();
    }

    return 0;
}