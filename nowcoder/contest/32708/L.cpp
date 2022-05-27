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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<double, double>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region fenwick
template<int SZ>
struct Fenwick {
    using fwt = int;

    int n;
    fwt tr[SZ + 10];

    Fenwick() {}

    void init(int _n) {
        n = _n;
        fill(tr, tr + n + 1, 0);
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
const double PI = acosl(-1.0);
const double eps = 1e-9;
const int N = 1e5 + 10;

int n, m;
pii a[N];
ll ans[N];
Fenwick<N> fw;
vector<double> lsh;

int get(double x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void work(int L, int R) {
    double s1 = sinl(L * PI / 180), s2 = sinl(R * PI / 180);
    double c1 = cosl(L * PI / 180), c2 = cosl(R * PI / 180);

    vector<pdd> ps(n + 1);
    for (int i = 1; i <= n; i++) {
        auto [x, y] = a[i];
        double nx = x * -s1 + y * -c1;
        double ny = x * s2 + y * c2;
        ps[i] = {nx, ny};
    }

    vector<int> ord(n + 1);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin() + 1, ord.end(), [&](auto &a, auto &b) {
        auto [x1, y1] = ps[a];
        auto [x2, y2] = ps[b];
        if (abs(x1 - x2) > eps) return x1 < x2;
        return y1 < y2;
    });

    lsh = {};
    for (int i = 1; i <= n; i++) {
        auto [x, y] = ps[i];
        lsh.push_back(y);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end(), [&](auto &a, auto &b) {
        return abs(a - b) <= eps;
    }) - lsh.begin());
    int nl = lsh.size();

    fw.init(nl);
    for (int i = 1; i <= n; i++) {
        int id = ord[i];
        auto [x, y] = ps[id];
        y = get(y - eps) + 1;

        ans[id] += fw.qr(y);
        fw.upd(y, 1);
    }
}

void solve() {
    while (m--) {
        int L, R;
        cin >> L >> R;
        work(L, R);
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        solve();
    }

    return 0;
}