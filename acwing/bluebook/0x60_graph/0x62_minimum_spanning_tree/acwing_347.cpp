#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

const int N = 22;

struct Edge {
    int u, v, w;
};

int n, m, K;
unordered_map<string, int> mp;
vector<Edge> es;
int dist[N];
int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    sort(es.begin(), es.end(), [&](auto &a, auto &b) {
        return a.w < b.w;
    });
    for (int i = 1; i <= n; i++) fa[i] = i, dist[i] = 1e8;

    vector<Edge> va;
    long long ans = 0, rem = n - 1;
    for (auto &[u, v, w] : es) {
        int tx = find(u), ty = find(v);
        if (tx == ty) continue;
        if (tx > ty) swap(tx, ty);
        // 如果这条边与 1 有关, 维护dist, 最后处理
        if (tx == 1) {
            dist[ty] = min(dist[ty], w);
            continue;
        }

        // 如果2个连通块都能连到 1, 把边存一下, 最后处理
        if (dist[tx] < 1e8 && dist[ty] < 1e8) {
            va.push_back({u, v, w});
        } else {
            ans += w;
            rem--;
            dist[ty] = min(dist[tx], dist[ty]);
            fa[tx] = ty;
        }
    }

    // 把 1 跟其他连通分量连上
    for (int i = 2; i <= n; i++) {
        if (i == fa[i]) ans += dist[i];
    }

    // 处理 K 的限制
    priority_queue<int> que;
    for (auto &[u, v, w] : va) {
        int tx = find(u), ty = find(v);
        int x = w - max(dist[tx], dist[ty]);
        que.push(-x);
    }
    while (rem > K) {
        int x = que.top(); que.pop(); x = -x;
        ans += x;
        rem--;
    }
    cout << "Total miles driven: " << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> m;
    mp["Park"] = ++n;
    while (m--) {
        string su, sv;
        int w;
        cin >> su >> sv >> w;
        int u = mp.count(su) ? mp[su] : mp[su] = ++n;
        int v = mp.count(sv) ? mp[sv] : mp[sv] = ++n;
        es.push_back({u, v, w});
    }
    cin >> K;
    solve();

    return 0;
}