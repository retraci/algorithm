#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 1010, M = 20010, C = 110;

struct Node {
    int u, y, w;
    bool operator<(const Node &rhs) const {
        return w > rhs.w;
    }
};

int n, m;
int ps[N];
vector<pii> g[N];

int dist[N][C];
int vis[N][C];

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

int dij(int cap, int st, int ed) {
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0, sizeof vis);

    priority_queue<Node> que;
    dist[st][0] = 0;
    que.push({st, 0, 0});
    while (!que.empty()) {
        auto [u, y, w] = que.top(); que.pop();
        if (vis[u][y]) continue;
        vis[u][y] = 1;
        if (u == ed) return w;

//        cout << u << " " << y << "\n";

        // 加油
        if (y + 1 <= cap && dist[u][y + 1] > w + ps[u]) {
            int ny = y + 1, nw = w + ps[u];
            dist[u][ny] = nw;
            que.push({u, ny, nw});
        }
        // 跑路
        for (auto &[v, cost] : g[u]) {
            if (y >= cost) {
                int ny = y - cost;
                if (dist[v][ny] > dist[u][y]) {
                    dist[v][ny] = dist[u][y];
                    que.push({v, ny, w});
                }
            }
        }
    }

    return -1;
}

void solve() {
    int q;
    cin >> q;
    while (q--) {
        int cap, st, ed;
        cin >> cap >> st >> ed; st++, ed++;
        int ans = dij(cap, st, ed);
        if (ans == -1) cout << "impossible" << "\n";
        else cout << ans << "\n";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> ps[i];
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w; u++, v++;
        add(u, v, w), add(v, u, w);
    }
    solve();

    return 0;
}