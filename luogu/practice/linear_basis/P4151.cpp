#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<ll, ll> pll;

const int N = 50010;

int n, m;
vector<pll> g[N];
ll dist[N];
int vis[N];
vector<ll> bas;

void add(ll u, ll v, ll w) {
    g[u].push_back({v, w});
}

void insert(ll x) {
    for (auto b : bas) x = min(x, x ^ b);
    for (auto &b : bas) b = min(b, x ^ b);
    if (x) bas.push_back(x);
}

void dfs(int u, ll s) {
    dist[u] = s;
    vis[u] = 1;
    for (auto &[v, w] : g[u]) {
        if (vis[v]) insert(s ^ w ^ dist[v]);
        else dfs(v, s ^ w);
    }
}

void solve() {
    dfs(1, 0);
    ll ans = dist[n];
    for (auto b : bas) ans = max(ans, ans ^ b);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    while (m--) {
        ll u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    solve();

    return 0;
}