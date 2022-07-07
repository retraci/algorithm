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

template<int SZ>
struct StrHash {
    pii v[SZ + 10];

    StrHash() {}

    // 下标 1 开始
    void init(const string &s) {
        int m = s.size() - 1;
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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e6 + 10;

int n;
string s;
StrHash<N> ha, rha;

pii get_rev(int L, int R) {
    return {n - R + 1, n - L + 1};
}

void solve() {
    ha.init(s), rha.init(' ' + string(s.rbegin(), s.rend() - 1));

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int L = 1, R = n - i;
        auto [rl, rr] = get_rev(L, R);

        if (ha.get(L, R) == rha.get(rl, rr)) {
            int len = R - L + 1;
            ans += len & 1 ? 26 : 1;
        } else {
            int left = 0, right = R - L + 1 >> 1;
            while (left < right) {
                int md = left + right + 1 >> 1;
                auto [t1, t2] = get_rev(R - md + 1, R);
                if (ha.get(L, L + md - 1) == rha.get(t1, t2)) left = md;
                else right = md - 1;
            }

            int x = L + left + 1, y = R - left - 1;
            auto [t1, t2] = get_rev(x, y);
            if (ha.get(x, y) == rha.get(t1, t2)) ans += 2;
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}