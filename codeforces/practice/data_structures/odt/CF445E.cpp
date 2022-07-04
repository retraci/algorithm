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

// region 区间修改 fenwick
template<int SZ>
struct Fenwick {
    using fwt = ll;

    int n;
    fwt tr1[SZ + 10], tr2[SZ + 10];

    Fenwick() {}

    void init(int _n) {
        n = _n;
        fill(tr1, tr1 + n + 1, 0);
        fill(tr2, tr2 + n + 1, 0);
    }

    void upd(fwt tr[], int id, fwt x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(fwt tr[], int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    fwt get_presum(int id) {
        return (id + 1) * qr(tr1, id) - qr(tr2, id);
    }

    void upd_range(int L, int R, fwt x) {
        upd(tr1, L, x), upd(tr1, R + 1, -x);
        upd(tr2, L, x * L), upd(tr2, R + 1, -x * (R + 1));
    }

    fwt qr_range(int L, int R) {
        return get_presum(R) - get_presum(L - 1);
    }
};
// endregion

const int N = 1e5 + 10;
Fenwick<N> fw;

// region odt
struct Odt {
    using odtt = int;

    int n;
    map<int, odtt> odt;

    Odt() {}

    void init(int _n) {
        n = _n;
        odt.clear();
        odt[0] = 0, odt[n + 1] = 0;
        for (int i = 1; i <= n; i++) odt[i] = i;
    }

    void split(int pos) {
        auto [L, v] = *prev(odt.upper_bound(pos));
        odt[pos] = v;
    }

    void assign(int L, int R, odtt v) {
        split(L), split(R + 1);

        auto it = odt.find(L);
        while (it->fi != R + 1) {
            auto [tl, tv] = *it;
            int tr = (next(it)->fi) - 1;
            fw.upd_range(tl, tr, abs(tv - v));
            it = odt.erase(it);
        }
        odt[L] = v;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

int n, q;
Odt odt;

void solve() {
    fw.init(n);
    odt.init(n);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int L, R, x;
            cin >> L >> R >> x;

            odt.assign(L, R, x);
        } else {
            int L, R;
            cin >> L >> R;

            cout << fw.qr_range(L, R) << "\n";
        }
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
        cin >> n >> q;
        solve();
    }

    return 0;
}