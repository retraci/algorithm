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

int n, p, q;
ll a[N], s[N];
int idx[N];

bool work(ll mx, ll sum, ll len) {
    return mx * q * len <= sum * p;
}

bool check(int mid) {
    for (int i = mid; i <= n; i++) {
        ll mx = a[idx[i]];
        ll sum = s[i] - s[i - mid];
        if (work(mx, sum, mid)) return true;
    }

    return false;
}

void solve() {
    iota(idx, idx + n + 1, 0);
    sort(idx + 1, idx + n + 1, [&](auto &lhs, auto &rhs) {
        return a[lhs] < a[rhs];
    });
    for (int i = 1; i <= n; i++) s[i] = a[idx[i]];
    for (int i = 1; i <= n; i++) s[i] += s[i - 1];

    int left = 0, right = n;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    int len = left;
    vector<int> d(n + 2, 0);
    for (int i = len; i <= n; i++) {
        ll mx = a[idx[i]];
        if (!work(mx, s[i] - s[i - len], len)) continue;

        left = 1, right = i - len + 1;
        ll sum = s[i] - s[i - len + 1];
        while (left < right) {
            int mid = left + right >> 1;
            if (work(mx, sum + a[idx[mid]], len)) right = mid;
            else left = mid + 1;
        }

        d[left]++, d[i + 1]--;
    }

    for (int i = 1; i <= n; i++) d[i] += d[i - 1];
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (d[i]) continue;
        ans.push_back(idx[i]);
    }

    cout << ans.size() << "\n";
    sort(ans.begin(), ans.end());
    for (int x : ans) cout << x << " ";
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
//    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        cin >> p >> q;
        solve();
    }

    return 0;
}