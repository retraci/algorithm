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
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 3e5 + 10;

int n, s;
int vt[N], vc[N];

void solve() {
    ll st[n + 1], sc[n + 1];
    st[0] = sc[0] = 0;
    for (int i = 1; i <= n; i++) {
        st[i] = st[i - 1] + vt[i];
        sc[i] = sc[i - 1] + vc[i];
    }

    ll f[n + 1];
    f[0] = 0;
    deque<int> que;
    que.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (que.size() >= 2) {
            int j1 = que[0];
            int j2 = que[1];
            if ((f[j2] - f[j1]) > ((__int128) (sc[j2] - sc[j1]) * (st[i] + s))) break;
            que.pop_front();
        }

        int j = que.front();
        f[i] = f[j] + (sc[i] - sc[j]) * st[i] + s * (sc[n] - sc[j]);

        while (que.size() >= 2) {
            int j1 = que[que.size() - 1];
            int j2 = que[que.size() - 2];
            if (((__int128) (f[j1] - f[j2]) * (sc[i] - sc[j2])) < ((__int128) (f[i] - f[j2]) * (sc[j1] - sc[j2]))) break;
            que.pop_back();
        }
        que.push_back(i);
    }
    cout << f[n] << "\n";
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
        cin >> n >> s;
        for (int i = 1; i <= n; i++) cin >> vt[i] >> vc[i];
        solve();
    }

    return 0;
}