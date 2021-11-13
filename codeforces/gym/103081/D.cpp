#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

const int N = 100010;

typedef pair<int, int> pii;

struct Node {
    int v, w, id;
};

int n, m, L, R;
vector<Node> g[N];
int dist[N];
int st[N];

void add(int u, int v, int w, int id) {
    g[u].push_back({v, w, id});
}

void solve() {
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;
    queue<int> que;
    que.push(0);
    st[0] = 1;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        st[u] = 0;

        for (auto &[v, w, _]: g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!st[v]) {
                    que.push(v);
                    st[v] = 1;
                }
            }
        }
    }

    unordered_set<int> es;
    for (int i = 0; i < n; i++) {
        if (dist[i] * 2 < R) {
            for (auto &[v, w, id]: g[i]) {
                es.insert(id);
            }
        }
    }

    cout << es.size() << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> L >> R;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w, m), add(v, u, w, m);
    }
    solve();

    return 0;
}