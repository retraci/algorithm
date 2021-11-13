#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

int n, m;
vector<int> ds[N];
vector<int> ps[N];
vector<int> g[N];
int du[N];
int dist[N];

void add(int u, int v) {
//    cout << u << " " << v << endl;

    g[u].push_back(v);
    du[v]++;
}

void solve() {
    for (int i = 1; i <= m; i++) {
        for (int p : ds[i]) ps[p].push_back(i);
    }

    for (int i = 1; i <= 1e5; i++) {
        if (ps[i].empty()) continue;

        int last = ps[i][0];
        for (int j = 1; j < ps[i].size(); j++) {
            int cur = ps[i][j];
            add(last, cur);
            last = cur;
        }
    }

    queue<int> que;
    for (int i = 1; i <= m; i++) {
        if (du[i] == 0) {
            dist[i] = 1;
            que.push(i);
        }
    }
    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (int v : g[u]) {
            if (--du[v] == 0) {
                dist[v] = max(dist[v], dist[u] + 1);
                que.push(v);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) ans = max(ans, dist[i]);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        while (k--) {
            int p;
            cin >> p;
            ds[i].push_back(p);
        }
    }
    solve();

    return 0;
}