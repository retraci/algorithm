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
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

// region 质因数分解, 枚举最小质数 (x < N)
vector<int> isp, mip, pr;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);
    mip.resize(lim + 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr.push_back(i);
            mip[i] = i;
        }

        for (int p : pr) {
            if (p > lim / i) break;

            mip[i * p] = p;
            isp[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}

vector<pii> divide(int x) {
    vector<pii> res;
    res.clear();
    while (x > 1) {
        int p = mip[x];
        int c = 0;
        while (x % p == 0) x /= p, c++;
        res.push_back({p, c});
    }

    return res;
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 3e5 + 10;

int n;
int a[N];

void solve() {
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        auto ps = divide(a[i]);
        int x = 1;
        for (auto [p, c] : ps) {
            if (c & 1) x *= p;
        }
        cnt[x]++;
    }

    int ans1 = 0;
    for (auto [_, c] : cnt) ans1 = max(ans1, c);

    for (auto &[p, c] : cnt) {
        if (p != 1 && ~c & 1) cnt[1] += c, c = 0;
    }
    int ans2 = 0;
    for (auto [_, c] : cnt) ans2 = max(ans2, c);

    int q;
    cin >> q;
    while (q--) {
        ll w;
        cin >> w;

        cout << (w >= 1 ? ans2 : ans1) << "\n";
    }
}

void prework() {
    init_prime(1e6);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}