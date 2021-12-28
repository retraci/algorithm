#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2e5 + 10;

ll n, K;
vector<int> g[N];
int fa[N];
int dep[N];
int vis[N];
int vc[N];

void add(int u, int v) {
    g[u].push_back(v);
}

void dfs(int u, int fno, int depth) {
    dep[u] = depth; fa[u] = fno;
    for (int v : g[u]) {
        if (v == fno) continue;
        dfs(v, u, depth + 1);
    }
}

void work(int u) {
    int &c = vc[u];
    while (!vis[u] && u != 0) {
        vis[u] = 1;
        u = fa[u];
        c++;
    }
}

void solve() {
    dfs(1, 0, 1);

    ll cnt = 0;
    for (int i = 1; i <= n; i++) cnt += g[i].size() == 1;

    ll ans = -1e18;
    ll half = n / 2;
    // 不让染蓝
    if (cnt <= K) {
        if (cnt >= half) ans = (n - cnt) * cnt;
        else if (K <= half) ans = (n - K) * K;
        else ans = (n - half) * half;
    }

    // 让染蓝
    int idx[n + 1];
    iota(idx, idx + n + 1, 0);
    sort(idx + 1, idx + n + 1, [&](auto &a, auto &b) {
        return dep[a] > dep[b];
    });
    for (int i = 1; i <= n; i++) {
        int id = idx[i];
        work(id);
    }

    iota(idx, idx + n + 1, 0);
    sort(idx + 1, idx + n + 1, [&](auto &a, auto &b) {
        return vc[a] > vc[b];
    });
    ll s = 0;
    for (int i = 0; i <= min(K, cnt - 1); i++) {
        s += vc[idx[i]];
        ll a = i, b = n - s;
        if (b >= half) b = half;

        ans = max(ans, (n - a) * a - (n - b) * b);
    }
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }
    solve();

    return 0;
}