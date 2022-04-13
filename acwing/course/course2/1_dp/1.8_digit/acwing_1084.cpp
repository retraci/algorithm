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
const int M = 110;

int L, R, P;
ll f[N][N][M];

ll work(int num) {
    if (num == 0) return 1;

    vector<int> va;
    while (num) va.push_back(num % 10), num /= 10;

    ll res = 0, lst = 0;
    for (int i = va.size() - 1; i >= 0; i--) {
        int x = va[i];

        for (int j = 0; j < x; j++) {
            int tmp = (-lst + P) % P;
            res += f[i + 1][j][tmp];
        }

        lst = (lst + x) % P;

        if (i == 0 && lst == 0) res++;
    }

    return res;
}

void init() {
    fill(&f[0][0][0], &f[N - 1][9][P - 1] + 1, 0);
    for (int i = 0; i <= 9; i++) f[1][i][i % P] = 1;

    for (int i = 2; i < N; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k < P; k++) {
                for (int q = 0; q <= 9; q++) {
                    int tmp = ((k - j) % P + P) % P;
                    f[i][j][k] += f[i - 1][q][tmp];
                }
            }
        }
    }
}

void solve() {
    init();
    cout << work(R) - work(L - 1) << "\n";
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
    while (cin >> L >> R >> P) {
        solve();
    }

    return 0;
}