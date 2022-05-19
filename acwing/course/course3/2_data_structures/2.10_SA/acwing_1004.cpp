#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cassert>
#include <random>
#include <cmath>

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
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region SA
template<int SZ>
struct SA {
    int n, m, sa[SZ + 10], rk[SZ + 10], prk[SZ * 2 + 10], id[SZ + 10], px[SZ + 10], cnt[SZ + 10];

    SA () {}

    // s 下标从 1 开始
    vector<int> get_sa(const string &s) {
        n = s.size() - 1, m = 300;
        fill(cnt, cnt + m + 1, 0);
        fill(prk, prk + 2 * n + 1, 0);

        for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;

        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (int i = n; i >= n - k + 1; i--) id[++p] = i;
            for (int i = 1; i <= n; i++) {
                if (sa[i] - k >= 1) id[++p] = sa[i] - k;
            }

            fill(cnt, cnt + m + 1, 0);
            for (int i = 1; i <= n; i++) cnt[px[i] = rk[id[i]]]++;
            for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; i--) sa[cnt[px[i]]--] = id[i];

            for (int i = 1; i <= n; i++) prk[i] = rk[i];
            rk[sa[1]] = 1, p = 1;
            for (int i = 2; i <= n; i++) {
                int x = sa[i], y = sa[i - 1];
                rk[sa[i]] = prk[x] == prk[y] && prk[x + k] == prk[y + k] ? p : ++p;
            }

            if (p == n) {
                vector<int> res(n + 1);
                for (int i = 1; i <= n; i++) res[i] = sa[i];
                return res;
            }

            m = p;
        }
    }

    vector<int> get_h(const string &s) {
        vector<int> res(n + 1);
        int k = 0;
        for (int i = 1; i <= n; i++) {
            if (rk[i] == 0) continue;
            if (k) k--;
            int j = sa[rk[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            res[rk[i]] = k;
        }

        return res;
    }
};
// endregion

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
const int N = 300010;

int n;
string s;
int a[N];
SA<N> saut;
Dsu<N> dsu;
vector<int> hs[N];
int mx1[N], mx2[N], mi1[N], mi2[N], sz[N];

ll C2(int x) {
    return 1LL * x * (x - 1) / 2;
}

pll work(int r) {
    static ll cnt = 0, mx = -2e18;

    for (auto x : hs[r]) {
        int tx = dsu.find(x - 1), ty = dsu.find(x);
        cnt -= C2(sz[tx]) + C2(sz[ty]);
        sz[ty] += sz[tx];
        cnt += C2(sz[ty]);

        if (mx1[tx] >= mx1[ty]) {
            mx2[ty] = max(mx1[ty], mx2[tx]);
            mx1[ty] = mx1[tx];
        }
        else if (mx1[tx] > mx2[ty]) {
            mx2[ty] = mx1[tx];
        }
        if (mi1[tx] <= mi1[ty]) {
            mi2[ty] = min(mi1[ty], mi2[tx]);
            mi1[ty] = mi1[tx];
        }
        else if (mi1[tx] < mi2[ty]) {
            mi2[ty] = mi1[tx];
        }
        mx = max({mx, 1LL * mx1[ty] * mx2[ty], 1LL * mi1[ty] * mi2[ty]});

        dsu.unite(tx, ty);
    }

    if (mx == -2e18) return {cnt, 0};
    return {cnt, mx};
}

void solve() {
    auto sa = saut.get_sa(s);
    auto h = saut.get_h(s);

    for (int i = 2; i <= n; i++) hs[h[i]].push_back(i);

    dsu.init(n);
    for (int i = 1; i <= n; i++) {
        mx1[i] = mi1[i] = a[sa[i]];
        mx2[i] = -2e9, mi2[i] = 2e9;
        sz[i] = 1;
    }

    vector<pll> ans(n + 1);
    for (int i = n - 1; i >= 0; i--) ans[i] = work(i);
    for (int i = 0; i <= n - 1; i++) cout << ans[i].fi << " " << ans[i].se << "\n";
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
        cin >> s;
        s = ' ' + s;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}