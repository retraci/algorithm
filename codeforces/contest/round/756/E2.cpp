#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct Node {
    int u, t, id;
};

const int N = 2e5 + 10;

int n, m;
vector<int> g[N];
int dist[N];
int ss[N];
int vis[N];
int tag[N];

void init() {
    for (int i = 1; i <= n; i++) dist[i] = -1;
    queue<int> que;
    dist[1] = 0;
    que.push(1);
    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
}

void solve() {
    init();

    for (int i = 1; i <= n; i++) vis[i] = 1e9, tag[i] = 0;
    queue<Node> que;
    for (int i = 1; i <= m; i++) {
        vis[ss[i]] = 0;
        tag[ss[i]] = i;
        que.push({ss[i], 0, i});
    }
    while (!que.empty()) {
        auto [u, t, id] = que.front(); que.pop();

        for (int v : g[u]) {
            if (dist[v] < dist[u] && vis[v] > t + 1) {
                vis[v] = t + 1;
                tag[v] = id;
                que.push({v, t + 1, id});
            }
        }
    }

//    for (int i = 1; i <= n; i++) {
//        cout << i << " " << vis[i] << endl;
//    }
//    cout << endl;

    vis[1] = 1e9;
    unordered_set<int> st;
    que = {};
    que.push({1, 0, 0});
    while (!que.empty()) {
        auto [u, t, _] = que.front(); que.pop();
        if (vis[u] <= t) {
            st.insert(tag[u]);
            continue;
        }
        if (g[u].size() == 1 && u != 1) {
            cout << -1 << endl;
            return;
        }

        for (int v : g[u]) {
            if (dist[v] > dist[u]) {
                que.push({v, t + 1, 0});
            }
        }
    }

    cout << st.size() << endl;
}

void add(int u, int v) {
    g[u].push_back(v);
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
        cin >> n >> m;
        for (int i = 1; i <= m; i++) cin >> ss[i];
        for (int i = 1; i <= n; i++) g[i] = {};
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}