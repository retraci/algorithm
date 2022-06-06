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
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region fenwick
template<int SZ>
struct Fenwick {
    using fwt = ll;

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
const int N = 2e5 + 10;

int n, m, q;
int ops[N];
ai3 qs[N];
Fenwick<N> fw;

void solve() {
    vector<pii> lst(n + 1);
    vector<ll> ans(q + 1);
    vector<ai3> a[q + 1];
    for (int i = 1; i <= q; i++) {
        auto op = ops[i];

        if (op == 1) {
            auto [L, R, x] = qs[i];
        }
        if (op == 2) {
            auto [id, x, _] = qs[i];
            lst[id] = {i, x};
        }
        if (op == 3) {
            auto [r, c, _] = qs[i];

            auto [lr, lx] = lst[r];
            ans[i] = lx;
            a[lr].push_back({-1, i, c});
            a[i].push_back({1, i, c});
        }
    }

    fw.init(m + 1);
    for (int i = 1; i <= q; i++) {
        auto op = ops[i];

        if (op == 1) {
            auto [L, R, x] = qs[i];
            fw.upd(L, x), fw.upd(R + 1, -x);
        } else {
            for (auto [sgn, qid, c] : a[i]) {
                ans[qid] += sgn * fw.qr(c);
            }
        }
    }

    for (int i = 1; i <= q; i++) {
        auto op = ops[i];

        if (op == 3) cout << ans[i] << "\n";
    }
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
        cin >> n >> m >> q;
        for (int i = 1; i <= q; i++) {
            int op;
            cin >> op;

            ops[i] = op;
            if (op == 1) {
                int L, R, x;
                cin >> L >> R >> x;
                qs[i] = {L, R, x};
            }
            if (op == 2) {
                int id, x;
                cin >> id >> x;
                qs[i] = {id, x, 0};
            }
            if (op == 3) {
                int x, y;
                cin >> x >> y;
                qs[i] = {x, y, 0};
            }
        }
        solve();
    }

    return 0;
}