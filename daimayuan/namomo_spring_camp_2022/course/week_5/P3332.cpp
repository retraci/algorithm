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

// region 区间修改bit
template<int SZ>
struct Bit {
    int n;
    ll tr1[SZ + 1], tr2[SZ + 1];

    Bit() {
        init(SZ);
    }

    void init(int _n) {
        n = _n;
    }

    void add(ll tr[], int id, ll x) {
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll qr(ll tr[], int id) {
        int res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }

    ll get(int id) {
        return (id + 1) * qr(tr1, id) - qr(tr2, id);
    }

    void upd(int L, int R, ll x) {
        add(tr1, L, x), add(tr1, R + 1, -x);
        add(tr2, L, x * L), add(tr2, R + 1, -x * (R + 1));
    }

    ll sum(int L, int R) {
        return get(R) - get(L - 1);
    }
};
// endregion

typedef array<ll, 5> ai5;

const int N = 5e4 + 10;

int n, m;

ai5 q[N], q1[N], q2[N];
int ans[N], qc;

Bit<N> bit;

void work(int left, int right, int ql, int qr) {
    if (ql > qr) return;
    if (left == right) {
        for (int i = ql; i <= qr; i++) {
            auto [L, R, x, op, id] = q[i];

            if (op == 2) ans[id] = left;
        }
        return;
    }

    int md = left + right >> 1, c1 = 0, c2 = 0;
    for (int i = ql; i <= qr; i++) {
        auto &[L, R, x, op, id] = q[i];

        if (op == 1) {
            if (x > md) {
                bit.upd(L, R, 1);

                q2[++c2] = q[i];
            } else {
                q1[++c1] = q[i];
            }
        } else {
            ll cnt = bit.sum(L, R);

            if (cnt >= x) {
                q2[++c2] = q[i];
            } else {
                x -= cnt;
                q1[++c1] = q[i];
            }
        }
    }

    for (int i = 1; i <= c2; i++) {
        auto [L, R, x, op, id] = q2[i];

        if (op == 1) bit.upd(L, R, -1);
    }

    for (int i = 1; i <= c1; i++) q[ql + i - 1] = q1[i];
    for (int i = 1; i <= c2; i++) q[ql + c1 + i - 1] = q2[i];
    work(left, md, ql, ql + c1 - 1), work(md + 1, right, ql + c1, qr);
}

void solve() {
    bit.init(n);
    work(-n, n, 1, m);

    for (int i = 1; i <= qc; i++) cout << ans[i] << "\n";
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
            ll op, L, R, x;
            cin >> op >> L >> R >> x;
            if (op == 2) qc++;
            q[i] = {L, R, x, op, qc};
        }
        solve();
    }

    return 0;
}