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

const int N = 1e6 + 10;

int n;
ll a[N];
int p[N];

vector<pii> mx, mi;

int getpf(const vector<pii> &stk, int k, int x) {
    if (x == 0) return 0;

    int res = 0;
    int j = lower_bound(stk.begin(), stk.end(), (pii) {x, 0}) - stk.begin();
    res += stk[j - 1].se;
    res += (x - stk[j - 1].fi) * (k == p[stk[j].fi]);
    return res;
}

int get(const vector<pii> &stk, int k, int L, int R) {
    return getpf(stk, k, R) - getpf(stk, k, L - 1);
}

void solve() {
    for (int i = 1; i <= n; i++) p[i] = __builtin_popcountll(a[i]);

    ll ans = 0;
    for (int k = 0; k <= 60; k++) {
        mx = mi = {};
        mx.push_back({0, 0}), mi.push_back({0, 0});

        ll cnt = 0;
        for (int i = 1; i <= n; i++) {
            while (mx.size() >= 2 && a[i] > a[mx.back().fi]) {
                auto [id, s] = mx.back(); mx.pop_back();
                if (p[id] == k) {
                    cnt -= get(mi, k, mx.back().fi + 1, id);
                }
            }
            if (p[i] == k) {
                cnt += get(mi, k, mx.back().fi + 1, i - 1);
            }
            mx.push_back({i, mx.back().se + (i - mx.back().fi) * (k == p[i])});

            while (mi.size() >= 2 && a[i] < a[mi.back().fi]) {
                auto [id, s] = mi.back(); mi.pop_back();
                if (p[id] == k) {
                    cnt -= get(mx, k, mi.back().fi + 1, id);
                }
            }
            if (p[i] == k) {
                cnt += get(mx, k, mi.back().fi + 1, i);
            }
            mi.push_back({i, mi.back().se + (i - mi.back().fi) * (k == p[i])});

            ans += cnt;
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}