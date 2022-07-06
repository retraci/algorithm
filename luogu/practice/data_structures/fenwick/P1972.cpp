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

const int N = 1e6 + 10;

int n, m;
int a[N];
ti3 qs[N];
int lst[N];

int bit[N];

void add(int id, int x) {
    for (int i = id; i <= n; i += i & -i) bit[i] += x;
}

int query(int id) {
    int res = 0;
    for (int i = id; i; i -= i & -i) res += bit[i];
    return res;
}

void solve() {
    sort(qs + 1, qs + m + 1, [](auto &a, auto &b) {
        return get<1>(a) < get<1>(b);
    });

    vector<int> ans(m + 1, 0);
    int pos = 1;
    for (int i = 1; i <= m; i++) {
        auto [L, R, id] = qs[i];
        while (pos <= R) {
            int x = a[pos];
            if (lst[x]) add(lst[x], -1);
            add(pos, 1);
            lst[x] = pos++;
        }

        ans[id] = query(R) - query(L - 1);
    }

    for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
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
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int L, R;
            cin >> L >> R;
            qs[i] = {L, R, i};
        }

        solve();
    }

    return 0;
}