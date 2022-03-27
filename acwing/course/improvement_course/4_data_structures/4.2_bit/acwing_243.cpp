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

const int N = 1e5 + 10;

int n, m;
int a[N];

ll b1[N], b2[N];

int lowbit(int x) {
    return x & -x;
}

ll query(ll b[], int id) {
    ll res = 0;
    for (int i = id; i; i -= lowbit(i)) res += b[i];
    return res;
}

void modify(ll b[], int id, ll x) {
    for (int i = id; i <= n; i += lowbit(i)) b[i] += x;
}

ll query(int id) {
    return 1LL * (id + 1) * query(b1, id) - query(b2, id);
}

void solve() {
    for (int i = 1; i <= n; i++) {
        modify(b1, i, a[i] - a[i - 1]);
        modify(b2, i, 1LL * i * (a[i] - a[i - 1]));
    }
    while (m--) {
        string op;
        cin >> op;
        if (op == "C") {
            int L, R, x;
            cin >> L >> R >> x;
            modify(b1, L, x), modify(b2, L, 1LL * L * x);
            modify(b1, R + 1, -x), modify(b2, R + 1, 1LL * (R + 1) * -x);
        } else {
            int L, R;
            cin >> L >> R;
            cout << query(R) - query(L - 1) << "\n";
        }
    }
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}