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
const int N = 2e5 + 10;

using ai4 = array<int, 4>;

int n, q;
int a[N];
ai3 qs[N];
vector<int> lsh;
Fenwick<2 * N> fwc, fws;
int nl;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    lsh.insert(lsh.end(), a + 1, a + n + 1);
    for (int i = 1; i <= q; i++) {
        auto [L, R, k] = qs[i];
        lsh.push_back(k / 2 + 1);
    }

    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();
}

void solve() {
    init();

    vector<ai4> oqs;
    for (int i = 1; i <= q; i++) {
        auto [L, R, k] = qs[i];

        oqs.push_back({i, R, k / 2 + 1, 1});
        oqs.push_back({i, L - 1, k / 2 + 1, -1});
    }
    sort(oqs.begin(), oqs.end(), [](auto &a, auto &b) {
        return a[1] < b[1];
    });

    fwc.init(nl), fws.init(nl);
    vector<ll> sum(q + 1), cnt(q + 1);
    int u = 1;
    for (auto [qid, id, x, sgn] : oqs) {
        while (u <= id) {
            int v = get(a[u]) + 1;
            fwc.upd(v, 1), fws.upd(v, a[u]);
            u++;
        }

        int lb = get(x) + 1;
        ll tc = fwc.qr(nl) - fwc.qr(lb - 1);
        ll ts = fws.qr(nl) - fws.qr(lb - 1);

        cnt[qid] += sgn * tc;
        sum[qid] += sgn * ts;
    }

    vector<ll> s(n + 1);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];

    vector<ll> ans(q + 1);
    for (int i = 1; i <= q; i++) {
        auto [L, R, k] = qs[i];

        ans[i] = (s[R] - s[L - 1] - sum[i]) + (cnt[i] * k - sum[i]);
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= q; i++) {
            int L, R, k;
            cin >> L >> R >> k;
            qs[i] = {L, R, k};
        }
        solve();
    }

    return 0;
}