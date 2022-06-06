#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int M = 1e5 + 10;

int n, m, k, l;
int a[N], b[N];
pii e[M * 2];
int ne[M * 2], h[N], edm;
ll d[N];
int vis[N];

void add(int u, int v, int cost) {
    e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
}

void dij(const vector<int> &s) {
    static priority_queue<pll> que;
    fill(d + 1, d + n + 1, 1e18);
    fill(vis + 1, vis + n + 1, 0);

    for (auto v : s) {
        d[v] = 0;
        que.push({0, v});
    }
    while (!que.empty()) {
        auto [_, u] = que.top(); que.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cost] = e[i];

            if (d[v] > d[u] + cost) {
                d[v] = d[u] + cost;
                que.push({-d[v], v});
            }
        }
    }
}

void solve() {
    vector<ll> ans(n + 1, 1e18);
    for (int bit = 0; bit <= __lg(k); bit++) {
        for (int dit = 0; dit <= 1; dit++) {
            vector<int> s;
            for (int i = 1; i <= l; i++) {
                if ((a[b[i]] >> bit & 1) == dit) s.push_back(b[i]);
            }

            dij(s);

            for (int i = 1; i <= n; i++) {
                if ((a[i] >> bit & 1) == 1 - dit) ans[i] = min(ans[i], d[i]);
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << (ans[i] == 1e18 ? -1 : ans[i]) << " ";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> m >> k >> l;
        fill(h + 1, h + n + 1, -1), edm = 0;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= l; i++) cin >> b[i];
        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            add(u, v, cost), add(v, u, cost);
        }
        solve();
    }

    return 0;
}