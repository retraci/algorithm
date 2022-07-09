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

// region 线性筛
vector<int> isp, pr;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) pr.push_back(i);

        for (int p : pr) {
            if (p > lim / i) break;

            isp[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}
// endregion

const int MOD = 1e9 + 7;

int ksm(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

const int P = 2262;

// region odt
struct Odt {
    using odtt = vector<int>;

    map<int, odtt> tr;

    Odt() {}

    void init(int _n) {
        tr.clear();
        tr[0] = {}, tr[_n + 1] = {};
    }

    void split(int pos) {
        auto [L, v] = *prev(tr.upper_bound(pos));
        tr[pos] = v;
    }

    void assign(int L, int R, const odtt &v) {
        split(L), split(R + 1);

        auto it = tr.find(L);
        while (it->fi != R + 1) {
            auto [tl, tv] = *it;
            it = tr.erase(it);
        }
        tr[L] = v;
    }

    odtt qr(int L, int R) {
        split(L), split(R + 1);

        odtt res(P, 0);
        auto it = tr.find(L);
        while (it->fi != R + 1) {
            auto [tl, tv] = *it;
            for (int i = 0; i < P; i++) res[i] = max(res[i], tv[i]);
            it++;
        }
        tr[L] = res;

        return res;
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 20010;

int n, q;
int a[N];
Odt odt;

vector<int> get(int x) {
    vector<int> res(P, 0);
    for (int i = 0; i < P; i++) {
        while (x % pr[i] == 0) res[i]++, x /= pr[i];
    }
    return res;
}

void solve() {
    odt.init(n);
    for (int i = 1; i <= n; i++) {
        odt.assign(i, i, get(a[i]));
    }

    while (q--) {
        int L, R;
        cin >> L >> R;

        auto t = odt.qr(L, R);
        int ans = 1;
        for (int i = 0; i < P; i++) ans = 1LL * ans * ksm(pr[i], t[i]) % MOD;
        odt.assign(L, R, t);

        cout << ans << "\n";
    }
}

void prework() {
    init_prime(20000);
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
        solve();
    }

    return 0;
}