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

const int N = 110;
const int M = 10010;

int n;
int va[N], vb[N];
int f[N][M];
int pre[N][M];

void solve() {
    fill(&f[0][0], &f[n][M - 1] + 1, 0);

    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < M; j++) {
            if (j - va[i] >= 0 && f[i - 1][j - va[i]]) {
                f[i][j] |= f[i - 1][j - va[i]];
                pre[i][j] = j - va[i];
            }
            if (j - vb[i] >= 0 && f[i - 1][j - vb[i]]) {
                f[i][j] |= f[i - 1][j - vb[i]];
                pre[i][j] = j - vb[i];
            }
        }
    }

    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += va[i] + vb[i];
    int mi = 1e9, t;
    for (int j = 0; j < M; j++) {
        if (!f[n][j]) continue;
        int a = j, b = sum - a;
        int del = abs(a - b);
        if (del < mi) {
            mi = del;
            t = j;
        }
    }

    vector<int> cho(n + 1, 0);
    for (int i = n; i >= 1; i--) {
        int nt = pre[i][t];
        if (t - nt == va[i]) cho[i] = 1;
        t = nt;
    }

    vector<int> vc(n + 1, 0), vd(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (cho[i]) vc[i] = va[i], vd[i] = vb[i];
        else vc[i] = vb[i], vd[i] = va[i];
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            ans += (vc[i] + vc[j]) * (vc[i] + vc[j]);
            ans += (vd[i] + vd[j]) * (vd[i] + vd[j]);
        }
    }
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
    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= n; i++) cin >> vb[i];
        solve();
    }

    return 0;
}