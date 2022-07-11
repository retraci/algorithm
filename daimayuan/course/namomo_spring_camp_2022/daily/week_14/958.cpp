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
// endregion

// region 字符串哈希
vector<pii> pw;
pii base;

void init_strhash(int lim = 0) {
    pw = vector<pii>(lim + 1);
    base = {rnd(mod1), rnd(mod2)};
    pw[0] = {1, 1};
    for (int i = 1; i <= lim; i++) pw[i] = pw[i - 1] * base;
}

struct Str_hash {
    vector<pii> v;

    Str_hash() {}

    // 下标 1 开始
    void init(const string &s) {
        int m = s.size() - 1;
        v.resize(m + 1);
        for (int j = 1; j <= m; j++) {
            char ch = s[j];
            v[j] = v[j - 1] * base + (pii) {ch, ch};
        }
    }

    pii get(int L, int R) {
        return v[R] - (v[L - 1] * pw[R - L + 1]);
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int M = 1e6 + 10;

int n;
string a[N];
Str_hash ha[N];
pii v[M];

pii get(int L, int R) {
    return v[R] - (v[L - 1] * pw[R - L + 1]);
}

void solve() {
    for (int i = 1; i <= n; i++) {
        ha[i].init(' ' + a[i]);
    }

    v[0] = {0, 0};
    for (int i = 1; i <= a[1].size(); i++) v[i] = ha[1].v[i];
    string ans = a[1];
    for (int i = 2; i <= n; i++) {
        int sz1 = ans.size(), sz2 = a[i].size();
        int mxl = min(sz1, sz2);

        for (int j = mxl; j >= 0; j--) {
            if (get(sz1 - j + 1, sz1) == ha[i].get(1, j)) {
                const string &ns = a[i].substr(j, sz2 - j);

                ans += ns;
                for (int k = 1; k <= ns.size(); k++) {
                    char ch = ns[k - 1];
                    v[sz1 + k] = v[sz1 + k - 1] * base + (pii) {ch, ch};
                }

                break;
            }
        }
    }
    cout << ans << "\n";
}

void prework() {
    init_strhash(1e6);
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