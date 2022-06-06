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
using al3 = array<ll, 3>;
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
ll d1[N], d2[N];
int vis[N], co[N];

void add(int u, int v, int cost) {
    e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
}

void dij() {
    static priority_queue<al3> que;
    fill(d1 + 1, d1 + n + 1, 1e18);
    fill(d2 + 1, d2 + n + 1, 1e18);
    fill(vis + 1, vis + n + 1, 0);
    fill(co + 1, co + n + 1, 0);

    for (int i = 1; i <= l; i++) {
        int u = b[i];
        d1[u] = 0;
        que.push({0, u, a[u]});
    }
    while (!que.empty()) {
        auto [d, u, col] = que.top(); que.pop(); d = -d;

        if (vis[u] < 2 && co[u] != col) {
            if (vis[u] == 0) {
                co[u] = col;
                d1[u] = d;
            } else {
                d2[u] = d;
            }
            vis[u]++;

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cost] = e[i];

                que.push({-(d + cost), v, col});
            }
        }
    }
}

void solve() {
    dij();

    for (int i = 1; i <= n; i++) {
        ll ans;
        if (co[i] != a[i]) {
            ans = d1[i];
        } else {
            ans = d2[i];
        }

        cout << (ans == 1e18 ? -1 : ans) << " \n"[i == n];
    }
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