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
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 15;

int L, R;
ll f[N][N];

ll work(int num) {
    if (num == 0) return 0;

    vector<int> va;
    while (num) va.push_back(num % 10), num /= 10;

    ll res = 0;
    for (int i = 1; i < va.size(); i++) {
        for (int j = 1; j <= 9; j++) {
            res += f[i][j];
        }
    }

    int lst = -2;
    for (int i = va.size() - 1; i >= 0; i--) {
        int x = va[i];

        for (int j = 0; j < x; j++) {
            if (j == 0 && i == va.size() - 1) continue;
            if (abs(j - lst) >= 2) res += f[i + 1][j];
        }

        if (abs(lst - x) < 2) break;
        lst = x;

        if (i == 0) res++;
    }

    return res;
}

void solve() {
    cout << work(R) - work(L - 1) << "\n";
}

void prework() {
    for (int i = 0; i <= 9; i++) f[1][i] = 1;

    for (int i = 2; i < N; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (abs(j - k) >= 2) f[i][j] += f[i - 1][k];
            }
        }
    }
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
        cin >> L >> R;
        solve();
    }

    return 0;
}