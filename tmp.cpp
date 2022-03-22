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

struct Node {
    double w;
    ll a, b, c;
};

ll n, C, m;
vector<Node> a;
vector<ll> f;

void init() {
    sort(a.begin(), a.end(), [](auto &a, auto &b) {
        return a.w > b.w;
    });

    f = vector<ll>(C + 1, 0);
    for (auto &[d, x, y, z] : a) {
        ll p = y * z;
        ll s = p;
        for (ll j = x; j <= C; j += x) {
            if (s <= f[j]) break;

            f[j] = s;
            s += p;
        }
    }
    for (int i = 1; i <= C; i++) f[i] = max(f[i], f[i - 1]);
}

void solve() {
    init();

    cin >> m;
    while (m--) {
        ll x, y;
        cin >> x >> y;

        ll tmp = x * y;
        int pos = upper_bound(f.begin(), f.end(), tmp) - f.begin();
        cout << (pos == f.size() ? -1 : pos) << " ";
    }
    cout << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> C;
    a = vector<Node>(n);
    for (auto &[d, x, y, z] : a) {
        cin >> x >> y >> z;
        d = 1.0 * y * z / x;
    }
    solve();
    return 0;
}