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

// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

// region fenwick
template<int SZ>
struct Bit {
    int n;
    ll tr[SZ + 10];

    Bit() {
        init(SZ);
    }

    void init(int _n, ll v = 0) {
        n = _n;
        fill(tr, tr + n + 1, v);
    }

    void upd(int id, ll x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = max(tr[i], x);
    }

    ll qr(int id) {
        ll res = -1e9;
        for (int i = id; i; i -= i & -i) res = max(res, tr[i]);
        return res;
    }
};
// endregion

const int N = 5e5 + 10;

int n;
ll a[N], s[N];
int nl;
vector<ll> lsh;

Bit<N> bit;

int get(ll x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
    lsh = {};
    for (int i = 0; i <= n; i++) lsh.push_back(s[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();
    for (int i = 0; i <= n; i++) s[i] = get(s[i]) + 1;
}

void solve() {
    init();
    bit.init(nl, -1e9);

    vector<ll> f(n + 1, -1e9);
    vector<ll> mx(nl + 1, -1e9);
    bit.upd(s[0], 0);
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        int tmp = 0;
        if (a[i] > 0) tmp = 1;
        else if (a[i] < 0) tmp = -1;
        f[i] = f[i - 1] + tmp;

        ll t1 = bit.qr(s[i] - 1);
        f[i] = max(f[i], i + t1);
        f[i] = max(f[i], mx[s[i]]);

        bit.upd(s[i], f[i] - i);
        mx[s[i]] = max(mx[s[i]], f[i]);
    }

    cout << f[n] << "\n";
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
    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}