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

int L, R, k;

int isp[N];
int pr[N], pc;
int s[N];

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);
    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) pr[++pc] = i;

        for (int j = 1; j <= pc; j++) {
            if (pr[j] > lim / i) break;

            isp[i * pr[j]] = 0;
            if (i % pr[j] == 0) break;
        }
    }
}

bool check(int md) {
    int flag = 0;
    for (int i = L; i <= R - md + 1; i++) {
        if (s[i + md - 1] - s[i - 1] < k) flag = 1;
    }

    return flag == 0;
}

void solve() {
    int left = max(1, k), right = R - L + 1 + 1;
    while (left < right) {
        int md = left + right >> 1;
        if (check(md)) right = md;
        else left = md + 1;
    }

    if (left == R - L + 1 + 1) cout << -1 << "\n";
    else cout << left << "\n";
}

void prework() {
    prime(1e6);
    for (int i = 1; i <= 1e6; i++) s[i] = s[i - 1] + isp[i];
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
        cin >> L >> R >> k;
        solve();
    }

    return 0;
}