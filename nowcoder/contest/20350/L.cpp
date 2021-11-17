#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int N = 1e5 + 10;

int n, m, q;
int w[N];
vector<int> g[N];
vector<int> nodes[110];
int dist[110][N];
int vis[N];

template<typename T> inline void rd(T& x){
    T ret = 0, sgn = 1;
    char c = getchar();
    while(!isdigit(c)) sgn = (c == '-' ? -1 : 1), c = getchar();
    while(isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
    x = (sgn == -1 ? -ret : ret);
}

void add(int a, int b) {
    g[a].push_back(b);
}

void solve() {
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < n; i++) {
        nodes[w[i]].push_back(i);
    }

    for (int i = 1; i <= 100; i++) {
        memset(vis, 0, sizeof vis);
        for (int j = 0; j < n; j++) dist[i][j] = dist[i - 1][j];

        queue<pair<int, int>> que;
        for (auto &vk : nodes[i]) {
            que.push({vk, 0});
            dist[i][vk] = 0;
        }

        while (!que.empty()) {
            auto cur = que.front(); que.pop();
            if (vis[cur.first] == 1) continue;
            vis[cur.first] = 1;

            for (auto &to : g[cur.first]) {
                if (!vis[to] && dist[i][to] > cur.second + 1) {
                    dist[i][to] = cur.second + 1;
                    que.push({to, cur.second + 1});
                }
            }
        }
    }

    while (q--) {
        int a, b;
        rd(a), rd(b);
        a--;
        printf("%d\n", dist[b][a] == 0x3f3f3f3f ? -1 : dist[b][a]);
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    rd(n); rd(m); rd(q);
    for (int i = 0; i < n; i++) rd(w[i]);
    for (int i = 0; i < m; i++) {
        int a, b;
        rd(a); rd(b);
        a--, b--;
        add(a, b);
        add(b, a);
    }
    solve();

    return 0;
}
