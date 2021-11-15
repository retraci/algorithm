#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int N = 50010;

int n;
int va[N], vb[N], vc[N];
vector<pii> g[N];
int dist[N];
int st[N];

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

void spfa() {
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;
    queue<int> que;
    que.push(0);
    st[0] = 1;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        st[u] = 0;

        for (auto &[v, w] : g[u]) {
            if (dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!st[v]) {
                    que.push(v);
                    st[v] = 1;
                }
            }
        }
    }
}

void solve() {
    for (int i = 1; i <= 50001; i++) add(i - 1, i, 0), add(i, i - 1, -1);
    for (int i = 1; i <= n; i++) add(va[i] - 1, vb[i], vc[i]);

    spfa();
    cout << dist[50001] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a++, b++;
        va[i] = a, vb[i] = b, vc[i] = c;
    }
    solve();

    return 0;
}