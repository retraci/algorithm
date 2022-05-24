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
#include <cassert>
#include <random>
#include <cmath>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 51;

int n;
string g[N];
int f[N][N][N][N];

int dfs(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    if (f[x1][y1][x2][y2] != -1) return f[x1][y1][x2][y2];


    int res = max(x2 - x1 + 1, y2 - y1 + 1);

    for (int i = x1; i <= x2; i++) {
        int flag = 0;
        for (int j = y1; j <= y2; j++) {
            if (g[i][j] == '#') {
                flag = 1;
                break;
            }
        }

        if (!flag) res = min(res, dfs(x1, y1, i - 1, y2) + dfs(i + 1, y1, x2, y2));
    }

    for (int j = y1; j <= y2; j++) {
        int flag = 0;
        for (int i = x1; i <= x2; i++) {
            if (g[i][j] == '#') {
                flag = 1;
                break;
            }
        }

        if (!flag) res = min(res, dfs(x1, y1, x2, j - 1) + dfs(x1, j + 1, x2, y2));
    }

    return f[x1][y1][x2][y2] = res;
}

void solve() {
    fill(&f[0][0][0][0], &f[n][n][n][n] + 1, -1);

    int ans = dfs(1, 1, n, n);
    cout << ans << "\n";
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> g[i];
            g[i] = ' ' + g[i];
        }
        solve();
    }

    return 0;
}