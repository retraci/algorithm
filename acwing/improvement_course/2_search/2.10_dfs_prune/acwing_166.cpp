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

string str;
char g[9][9];
int vx[9], vy[9], vc[3][3];

int lowbit(int x) {
    return x & -x;
}

int get(int x, int y) {
    return vx[x] & vy[y] & vc[x / 3][y / 3];
}

void init() {
    int lim = 1 << 9;
    for (int i = 0; i < 9; i++) vx[i] = lim - 1;
    for (int j = 0; j < 9; j++) vy[j] = lim - 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            vc[i][j] = lim - 1;
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            g[i][j] = str[i * 9 + j];

            if (g[i][j] != '.') {
                g[i][j]--;

                int x = g[i][j] - '0';
                vx[i] -= 1 << x, vy[j] -= 1 << x, vc[i / 3][j / 3] -= 1 << x;
            }
        }
    }
}

bool dfs(int cnt) {
    if (cnt == 0) return true;

    int mi = 10;
    int x, y;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (g[i][j] != '.') continue;

            int mask = get(i, j);
            int c = __builtin_popcount(mask);
            if (mi > c) mi = c, x = i, y = j;
        }
    }

    int mask = get(x, y);
    for (int i = mask; i; i -= lowbit(i)) {
        int tmp = lowbit(i);
        int cur = __lg(tmp);

        g[x][y] = cur + '0';
        vx[x] -= 1 << cur, vy[y] -= 1 << cur, vc[x / 3][y / 3] -= 1 << cur;

        if (dfs(cnt - 1)) return true;

        g[x][y] = '.';
        vx[x] += 1 << cur, vy[y] += 1 << cur, vc[x / 3][y / 3] += 1 << cur;
    }

    return false;
}

void solve() {
    init();

    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cnt += g[i][j] == '.';
        }
    }

    dfs(cnt);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << (char) (g[i][j] + 1);
        }
    }
    cout << endl;
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
    while (cin >> str, str != "end") {
        solve();
    }

    return 0;
}