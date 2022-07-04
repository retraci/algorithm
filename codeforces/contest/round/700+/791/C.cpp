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

    int kth(fwt x) {
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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;

int n, q;
Fenwick<N> fw1, fw2;

void solve() {
    fw1.init(n);
    fw2.init(n);

    vector<int> c1(n + 1), c2(n + 1);
    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, y;
            cin >> x >> y;

            if (++c1[x] == 1) fw1.upd(x, 1);
            if (++c2[y] == 1) fw2.upd(y, 1);
        }
        if (op == 2) {
            int x, y;
            cin >> x >> y;

            if (--c1[x] == 0) fw1.upd(x, -1);
            if (--c2[y] == 0) fw2.upd(y, -1);
        }
        if (op == 3) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            int s1 = fw1.qr(x2) - fw1.qr(x1 - 1);
            int s2 = fw2.qr(y2) - fw2.qr(y1 - 1);
            int flag = s1 == (x2 - x1 + 1) || s2 == (y2 - y1 + 1);
            cout << (flag ? "Yes" : "No") << "\n";
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