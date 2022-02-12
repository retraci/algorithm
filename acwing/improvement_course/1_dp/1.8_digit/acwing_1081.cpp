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

const int N = 33;

ll L, R, K, B;

ll C[N][N];

ll calc(int a, int b) {
    if (a < 0 || b < 0 || a < b) return 0;
    return C[a][b];
}

ll work(int num) {
    if (num == 0) return 0;

    vector<int> va;
    while (num) va.push_back(num % B), num /= B;

    ll res = 0, lst = 0;
    for (int i = va.size() - 1; i >= 0; i--) {
        int x = va[i];

        if (x > 0) {
            if (x == 1) {
                res += calc(i, K - lst);
                lst++;
            } else {
                res += calc(i, K - lst) + calc(i, K - lst - 1);
                break;
            }
        }

        if (i == 0 && lst == K) res++;
    }

    return res;
}

void solve() {
    cout << work(R) - work(L - 1) << "\n";
}

void prework() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) C[i][j] = 1;
            else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
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
        cin >> L >> R >> K >> B;
        solve();
    }

    return 0;
}