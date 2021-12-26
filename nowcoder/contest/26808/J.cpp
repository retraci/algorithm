#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2e5 + 10;

ll n, m;
pll vp[N];

vector<pll> g[N];

void add(int u, int v, ll cost) {
    g[u].push_back({v, cost});
}

ll dfs(ll u, ll fno, ll w, ll ti) {
    if (ti < 2 * w) return 0;

    auto &[c, p] = vp[u];
    ll res;
    if (p == 0) res = c;
    else res = min(c, (ti - 2 * w) / p + 1);
    for (auto &[v, cost] : g[u]) {
        if (v == fno) continue;
        res += dfs(v, u, w + cost, ti);
    }

    return res;
}

bool check(ll mid) {
    return dfs(1, 0, 0, mid) >= m;
}

void solve() {
    ll left = 0, right = 1e18;
    while (left < right) {
        ll mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

    if (left == 1e18) {
        cout << "Too many students!" << "\n";
        return;
    }
    cout << left << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        ll c, p;
        cin >> c >> p;
        vp[i] = {c, p};
    }
    for (int i = 1; i <= n - 1; i++) {
        ll u, v, cost;
        cin >> u >> v >> cost;
        add(u, v, cost), add(v, u, cost);
    }
    solve();

    return 0;
}