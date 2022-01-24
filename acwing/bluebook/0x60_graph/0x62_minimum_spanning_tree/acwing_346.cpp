#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct Edge {
    int u, v, w;
};

const int N = 12010;

int n;
vector<Edge> es;
int fa[N], sz[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    sort(es.begin(), es.end(), [&](auto &a, auto &b) {
        return a.w < b.w;
    });

    long long ans = 0;
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
    for (auto &[u, v, w]: es) {
        int tx = find(u), ty = find(v);
        if (tx == ty) continue;

        ans += 1LL * (w + 1) * (sz[tx] * sz[ty] - 1);

        fa[tx] = ty;
        sz[ty] += sz[tx];
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        es = {};
        for (int i = 0; i < n - 1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            es.push_back({u, v, w});
        }
        solve();
    }

    return 0;
}