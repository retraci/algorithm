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
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region 双模哈希
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;

pii operator+(const pii &a, const pii &b) {
    int c1 = a.fi + b.fi, c2 = a.se + b.se;
    if (c1 >= mod1) c1 -= mod1;
    if (c2 >= mod2) c2 -= mod2;
    return {c1, c2};
}

pii operator-(const pii &a, const pii &b) {
    int c1 = a.fi - b.fi, c2 = a.se - b.se;
    if (c1 < 0) c1 += mod1;
    if (c2 < 0) c2 += mod2;
    return {c1, c2};
}

pii operator*(const pii &a, const pii &b) {
    return {1LL * a.fi * b.fi % mod1, 1LL * a.se * b.se % mod2};
}

vector<pii> pw;
pii base;

void init_hash(int lim = 0) {
    pw = vector<pii>(lim + 1);
    base = {rnd(mod1), rnd(mod2)};
    pw[0] = {1, 1};
    for (int i = 1; i <= lim; i++) pw[i] = pw[i - 1] * base;
}
// endregion

// region fenwick
template<int SZ>
struct Fenwick {
    using fwt = pii;

    int n;
    fwt tr[SZ + 10];

    Fenwick() {}

    void init(int _n, fwt v = {0, 0}) {
        n = _n;
        fill(tr, tr + n + 1, v);
    }

    void upd(int id, fwt x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(int id) {
        fwt res = {0, 0};
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    int kth(int x) {
        int pos = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (pos + (1 << i) <= n && tr[pos + (1 << i)] < x) {
                pos += 1 << i;
                x -= tr[pos];
            }
        }

        return pos + 1;
    }
};
// endregion

// region fenwick
template<int SZ>
struct Fenwick2 {
    using fwt = ll;

    int n;
    fwt tr[SZ + 10];

    Fenwick2() {}

    void init(int _n, fwt v = 0) {
        n = _n;
        fill(tr, tr + n + 1, v);
    }

    void upd(int id, fwt x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    int kth(int x) {
        int pos = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (pos + (1 << i) <= n && tr[pos + (1 << i)] < x) {
                pos += 1 << i;
                x -= tr[pos];
            }
        }

        return pos + 1;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

int n, m;
int a[N];
Fenwick<N> fw;
Fenwick2<N> fw2;

void solve() {
    fw.init(n);
    fw2.init(n);
    for (int i = 1; i <= n; i++) {
        fw.upd(i, pw[a[i]]);
        fw2.upd(i, a[i]);
    }

    while (m--) {
        int op;
        cin >> op;

        if (op == 0) {
            int p, x;
            cin >> p >> x;

            fw.upd(p, pw[x] - pw[a[p]]);
            fw2.upd(p, x - a[p]);
            a[p] = x;
        }
        if (op == 1) {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;

            ll s1 = fw2.qr(r1) - fw2.qr(l1 - 1);
            ll s2 = fw2.qr(r2) - fw2.qr(l2 - 1);
            ll dta = abs(s1 - s2);
            int len = r1 - l1 + 1;
            if (dta % len) {
                cout << "NO" << "\n";
                continue;
            }

            int k = dta / len;
            pii h1 = fw.qr(r1) - fw.qr(l1 - 1);
            pii h2 = fw.qr(r2) - fw.qr(l2 - 1);
            pii hk = pw[k];
            if (h1 * hk == h2 || h2 * hk == h1) cout << "YES" << "\n";
            else cout << "NO" << "\n";
        }
    }
}

void prework() {
    init_hash(1e6);
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}