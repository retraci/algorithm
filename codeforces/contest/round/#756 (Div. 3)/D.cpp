#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

int n;
int fa[N], ps[N];
int rt;
vector<int> g[N];
int dist[N];
int ans[N];

void add(int u, int v) {
    if (u == v) {
        rt = u;
        return;
    }
    g[u].push_back(v);
}

void init() {
    for (int i = 1; i <= n; i++) g[i] = {};
    for (int i = 1; i <= n; i++) add(fa[i], i);
    for (int i = 1; i <= n; i++) dist[ps[i]] = i - 1;
}

void solve() {
    init();
    queue<pii> que;
    ans[rt] = 0;
    que.push({rt, 0});
    while (!que.empty()) {
        auto [u, w] = que.front(); que.pop();

        for (auto v : g[u]) {
            ans[v] = dist[v] - w;
            if (ans[v] < 1) {
                cout << -1 << endl;
                return;
            }
            que.push({v, dist[v]});
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> fa[i];
        for (int i = 1; i <= n; i++) cin >> ps[i];
        solve();
    }

    return 0;
}