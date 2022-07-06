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

// region 可撤销 dsu
template<int SZ>
struct Dsu {
    vector<pii> his_fa, his_sz;
    int fa[SZ + 10], sz[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
        fill(sz, sz + _n + 1, 1);
        his_fa.clear();
        his_sz.clear();
    }

    int find(int x) {
        while (x != fa[x]) x = fa[x];
        return x;
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        if (sz[tx] > sz[ty]) swap(tx, ty);

        his_sz.push_back({ty, sz[ty]});
        sz[ty] += sz[tx];
        his_fa.push_back({tx, fa[tx]});
        fa[tx] = ty;

        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }

    void rollback(int h) {
        while (his_fa.size() > h) {
            fa[his_fa.back().fi] = his_fa.back().se;
            his_fa.pop_back();
            sz[his_sz.back().fi] = his_sz.back().se;
            his_sz.pop_back();
        }
    }

    int his() {
        return his_fa.size();
    }

    int size(int x) {
        int tx = find(x);
        return sz[tx];
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 5e5 + 10;

int n;
ai3 es[N];
map<int, vector<pii>> mp;
Dsu<N> dsu;
ll ans;

void dfs(int L, int R) {
    if (L == R) {
        for (auto [u, v] : mp[L]) {
            ans += 1LL * dsu.size(u) * dsu.size(v);
        }
        return;
    }

    int mid = L + R >> 1;
    int h = dsu.his();
    for (int i = mid + 1; i <= R; i++) {
        for (auto [u, v] : mp[i]) {
            dsu.unite(u, v);
        }
    }
    dfs(L, mid);
    dsu.rollback(h);

    for (int i = L; i <= mid; i++) {
        for (auto [u, v] : mp[i]) {
            dsu.unite(u, v);
        }
    }
    dfs(mid + 1, R);
    dsu.rollback(h);
}

void solve() {
    dsu.init(n);
    for (int i = 1; i <= n - 1; i++) {
        auto [u, v, cost] = es[i];
        mp[cost].push_back({u, v});
    }

    dfs(1, n);

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
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n - 1; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            es[i] = {u, v, cost};
        }
        solve();
    }

    return 0;
}