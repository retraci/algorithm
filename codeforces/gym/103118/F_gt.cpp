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
mt19937 rnd(time(0));
mt19937_64 rnd64(time(0));

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

void init_hash(int lim) {
    pw = vector<pii>(lim + 1);
    base = {rnd() % mod1, rnd() % mod2};
    pw[0] = {1, 1};
    for (int i = 1; i <= lim; i++) pw[i] = pw[i - 1] * base;
}
// endregion

// region 字符串哈希
struct Hv {
    vector<pii> v;

    Hv() {}

    void init(const string &s) {
        int m = s.size();
        v.resize(m + 1);
        for (int j = 1; j <= m; j++) {
            char ch = s[j - 1];
            v[j] = v[j - 1] * base + (pii) {ch, ch};
        }
    }

    pii get(int L, int R) {
        return v[R] - (v[L - 1] * pw[R - L + 1]);
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 4e5 + 10;

int n;
string a[N];
Hv ha[N];

void solve() {
    for (int i = 1; i <= n; i++) {
        ha[i].init(a[i]);
    }

    map<pii, int> cnt;
    for (int i = 1; i <= n; i++) {
        int m = a[i].size();
        cnt[ha[i].get(1, m)]++;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int m = a[i].size();
        ans += cnt[ha[i].get(1, m)] - 1;
    }
    ans /= 2;

    for (int i = 1; i <= n; i++) {
        int m = a[i].size();
        for (int j = 1; j <= m / 2; j++) {
            int lb = j + 1, rb = m - j;
            if (ha[i].get(1, j) == ha[i].get(rb + 1, m)) {
                ans += cnt[ha[i].get(lb, rb)];
            }
        }
    }

    cout << ans << "\n";
}

void prework() {
    init_hash(4e5);
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}