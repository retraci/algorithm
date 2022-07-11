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

const int N = 5e5 + 10;

int n, m;
int a[N], b[N];
pii qs[N];

int tr[N];

void add(int id, int x) {
    for (int i = id; i <= n; i += i & -i) tr[i] += x;
}

int qr(int id) {
    int res = 0;
    for (int i = id; i; i -= i & -i) res += tr[i];
    return res;
}

void solve() {
    vector<int> lst(n + 1, 0);
    stack<int> stk;
    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && (a[i] == a[stk.top()] || b[i] >= b[stk.top()])) stk.pop();
        lst[i] = stk.empty() ? 0 : stk.top();
        stk.push(i);
    }
    for (int i = 1; i <= n; i++) lst[i]++;

    vector<ti3> ask[n + 1];
    for (int i = 1; i <= m; i++) {
        auto [L, R] = qs[i];
        ask[L - 1].push_back({i, -1, lst[L]});
        ask[R].push_back({i, 1, lst[L]});
    }

    vector<int> ans(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        add(lst[i], 1);

        for (auto [qid, sign, x] : ask[i]) {
            ans[qid] += sign * qr(x);
        }
    }

    for (int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        for (int i = 1; i <= m; i++) cin >> qs[i].fi >> qs[i].se;
        solve();
    }

    return 0;
}