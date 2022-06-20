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

// region dsu
template<int SZ>
struct Dsu {
    int fa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        fa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1010;

int n;
string a[N], b[N];
Dsu<4 * N> dsu;

void solve() {
    dsu.init(4 * n);
    int flag = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int u = i, v = n + j;
            if (a[i][j] == b[i][j]) {
                if (dsu.same(u, 2 * n + v)) flag = 1;
                dsu.unite(u, v);
                dsu.unite(2 * n + u, 2 * n + v);
            } else {
                if (dsu.same(u, v)) flag = 1;
                dsu.unite(u, 2 * n + v);
                dsu.unite(2 * n + u, v);
            }
        }
    }

    cout << (flag ? "NO" : "YES") << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] = ' ' + a[i];
        }

        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            b[i] = ' ' + b[i];
        }
        solve();
    }

    return 0;
}