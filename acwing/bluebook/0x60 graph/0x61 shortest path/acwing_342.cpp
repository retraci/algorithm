#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>

using namespace std;

typedef pair<int, int> pii;

const int N = 25010;
const int INF = 0x3f3f3f3f;

int n, R, P, s;
vector<pii> g[N];
int dist[N];
int st[N];

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

void solve() {
    memset(dist, INF, sizeof dist);
    dist[s] = 0;
    deque<int> que;
    que.push_back(s);
    st[s] = 1;
    while (!que.empty()) {
        int u = que.front(); que.pop_front();
        st[u] = 0;

        for (auto &[v, w]: g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;

                if (!st[v]) {
                    st[v] = 1;
                    if (que.size() && dist[v] < dist[que.front()]) que.push_front(v);
                    else que.push_back(v);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) cout << "NO PATH" << endl;
        else cout << dist[i] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> R >> P >> s;
    while (R--) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    while (P--) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    solve();

    return 0;
}