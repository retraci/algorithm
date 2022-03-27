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

const int N = 200010;

int n;
int a[N];

int b[N];

int lowbit(int x) {
    return x & -x;
}

void modify(int id, int x) {
    for (int i = id; i <= n; i += lowbit(i)) b[i] += x;
}

int query(int id) {
    int res = 0;
    for (int i = id; i; i -= lowbit(i)) res += b[i];
    return res;
}

void solve() {
    vector<int> cnt1(n + 1, 0), cnt2(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cnt1[i] = query(a[i] - 1), cnt2[i] = query(n) - query(a[i]);
        modify(a[i], 1);
    }

    fill(b, b + n + 1, 0);
    vector<int> cnt3(n + 1, 0), cnt4(n + 1, 0);
    for (int i = n; i >= 1; i--) {
        cnt3[i] = query(a[i] - 1), cnt4[i] = query(n) - query(a[i]);
        modify(a[i], 1);
    }

    ll ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++) {
        ans1 += 1LL * cnt2[i] * cnt4[i];
        ans2 += 1LL * cnt1[i] * cnt3[i];
    }
    cout << ans1 << " " << ans2 << "\n";
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