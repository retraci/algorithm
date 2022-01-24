#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

typedef pair<int, int> PII;

const int M = 1e3 + 10, N = 1e5 + 10;
const ll MOD = 998244353;

int n, m, K;
PII va[N];
ll mp[M][M], f[M][M];

ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }

    return res;
}

ll inv(ll a, ll mod) {
    return ksm(a, mod - 2);
}

ll C(ll a, ll b) {
    ll res = 1;
    for (ll x = 1; x <= b; x++) {
        res = res * (a + 1 - x) % MOD;
        res = res * inv(x, MOD) % MOD;
    }

    return res;
}

ll calc(int x, int y) {
    return C(x + y, x);
}

void dp() {
    memset(mp, 0, sizeof mp);
    for (int i = 0; i < K; i++) {
        auto &[x, y] = va[i];
        mp[x][y] = 1;
    }

    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j]) continue;
            if (i == 1 && j == 1) f[i][j] = 1;
            else f[i][j] = (f[i - 1][j] + f[i][j - 1]) % MOD;
        }
    }
}

void solve() {
    if (n <= 1000 && m <= 1000) {
        dp();
        cout << f[n][m] << endl;
        return;
    }

    va[K++] = {n, m};
    sort(va, va + K, [&](PII &a, PII &b) { return a.first + a.second < b.first + b.second; });
    ll ans[5] = {0};
    for (int i = 0; i < K; i++) {
        auto &[x1, y1] = va[i];
        ans[i] = calc(x1 - 1, y1 - 1);

        for (int j = 0; j < i; j++) {
            auto &[x2, y2] = va[j];
            if (x1 >= x2 && y1 >= y2) {
                ans[i] -= ans[j] * calc(x1 - x2, y1 - y2) % MOD;
                ans[i] = (ans[i] + MOD) % MOD;
            }
        }
    }

    cout << ans[K - 1] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> m >> K;
    n++, m++;
    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        va[i] = {n + 1 - a, b};
    }
    solve();

    return 0;
}