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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 2e5 + 10;

int n, k;
int a[N];
Dsu<N> dsu;

void solve() {
    dsu.init(n);

    for (int i = 1; i + k <= n; i++) {
        dsu.unite(i, i + k);
    }

    vector<int> b[n + 1];
    for (int i = 1; i <= n; i++) {
        int tx = dsu.find(i);
        b[tx].push_back(i);
    }

    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        vector<int> ord = b[i];
        sort(ord.begin(), ord.end(), [&](auto &x, auto &y) {
            return a[x] < a[y];
        });

        for (int j = 0; j < b[i].size(); j++) {
            ans[b[i][j]] = a[ord[j]];
        }
    }

    int flag = is_sorted(ans.begin() + 1, ans.end());
    cout << (flag ? "Yes" : "No") << "\n";
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
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}