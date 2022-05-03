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

// region fenwick
template<int SZ>
struct Fenwick {
    int n;
    ll tr[SZ + 10];

    Fenwick() {
        init(SZ);
    }

    void init(int _n, ll v = 0) {
        n = _n;
        fill(tr, tr + n + 1, v);
    }

    void upd(int id, ll x) {
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll qr(int id) {
        ll res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }
};
// endregion

const int N = 4e5 + 10;

int n, m, x, y;
pii a[N], b[N];
Fenwick<N> fw;
int nl;
vector<int> lsh;

int get(int t) {
    return lower_bound(lsh.begin(), lsh.end(), t) - lsh.begin();
}

ll work1() {
    fw.init(nl);
    sort(a + 1, a + x + 1);

    ll res = 0;
    for (int i = 1; i <= x; i++) {
        auto [ta, tb] = a[i];
        ta = get(ta) + 1, tb = get(tb) + 1;

        res += (i - 1) - fw.qr(tb);
        fw.upd(tb, 1);
    }

    return res;
}

ll work2() {
    fw.init(nl);
    sort(b + 1, b + y + 1);

    ll res = 0;
    for (int i = 1; i <= y; i++) {
        auto [ta, tb] = b[i];
        ta = get(ta) + 1, tb = get(tb) + 1;

        res += (i - 1) - fw.qr(tb);
        fw.upd(tb, 1);
    }

    return res;
}

void solve() {
    for (int i = 1; i <= x; i++) {
        auto [ta, tb] = a[i];
        lsh.push_back(ta), lsh.push_back(tb);
    }
    for (int i = 1; i <= y; i++) {
        auto [ta, tb] = b[i];
        lsh.push_back(ta), lsh.push_back(tb);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    ll t1 = 2 * (x + y);
    ll t2 = 1LL * x * y + work1() + work2();

    ll V = t1 + t2;
    ll E = (3 * t1 + 4 * t2) / 2;
    ll F = 2 + E - V;

    cout << F - 1 << "\n";
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
        cin >> n >> m >> x >> y;
        for (int i = 1; i <= x; i++) cin >> a[i].fi >> a[i].se;
        for (int i = 1; i <= y; i++) cin >> b[i].fi >> b[i].se;
        solve();
    }

    return 0;
}