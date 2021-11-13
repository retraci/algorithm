#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

ll n, m, K;
vector<vector<ll>> g;

void solve() {
    g = vector<vector<ll>>(n + 1, vector<ll>(m + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%lld", &g[i][j]);
        }
    }

    if (K == 1) {
        cout << *max_element(g[0].begin(), g[0].end()) << endl;
        return;
    }

    ll ans;
    if (K & 1) {
        ans = 1e9 + 7;
        for (int i = 0; i < n; i++) {
            ll mx = 0;
            for (int j = 0; j < m; j++) {
                mx = max(mx, g[i][j]);
            }
            ans = min(ans, mx);
        }
    } else {
        ans = 0;
        for (int j = 0; j < m; j++) {
            ll mi = 1e9 + 7;
            for (int i = 0; i < n; i++) {
                mi = min(mi, g[i][j]);
            }
            ans = max(ans, mi);
        }
    }

    if (g[0][0] > ans) ans = g[0][0];
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> K;
        solve();
    }

    return 0;
}