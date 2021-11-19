#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

constexpr ll INF = 1e18;

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m, c;
    cin >> n >> m >> c;
    vector<vector<pair<int, int>>> g(n);
    int mip = 1e9;
    for (int i = 0; i < m; i++) {
        int u, v, p;
        cin >> u >> v >> p;
        g[--u].emplace_back(--v, p);
        mip = min(mip, p);
    }
    int tar = 0;
    vector<ll> dp(n, INF), vis(n);
    ll ans = INF;
    auto dij = [&](int tar) {
        priority_queue<pair<ll, int>> pq;
        vector<ll> d(n, INF);
        d[tar] = 0;
        pq.emplace(0, tar);
        vector<int> vis(n);
        while (!pq.empty()) {
            auto[ww, u] = pq.top();
            pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            ww = -ww;
            for (auto&[v, w]: g[u]) {
                if (v == tar) {
                    ans = min(ans, d[u] + w);
                    continue;
                }
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    pq.emplace(-d[v], v);
                }
            }
        }

    };
    for (int i = 0; i < n; i++) dij(i);

    if (c < mip) cout << 0 << "\n";
    else if (c < ans) cout << 1 << "\n";
    else cout << 2 << "\n";

    return 0;
}