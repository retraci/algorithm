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

pll operator+(const pll &a, const pll &b) {
    pll res;
    res.fi = a.fi + b.fi;
    res.se = a.se + b.se;
    return res;
}

// region fenwick
template<int SZ>
struct Fenwick {
    using fwt = pll;

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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;

int n;
int x[N], v[N];
Fenwick<N> fw;
vector<int> lsh;
int nl;

int get(int tx) {
    return lower_bound(lsh.begin(), lsh.end(), tx) - lsh.begin();
}

void init() {
    lsh = {};
    for (int i = 1; i <= n; i++) lsh.push_back(v[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();
}

void solve() {
    init();

    fw.init(n);
    vector<int> ord(n + 1);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](auto &a, auto &b) {
        return x[a] < x[b];
    });

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int id = ord[i];

        int lsv = get(v[id]) + 1;
        auto [c, s] = fw.qr(lsv);
        ans += 1LL * c * x[id] - s;

        fw.upd(lsv, {1, x[id]});
    }

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
        for (int i = 1; i <= n; i++) cin >> x[i];
        for (int i = 1; i <= n; i++) cin >> v[i];
        solve();
    }

    return 0;
}