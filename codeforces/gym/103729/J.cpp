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

int n;
string s;
Str_hash ha1, ha2;

void work2(string ss, int st, int flag) {
    string rs = string(ss.rbegin(), ss.rend());
    ha1.init(' ' + ss), ha2.init(' ' + rs);

    ss = ' ' + ss;
    int m = ss.size() - 1;
    for (int i = 0; i <= m / 2; i++) {
        pii hash1 = ha1.get(1, 1 + i - 1), hash2 = ha1.get(m - i + 1, m);
        if (hash1 != hash2) continue;

        int L1 = 1 + i, R1 = m - i;
        int L2 = m - R1 + 1, R2 = m - L1 + 1;
        hash1 = ha1.get(L1, R1), hash2 = ha2.get(L2, R2);
        if (hash1 == hash2) {
            int al = st + 1, ar = st + 1 + i - 1;
            if (flag) {
                int t1 = n - ar + 1, t2 = n - al + 1;
                al = t1, ar = t2;
            }

            cout << al << " " << ar << "\n";
            exit(0);
        }
    }
}

void work(string ss, int st, int flag) {
    string rs = string(ss.rbegin(), ss.rend());
    ha1.init(' ' + ss), ha2.init(' ' + rs);

    ss = ' ' + ss;
    int m = ss.size() - 1;
    for (int i = 0; i <= m / 2; i++) {
        pii hash1 = ha1.get(1, 1 + i - 1), hash2 = ha1.get(1 + i, 1 + i + i - 1);
        if (hash1 != hash2) continue;

        int L1 = 1 + 2 * i, R1 = m;
        int L2 = m - R1 + 1, R2 = m - L1 + 1;
        hash1 = ha1.get(L1, R1), hash2 = ha2.get(L2, R2);
        if (hash1 == hash2) {
            int al = st + i + 1, ar = st + m;
            if (flag) {
                int t1 = n - ar + 1, t2 = n - al + 1;
                al = t1, ar = t2;
            }

            cout << al << " " << ar << "\n";
            exit(0);
        }
    }
}

void solve() {
    int st;
    {
        n = s.size() - 1;
        int i = 1, j = n;
        while (i <= j) {
            if (s[i] != s[j]) break;
            i++, j--;
        }

        if (i > j) {
            cout << 1 << " " << n << "\n";
            return;
        }

        st = i - 1;
        s = s.substr(i, j - i + 1);
    }

    work(s, st, 0);
    work2(s, st, 0);
    reverse(s.begin(), s.end());
    work(s, st, 1);
    work2(s, st, 1);
    cout << -1 << " " << -1 << "\n";
}

void prework() {
    init_strhash(1e5);
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}