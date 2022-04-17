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

const int N = 2e5 + 10;

int n;
int a[N];

ll b[N];

int lowbit(int x) {
    return x & -x;
}

ll qr(int id) {
    ll res = 0;
    for (int i = id; i; i -= lowbit(i)) res += b[i];
    return res;
}

void upd(int id, ll x) {
    for (int i = id; i <= n; i += lowbit(i)) b[i] += x;
}

void solve() {
    fill(b, b + n + 1, 0);
    for (int i = 1; i <= n; i++) {
        upd(i, a[i]), upd(i + 1, -a[i]);
    }

    int c = accumulate(a + 1, a + n + 1, 0LL) / n;
    vector<int> ans(n + 1);
    for (int i = n; i >= 2; i--) {
        int R = i, L = R - c + 1;
        upd(L, -1), upd(R + 1, 1);
        if (qr(i)) ans[i] = 1, c--;
    }
    ans[1] = qr(1);

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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