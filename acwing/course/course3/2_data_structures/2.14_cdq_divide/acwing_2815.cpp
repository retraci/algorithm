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
        assert(id > 0);
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

// region 三维偏序 cdq
template<int SZ, class Fenwick>
struct Cdq {
    using cdqt = int;
    using at3 = array<cdqt, 3>;
    using at5 = array<cdqt, 5>;

    int n;
    at5 a[SZ + 10];

    Cdq() {}

    // 三维偏序, x1 <= x2 && y1 <= y2 && z1 <= z2, 答案记录在 p2
    void cdq(int L, int R, Fenwick &fw) {
        static at5 tmp[SZ + 10];

        if (L >= R) return;
        int mid = L + R >> 1;
        cdq(L, mid, fw), cdq(mid + 1, R, fw);

        int i = L, j = mid + 1, k = 0;
        while (i <= mid && j <= R) {
            if (a[i][2] <= a[j][2]) fw.upd(a[i][3], a[i][4]), tmp[++k] = a[i++];
            else a[j][0] += fw.qr(a[j][3]), tmp[++k] = a[j++];
        }
        while (i <= mid) fw.upd(a[i][3], a[i][4]), tmp[++k] = a[i++];
        while (j <= R) a[j][0] += fw.qr(a[j][3]), tmp[++k] = a[j++];

        for (int u = L; u <= mid; u++) fw.upd(a[u][3], -a[u][4]);
        for (int u = L, v = 1; u <= R; u++, v++) a[u] = tmp[v];
    }

    // m 为 第三维的值域
    // at5 = {ans, x, y, z, cnt};
    vector<at5> work(const vector<at3> &ps, Fenwick &fw, int m) {
        n = 0;
        for (auto [x, y, z] : ps) a[++n] = {0, x, y, z, 1};
        sort(a + 1, a + n + 1, [](auto &lhs, auto &rhs) {
            auto [ans1, x1, y1, z1, c1] = lhs;
            auto [ans2, x2, y2, z2, c2] = rhs;
            if (x1 != x2) return x1 < x2;
            if (y1 != y2) return y1 < y2;
            return z1 < z2;
        });
        int tt = 1;
        for (int i = 2; i <= n; i++) {
            if (a[i][1] == a[tt][1] && a[i][2] == a[tt][2] && a[i][3] == a[tt][3]) a[tt][4]++;
            else a[++tt] = a[i];
        }

        fw.init(m);
        cdq(1, tt, fw);

        vector<at5> res(tt);
        for (int i = 1; i <= tt; i++) {
            auto [ret, x, y, z, cnt] = a[i];
            res[i - 1] = {ret + cnt - 1, x, y, z, cnt};
        }

        return res;
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;
const int M = 2e5 + 10;


int n, m;
ai3 a[N];
Fenwick<M> fw;
Cdq<N, Fenwick<M>> cdq;

void solve() {
    auto ret = cdq.work(vector<ai3>(a + 1, a + n + 1), fw, m);

    vector<int> ans(n + 1);
    for (auto [res, x, y, z, cnt] : ret) {
        ans[res] += cnt;
    }
    for (int i = 0; i < n; i++) cout << ans[i] << "\n";
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
        for (int i = 1; i <= n; i++) {
            int ta, tb, tc;
            cin >> ta >> tb >> tc;

            a[i] = {ta, tb, tc};
        }
        solve();
    }

    return 0;
}