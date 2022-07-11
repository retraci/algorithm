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

// region dsu
template <int SZ>
struct Dsu {
    int pa[SZ + 10];

    Dsu() {}

    void init(int n) {
        iota(pa, pa + n + 1, 0);
    }

    int find(int x) {
        return x == pa[x] ? x : pa[x] = find(pa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        pa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

const int N = 2e5 + 10;
const int MOD = 998244353;

int n;
int a[N], b[N];
Dsu<N> dsu;

void solve() {
    dsu.init(n);
    for (int i = 1; i <= n; i++) dsu.unite(a[i], b[i]);

    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) cnt[dsu.find(i)]++;
    int mx = *max_element(cnt.begin() + 1, cnt.end());

    int f[mx + 1][2][2];
    memset(f, 0, sizeof f);
    f[1][0][0] = f[1][1][1] = 1;
    for (int i = 2; i <= mx; i++) {
        for (int j = 0; j <= 1; j++) {
            f[i][j][0] = f[i - 1][j][1];
            f[i][j][1] = (f[i - 1][j][0] + f[i - 1][j][1]) % MOD;
        }
    }

    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        int tx = dsu.find(i);
        if (i == tx) {
            int sz = cnt[i];
            ans *= (1LL * f[sz][0][1] + f[sz][1][0] + f[sz][1][1]) % MOD;
            ans %= MOD;
        }
    }
    cout << ans << "\n";
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}