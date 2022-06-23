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
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;
const int M = 2e5 + 10;

int n, k, S, T;
int a[N];
int h[N], ne[M * 2], e[M * 2], edm;
int fa[N], dep[N];

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u, int fno) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        fa[v] = u, dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

void solve() {
    dep[S] = 1;
    dfs(S, 0);

    vector<int> vis(n + 1);
    vis[S] = 1;
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        int u = a[i];
        while (!vis[u]) {
            vis[u] = 1;
            ans += 2;
            u = fa[u];
        }
    }
    int u = T;
    while (!vis[u]) {
        vis[u] = 1;
        ans += 2;
        u = fa[u];
    }

    ans -= dep[T] - dep[S];
    cout << ans << "\n";
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
    cin >> _;
    while (_--) {
        cin >> n >> k >> S >> T;
        fill(h + 1, h + n + 1, -1), edm = 0;
        for (int i = 1; i <= k; i++) cin >> a[i];
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}