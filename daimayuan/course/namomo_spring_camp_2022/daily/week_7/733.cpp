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

// region 质因数分解, 枚举最小质数 (x < N)
vector<int> isp, mip, pr;

void prime(int lim) {
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

const int N = 1e6 + 10;
const int M = 1e7 + 10;

int n, m;
int a[N];
int cnt[M];

ll ksm(ll ta, ll k) {
    ll res = 1;
    while (k) {
        if (ta > 1e7) return 1e9;
        if (k & 1) {
            res *= ta;
            if (res > 1e7) return 1e9;
        }
        ta *= ta;
        k >>= 1;
    }
    return res;
}

void solve() {
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        ll cur = 1, need = 1;
        divide(x);
        for (auto [p, c] : fs) {
            c %= m;
            cur *= ksm(p, c);
            if (c) need *= ksm(p, m - c);
            if (need > 1e7) need = 0;
        }

        ans += cnt[need];
        cnt[cur]++;
    }
    cout << ans << "\n";
}

void prework() {
    prime(1e7);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}