#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int N = 1010;

int n, m, K;
vector<pii> g[N];
int dist[N];
int vis[N];

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

bool check(int mid) {
    memset(dist, 0x3f, sizeof dist), memset(vis, 0, sizeof vis);
    dist[1] = 0;
    priority_queue<pii> que;
    que.push({0, 1});
    while (!que.empty()) {
        auto [d, u] = que.top(); que.pop(); d = -d;
        if (vis[u]) continue;
        vis[u] = 1;

        for (auto &[v, w]: g[u]) {
            int nd = d + (w > mid);
            if (dist[v] > nd) {
                dist[v] = nd;
                que.push({-dist[v], v});
            }
        }
    }

    return dist[n] <= K;
}

void solve() {
    int left = 0, right = 1000001;
    while (left < right) {
        int mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

    cout << (left == 1000001 ? -1 : left) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> K;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    solve();

    return 0;
}