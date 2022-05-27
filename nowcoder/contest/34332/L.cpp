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

vector<pii> pw;
pii base;

void init_hash(int lim = 0) {
    pw = vector<pii>(lim + 1);
    base = {rnd(mod1), rnd(mod2)};
    pw[0] = {1, 1};
    for (int i = 1; i <= lim; i++) pw[i] = pw[i - 1] * base;
}
// endregion

// region 字符串哈希
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
const int N = 5e5 + 10;

int n;
string s1, s2;
string t1, t2, t3, t4;
int a, b;
Str_hash ha1, ha2, ha3, ha4;

bool check(int u) {
    int d = (n - u) % n + 1;

    auto tar = ha2.get(1, n);
    if (ha1.get(d, d + n - 1) == tar) return true;
    if (ha3.get(d, d + n - 1) == tar) return true;
    if (ha4.get(d, d + n - 1) == tar) return true;

    return false;
}

void solve() {
    n = s1.size();

    string rsa1 = s1.substr(0, a), rsa2 = s1.substr(a);
    reverse(rsa1.begin(), rsa1.end()), reverse(rsa2.begin(), rsa2.end());
    string rsb1 = s1.substr(0, b), rsb2 = s1.substr(b);
    reverse(rsb1.begin(), rsb1.end()), reverse(rsb2.begin(), rsb2.end());

    t1 = ' ' + s1 + s1;
    t2 = ' ' + s2;
    t3 = ' ' + rsa1 + rsa2 + rsa1 + rsa2;
    t4 = ' ' + rsb1 + rsb2 + rsb1 + rsb2;
    ha1.init(t1), ha2.init(t2), ha3.init(t3), ha4.init(t4);

    int gap = abs(a - b);
    vector<int> vis(n);
    int u = 0;
    while (1) {
        if (vis[u]) break;

        vis[u] = 1;
        if (check(u)) {
            cout << "yes" << "\n";
            return;
        }
        u = (u + gap) % n;
    }

    cout << "no" << "\n";
}

void prework() {
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
    cin >> _;
    while (_--) {
        cin >> s1 >> s2;
        cin >> a >> b;
        solve();
    }

    return 0;
}