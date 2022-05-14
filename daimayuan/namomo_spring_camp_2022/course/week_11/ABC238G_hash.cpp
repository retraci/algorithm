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
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

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

vector<pii> fs;

void divide(int x) {
    fs = {};
    while (x > 1) {
        int p = mip[x];
        int c = 0;
        while (x % p == 0) x /= p, c++;
        fs.push_back({p, c});
    }
}
// endregion

// region 双模哈希
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;

pii operator+(const pii &a, const pii &b) {
    int c1 = a.fi + b.fi, c2 = a.se + b.se;
    if (c1 >= mod1) c1 -= mod1;
    if (c2 >= mod2) c2 -= mod2;
    return {c1, c2};
}

pii operator-(const pii &a, const pii &b) {
    int c1 = a.fi - b.fi, c2 = a.se - b.se;
    if (c1 < 0) c1 += mod1;
    if (c2 < 0) c2 += mod2;
    return {c1, c2};
}

pii operator*(const pii &a, const pii &b) {
    return {1LL * a.fi * b.fi % mod1, 1LL * a.se * b.se % mod2};
}

vector<pii> pw;
pii base;

void init_hash(int lim = 0) {
    pw = vector<pii>(lim + 1);
    base = {rnd(mod1), rnd(mod2)};
    pw[0] = {1, 1};
    for (int i = 1; i <= lim; i++) pw[i] = pw[i - 1] * base;
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;

int n, m;
int a[N];
int cnt[(int) 1e6 + 1];
vector<pii> b[N];

pii add(pii ha, int p, int x) {
    ha = ha - (pw[p] * (pii) {cnt[p], cnt[p]});
    cnt[p] = (cnt[p] + x) % 3;
    ha = ha + (pw[p] * (pii) {cnt[p], cnt[p]});
    return ha;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        divide(a[i]);
        b[i] = fs;
    }

    vector<pii> ha(n + 1);
    for (int i = 1; i <= n; i++) {
        pii cur = ha[i - 1];
        for (auto [p, c] : b[i]) {
            cur = add(cur, p, c);
        }
        ha[i] = cur;
    }

    while (m--) {
        int L, R;
        cin >> L >> R;

        cout << (ha[R] == ha[L - 1] ? "Yes" : "No") << "\n";
    }
}

void prework() {
    init_prime(1e6);
    init_hash(1e6);
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}