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

const int N = 1e6 + 10;

int n;
int o[N], d[N];

void solve() {
    vector<int> ans(n + 1, 0);

    // 顺时针
    {
        vector<ll> s(2 * n + 1, 0);
        for (int i = 1; i <= n; i++) s[i] = s[i + n] = o[i] - d[i];
        for (int i = 1; i <= 2 * n; i++) s[i] += s[i - 1];
        deque<int> que;
        for (int i = 2 * n; i >= 1; i--) {
            while (!que.empty() && que.front() - i + 1 > n) que.pop_front();
            while (!que.empty() && s[que.back()] >= s[i]) que.pop_back();
            que.push_back(i);
            if (i <= n) ans[i] |= s[que.front()] - s[i - 1] >= 0;
        }
    }
    // 逆时针
    {
        vector<ll> s(2 * n + 1, 0);
        d[0] = d[n];
        for (int i = 1; i <= n; i++) s[i] = s[i + n] = o[i] - d[i - 1];
        for (int i = 1; i <= 2 * n; i++) s[i] += s[i - 1];
        deque<int> que;
        for (int i = 1; i <= 2 * n; i++) {
            while (!que.empty() && i - que.front() > n) que.pop_front();
            if (i > n) ans[i - n] |= s[i] - s[que.front()] >= 0;
            while (!que.empty() && s[que.back()] <= s[i]) que.pop_back();
            que.push_back(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << (ans[i] ? "TAK" : "NIE") << "\n";
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
        for (int i = 1; i <= n; i++) cin >> o[i] >> d[i];
        solve();
    }

    return 0;
}