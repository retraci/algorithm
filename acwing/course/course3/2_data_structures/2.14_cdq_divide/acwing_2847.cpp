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
    using fwt = ll;

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

// region 二维数点
template<int Q, class Fenwick>
struct TwoDimCount {
    using fwt = ll;
    using tdct = int;
    using at3 = array<tdct, 3>;
    using at4 = array<tdct, 4>;
    using at5 = array<tdct, 5>;

    int oq;
    at4 oqs[4 * Q + 10];

    TwoDimCount() {}

    // ps[i] = {x, y, w}
    // qs[i] = {qid, x1, x2, y1, y2}
    // m 为第二维的值域, q 为询问总个数
    vector<fwt> work(vector<at3> ps, const vector<at5> &qs, Fenwick &fw, int m, int q) {
        oq = 0;
        for (auto [qid, x1, x2, y1, y2] : qs) {
            oqs[++oq] = {qid, x1 - 1, y2, -1};
            oqs[++oq] = {qid, x1 - 1, y1 - 1, +1};
            oqs[++oq] = {qid, x2, y2, +1};
            oqs[++oq] = {qid, x2, y1 - 1, -1};
        }

        sort(ps.begin(), ps.end(), [](auto &lhs, auto &rhs) {
            return lhs[0] < rhs[0];
        });
        sort(oqs + 1, oqs + oq + 1, [](auto &lhs, auto &rhs) {
            return lhs[1] < rhs[1];
        });

        fw.init(m);
        int u = 0;
        vector<fwt> res(q + 1);
        for (int i = 1; i <= oq; i++) {
            auto [qid, x, y, sgn] = oqs[i];

            while (u < ps.size() && ps[u][0] <= x) fw.upd(ps[u][1], ps[u][2]), u++;
            res[qid] += sgn * fw.qr(y);
        }
        return res;
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;

using ai4 = array<int, 4>;
using ai5 = array<int, 5>;

int n, q;
ai3 a[N];
ai4 qs[N];
Fenwick<3 * N> fw;
TwoDimCount<N, Fenwick<3 * N>> tdc;
vector<int> lsh;
int nl;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) lsh.push_back(a[i][1]);
    for (int i = 1; i <= q; i++) {
        auto [x1, y1, x2, y2] = qs[i];
        lsh.push_back(y1);
        lsh.push_back(y2);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();
}

void solve() {
    init();

    vector<ai3> ps;
    for (int i = 1; i <= n; i++) {
        auto [x, y, w] = a[i];
        int ny = get(y) + 1;
        ps.push_back({x, ny, w});
    }
    vector<ai5> tdcqs;
    for (int i = 1; i <= q; i++) {
        auto [x1, y1, x2, y2] = qs[i];

        int ny1 = get(y1) + 1;
        int ny2 = get(y2) + 1;
        tdcqs.push_back({i, x1, x2, ny1, ny2});
    }

    auto ret = tdc.work(ps, tdcqs, fw, nl, q);
    for (int i = 1; i <= q; i++) cout << ret[i] << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1] >> a[i][2];
        for (int i = 1; i <= q; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            qs[i] = {x1, y1, x2, y2};
        }
        solve();
    }

    return 0;
}