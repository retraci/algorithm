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
mt19937 mrnd(time(0));

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
const int N = 1000010;

int n, q;
string s;
Str_hash ha, rha;

void solve() {
    ha.init(' ' + s), rha.init(' ' + string(s.rbegin(), s.rend()));

    while (q--) {
        int L, R;
        cin >> L >> R;

        if (ha.get(L, R) == rha.get(n - R + 1, n - L + 1)) {
            cout << "Budada" << "\n";
            continue;
        }

        int sz = R - L + 1;
        cout << (sz & 1 ? "Putata" : "Budada") << "\n";
    }
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
        cin >> n >> q;
        cin >> s;
        solve();
    }

    return 0;
}