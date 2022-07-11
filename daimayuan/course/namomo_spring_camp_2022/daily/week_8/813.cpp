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

// region fenwick
template<int SZ>
struct Bit {
    int n;
    ll tr[SZ + 10];

    Bit() {
        init(SZ);
    }

    void init(int _n, ll v = 0) {
        n = _n;
        fill(tr, tr + n + 1, v);
    }

    void upd(int id, ll x) {
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll qr(int id) {
        ll res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }
};
// endregion

const int N = 1e5 + 10;

int n, q;
string s;
ti3 qs[N];

Bit<N> bit;

void solve() {
    sort(qs + 1, qs + q + 1, [](auto &a, auto &b) {
        return get<1>(a) < get<1>(b);
    });

    vector<int> stk;
    int pos = 1;
    bit.init(n, 0);
    vector<int> ans(q + 1);
    for (int i = 1; i <= q; i++) {
        auto [L, R, qid] = qs[i];
        while (pos <= R) {
            if (s[pos] == '(') {
                stk.push_back(pos);
            } else if (!stk.empty()) {
                bit.upd(stk.back(), 2);
                stk.pop_back();
            }
            pos++;
        }

        ans[qid] = bit.qr(R) - bit.qr(L - 1);
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
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
        cin >> n >> q;
        cin >> s;
        s = ' ' + s;
        for (int i = 1; i <= q; i++) {
            int L, R;
            cin >> L >> R;
            qs[i] = {L, R, i};
        }
        solve();
    }

    return 0;
}