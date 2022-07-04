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
const int N = 1e5 + 10;

using ai4 = array<int, 4>;

int n, q;
string s;
ai4 qs[N];
Dsu<N> dsu[335];

void solve() {
    n = s.size() - 1;
    int sq = sqrt(n);

    vector<int> vis(n + 1);
    for (int i = 1; i <= sq; i++) dsu[i].init(n + 1);
    for (int i = q; i >= 1; i--) {
        auto [st, d, len, ch] = qs[i];

        if (d > sq) {
            int cur = st;
            for (int k = 0; k <= len; k++) {
                if (!vis[cur]) {
                    vis[cur] = 1;
                    s[cur] = ch;
                }

                cur += d;
            }
        } else {
            int cur = st;
            while ((cur - st) / d <= len && cur <= n) {
                if (!vis[cur]) {
                    vis[cur] = 1;
                    s[cur] = ch;
                }

                dsu[d].unite(cur, min(n + 1, cur + d));
                cur = dsu[d].find(cur);
            }
        }
    }

    cout << s.substr(1) << "\n";
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
        cin >> s;
        s = ' ' + s;

        cin >> q;
        for (int i = 1; i <= q; i++) {
            int st, d, len;
            char ch;
            cin >> st >> d >> len >> ch;

            qs[i] = {st, d, len, ch};
        }
        solve();
    }

    return 0;
}