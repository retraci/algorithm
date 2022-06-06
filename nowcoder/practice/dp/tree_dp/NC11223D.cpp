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
const int N = 1e6 + 10;
const int M = 1e6 + 10;

int n;
pii e[M * 2];
int ne[M * 2], h[N], edm;
int f[N][3], ans[N];

void add(int u, int v, int cost) {
    e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
}

void dfs1(int u, int fno) {
    for (int i = h[u]; ~i; i = ne[i]) {
        auto [v, cost] = e[i];
        if (v == fno) continue;

        dfs1(v, u);

        if (cost == 1) {
            f[u][1]++;
            f[u][2] += f[v][1];
        }
        if (cost == 2) {
            f[u][2]++;
        }
    }
}

void dfs2(int u, int fno, int fa1, int fa2) {
    ans[u] = fa1 + fa2 + f[u][1] + f[u][2] + 1;

    for (int i = h[u]; ~i; i = ne[i]) {
        auto [v, cost] = e[i];
        if (v == fno) continue;

        if (cost == 1) dfs2(v, u, 1, fa1 + f[u][1] - 1);
        else if (cost == 2) dfs2(v, u, 0, 1);
        else dfs2(v, u, 0, 0);
    }
}

void solve() {
    dfs1(1, -1);
    dfs2(1, -1, 0, 0);

    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
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
        cin >> n;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 2; i <= n; i++) {
            int u = i, v, cost;
            cin >> v >> cost;
            add(u, v, cost), add(v, u, cost);
        }

        solve();
    }

    return 0;
}