#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int val, id;
    bool operator< (const Node &that) const {
        return val < that.val;
    }
};

const int N = 1e5 + 10;

int n;
vector<int> g[N];
Node va[N];
int vis[N];
int fa[N];
vector<int> g2[N];
int ans[N];

void add(int u, int v) {
    g[u].push_back(v);
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    sort(va + 1, va + n + 1);
    for (int i = 1; i <= n; i++) vis[i] = 0, fa[i] = i;
    for (int i = 1; i <= n; i++) g2[i].clear();
    for (int i = 1; i <= n; i++) {
        int id = va[i].id;
        vis[id] = 1;
        for (int son : g[id]) {
            if (vis[son]) {
                int tx = find(son);
                g2[id].push_back(tx);
                fa[tx] = id;
            }
        }
    }

    for (int i = 1; i <= n; i++) ans[i] = -1;
    queue<int> que;
    que.push(va[n].id);
    int layer = 0;
    while (!que.empty()) {
        int sz = que.size();
        layer++;
        for (int i = 0; i < sz; i++) {
            int cur = que.front(); que.pop();
            ans[cur] = layer;
            for (int son : g2[cur]) {
                que.push(son);
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
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
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            add(a, b); add(b, a);
        }
        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;
            va[i] = {a, i};
        }
        solve();
    }

    return 0;
}