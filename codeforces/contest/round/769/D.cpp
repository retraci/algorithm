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

int st[N][22];

void init_st() {
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            int ta = st[i][k - 1];
            int tb = st[i + (1 << (k - 1))][k - 1];

            st[i][k] = __gcd(ta, tb);
        }
    }
}

int qr(int L, int R) {
    int k = __lg(R - L + 1);
    int res = __gcd(st[L][k], st[R - (1 << k) + 1][k]);
    return res;
}

bool check(int L, int R) {
    int gcd = qr(L, R);
    int len = R - L + 1;
    return gcd - len >= 0;
}

void solve() {
    init_st();

    vector<int> ans(n + 1);
    int pre = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            cnt++, pre = i;
        } else {
            int left = pre + 1, right = i;
            while (left < right) {
                int md = left + right >> 1;
                if (check(md, i)) right = md;
                else left = md + 1;
            }

            int gcd = qr(left, i);
            int len = i - left + 1;
            if (gcd - len == 0) cnt++, pre = i;
        }

        ans[i] = cnt;
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
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