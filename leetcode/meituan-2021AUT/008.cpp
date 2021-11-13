#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int N = 50000 + 10;

int n, x, y;
vector<int> g[N];
int dist1[N], dist2[N];
int vis[N];

void addEdge(int a, int b) {
    g[a].push_back(b);
}

void bfs(int src, int *dist) {
    memset(vis, 0, sizeof vis);
    queue<int> que;
    que.push(src);
    int d = -1;
    while (!que.empty()) {
        int len = que.size();
        d++;
        while (len--) {
            int cur = que.front(); que.pop();
            dist[cur] = d;
            vis[cur] = 1;
            for (int i = 0; i < g[cur].size(); i++) {
                int to = g[cur][i];
                if (!vis[to]) {
                    que.push(to);
                }
            }
        }
    }
}

void solve() {
    bfs(x, dist1);
    bfs(y, dist2);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dist1[i] <= dist2[i]) continue;
        ans = max(ans, dist1[i]);
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> x >> y;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    solve();

    return 0;
}