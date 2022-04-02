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

const int N = 3e5 + 10;

int n, Q;
int x[N], w[N];
ti3 qs[N];

ll bit[N];

void upd(int id, ll v) {
    for (int i = id; i <= n; i += i & -i) bit[i] = min(bit[i], v);
}

ll qr(int id) {
    ll res = 5e18;
    for (int i = id; i; i -= i & -i) res = min(res, bit[i]);
    return res;
}

void solve() {
    sort(qs + 1, qs + Q + 1, [](auto &a, auto &b) {
        return get<1>(a) < get<1>(b);
    });

    vector<ll> ans(Q + 1);
    fill(bit, bit + n + 1, 5e18);
    vector<int> stk;
    int pos = 1;
    for (int i = 1; i <= Q; i++) {
        auto[L, R, qid] = qs[i];

        while (pos <= R) {
            int tx = x[pos], tw = w[pos];
            while (!stk.empty() && w[stk.back()] >= tw) {
                int id = stk.back(); stk.pop_back();
                ll tmp = 1LL * (tx - x[id]) * (w[id] + tw);

                upd(n - id + 1, tmp);
            }
            if (!stk.empty()) {
                int id = stk.back();
                ll tmp = 1LL * (tx - x[id]) * (w[id] + tw);

                upd(n - id + 1, tmp);
            }

            stk.push_back(pos++);
        }

        ans[qid] = qr(n - L + 1);
    }

    for (int i = 1; i <= Q; i++) cout << ans[i] << "\n";
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
        cin >> n >> Q;
        for (int i = 1; i <= n; i++) cin >> x[i] >> w[i];
        for (int i = 1; i <= Q; i++) {
            int L, R;
            cin >> L >> R;
            qs[i] = {L, R, i};
        }
        solve();
    }

    return 0;
}