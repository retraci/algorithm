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
const double eps = 1e-5;

int n;
int a[N];

bool check1(double mid) {
    double f[n + 1][2];
    fill(&f[0][0], &f[n][2], -1e18);

    f[0][0] = f[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        double tmp = a[i] - mid;

        f[i][0] = f[i - 1][1];
        f[i][1] = max(f[i - 1][0], f[i - 1][1]) + tmp;
    }

    return max(f[n][0], f[n][1]) >= 0;
}

bool check2(int mid) {
    int f[n + 1][2];
    fill(&f[0][0], &f[n][2], -1e9);

    f[0][0] = f[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        int tmp = a[i] >= mid ? 1 : -1;

        f[i][0] = f[i - 1][1];
        f[i][1] = max(f[i - 1][0], f[i - 1][1]) + tmp;
    }

    return max(f[n][0], f[n][1]) > 0;
}

void solve() {
    {
        double left = 0, right = 1e9;
        while (left + eps < right) {
            double mid = (left + right) / 2;
            if (check1(mid)) left = mid;
            else right = mid;
        }

        cout << left << "\n";
    }

    {
        int left = 1, right = 1e9;
        while (left < right) {
            int mid = left + right + 1 >> 1;
            if (check2(mid)) left = mid;
            else right = mid - 1;
        }

        cout << left << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}