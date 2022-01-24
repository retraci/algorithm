#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1e5 + 10, M = 510;
const ll INF = 1e18;

int n;
ll va[N], s[N];
ll f[N][M];

void solve() {
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + va[i];

    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j < M; j++) {
            f[i][j] = -INF;
        }
    }
    for (int i = 0; i <= n + 1; i++) f[i][0] = INF;

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j < M; j++) {
            f[i][j] = f[i + 1][j];

            if (i + j - 1 > n) break;
            ll cur = s[i + j - 1] - s[i - 1];
            if (cur < f[i + j][j - 1]) f[i][j] = max(f[i][j], cur);
        }
    }

    int ans = 0;
    for (int j = 1; j < M; j++) {
        if (f[1][j] != -INF) ans = j;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}