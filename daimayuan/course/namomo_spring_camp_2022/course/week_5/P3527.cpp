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

typedef array<int, 5> ai5;

int n, m, k;
int a[N];
vector<int> b[N];
ti3 c[N];

int tt;
ai5 q[2 * N], q1[2 * N], q2[2 * N];
int ans[N];

ll tr[2 * N];

void add(int id, ll x) {
    for (int i = id; i <= 2 * m; i += i & -i) tr[i] += x;
}

ll query(int id) {
    ll res = 0;
    for (int i = id; i; i -= i & -i) res += tr[i];
    return res;
}

void work(int left, int right, int ql, int qr) {
    if (ql > qr) return;
    if (left == right) {
        for (int i = ql; i <= qr; i++) {
            auto [L, R, x, op, id] = q[i];

            if (op) ans[id] = left;
        }
        return;
    }

    int md = left + right >> 1, c1 = 0, c2 = 0;
    for (int i = ql; i <= qr; i++) {
        auto &[L, R, x, op, id] = q[i];

        if (!op) {
            if (id <= md) {
                add(L, x), add(R + 1, -x);

                q1[++c1] = q[i];
            } else {
                q2[++c2] = q[i];
            }
        } else {
            ll sum = 0;
            for (int p : b[id]) {
                sum += query(p) + query(p + m);
                if (sum >= x) break;
            }

            if (sum >= x) {
                q1[++c1] = q[i];
            } else {
                x -= sum;
                q2[++c2] = q[i];
            }
        }
    }

    for (int i = 1; i <= c1; i++) {
        auto &[L, R, x, op, id] = q1[i];

        if (!op) add(L, -x), add(R + 1, x);
    }
    for (int i = 1; i <= c1; i++) q[ql + i - 1] = q1[i];
    for (int i = 1; i <= c2; i++) q[ql + c1 + i - 1] = q2[i];
    work(left, md, ql, ql + c1 - 1), work(md + 1, right, ql + c1, qr);
}

void init() {
    for (int i = 1; i <= k; i++) {
        auto [L, R, x] = c[i];
        q[++tt] = {L, R, x, 0, i};
    }

    for (int i = 1; i <= n; i++) {
        q[++tt] = {0, 0, a[i], 1, i};
    }
}

void solve() {
    init();

    work(0, k + 1, 1, tt);

    for (int i = 1; i <= n; i++) {
        if (ans[i] == k + 1) cout << "NIE" << "\n";
        else cout << ans[i] << "\n";
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
        for (int i = 1; i <= m; i++) {
            int x;
            cin >> x;
            b[x].push_back(i);
        }
        for (int i = 1; i <= n; i++) cin >> a[i];

        cin >> k;
        for (int i = 1; i <= k; i++) {
            int L, R, x;
            cin >> L >> R >> x;
            if (L > R) R += m;

            c[i] = {L, R, x};
        }

        solve();
    }

    return 0;
}