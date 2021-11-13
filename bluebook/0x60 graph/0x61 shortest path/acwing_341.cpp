#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int N = 100010;

int n, m;
vector<int> g1[N], g2[N];
int ps[N];
int dmin[N], dmax[N];
int st[N];

void add(vector<int> *g, int u, int v) {
    g[u].push_back(v);
}

void spfa(vector<int> *g, int *d, int s, int flag) {
    if (!flag) memset(d, 0x3f, sizeof dmin);
    else memset(d, 0, sizeof dmax);
    memset(st, 0, sizeof st);

    queue<int> que;
    que.push(s);
    d[s] = ps[s];
    st[s] = 1;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        st[u] = 0;

        for (int v: g[u]) {
            if (!flag && d[v] > min(d[u], ps[v]) || flag && d[v] < max(d[u], ps[v])) {
                if (!flag) d[v] = min(d[u], ps[v]);
                else d[v] = max(d[u], ps[v]);

                if (!st[v]) {
                    st[v] = 1;
                    que.push(v);
                }
            }
        }
    }
}

void solve() {
    spfa(g1, dmin, 1, 0);
    spfa(g2, dmax, n, 1);

//    for (int i = 1; i <= n; i++) {
//        cout << dmin[i] << " " << dmax[i] << endl;
//    }

    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, dmax[i] - dmin[i]);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> ps[i];
    while (m--) {
        int u, v, t;
        cin >> u >> v >> t;
        if (t == 1) {
            add(g1, u, v);
            add(g2, v, u);
        } else {
            add(g1, u, v), add(g1, v, u);
            add(g2, u, v), add(g2, v, u);
        }
    }
    solve();

    return 0;
}