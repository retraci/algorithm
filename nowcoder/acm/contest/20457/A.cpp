#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 210;
const ll MOD = 998244353;

int n;
ll ma[N][N], mb[N][N];
ll mat[N][N];

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }

    return res;
}

ll gauss() {
    int r, c;
    for (r = 1, c = 1; c <= n; c++) {
        // 找主元
        int p = r;
        while (p <= n) {
            if (mat[p][c] != 0) break;
            p++;
        }
        // 找不着
        if (p > n) continue;
        // 交换
        for (int j = c; j <= n + 1; j++) swap(mat[r][j], mat[p][j]);

        // 消元
        for (int i = r + 1; i <= n; i++) {
            if (mat[i][c] == 0) continue;
            for (int j = n + 1; j >= c; j--) {
                mat[i][j] ^= mat[r][j];
            }
        }
        r++;
    }

    return n - r + 1;
}

void solve() {
    ll cnt = 0;
    for (int j = 1; j <= n; j++) {
        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= n; b++) {
                mat[a][b] = ma[a][b];
            }
            mat[a][a] = (ma[a][a] != mb[a][j]);
        }
        cnt += gauss();
    }

    ll ans = qpow(2, cnt);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> ma[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mb[i][j];
        }
    }
    solve();

    return 0;
}