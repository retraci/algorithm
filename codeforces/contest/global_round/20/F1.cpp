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

const int N = 2e5 + 10;

int n;
int a[N];

void solve() {
    map<int, queue<int>> mp;
    for (int i = 1; i <= n; i++) mp[a[i]].push(i);

    vector<int> ans(n + 1, 0);
    while (!mp.empty()) {
        vector<pii> tmp;
        for (auto it = mp.begin(); it != mp.end(); ) {
            auto &[v, q] = *it;
            if (q.empty()) {
                it = mp.erase(it);
            } else {
                int id = q.front(); q.pop();
                tmp.push_back({v, id});
                it++;
            }
        }
        if (tmp.empty()) break;

        for (int i = 1; i < tmp.size(); i++) {
            auto [v1, id1] = tmp[i - 1];
            auto [v2, id2] = tmp[i];
            ans[id1] = v2;
        }
        ans[tmp.back().se] = tmp[0].fi;
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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
    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}