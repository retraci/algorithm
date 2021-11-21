#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 33;
const ll MOD = 20211121;

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

ll n;
matrix m1, m2;

// 默认 b >= 1
matrix qsm(matrix a, ll b) {
    matrix res = a;
    b--;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }

    return res;
}

void init() {
    m1 = matrix(26, 26);
    m2 = matrix(26, 1);

    for (int i = 1; i <= 26; i++) {
        for (int j = 1; j <= i; j++) {
            m1.s[i][j] = 1;
        }
    }

    for (int i = 1; i <= 26; i++) m2.s[i][1] = 1;
}

void print(matrix &mat) {
    cout << mat.r << " " << mat.c << endl;

    for (int i = 1; i <= mat.r; i++) {
        for (int j = 1; j <= mat.c; j++) {
            cout << mat.s[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve() {
    init();

    if (n == 1){
        cout << 26 << endl;
        return;
    }

    m1 = qsm(m1, n - 1);
    matrix res = m1 * m2;
    ll ans = 0;
    for (int i = 1; i <= 26; i++) {
        ans = (ans + res.s[i][1]) % MOD;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    solve();

    return 0;
}