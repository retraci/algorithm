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

const int N = 6e5 + 10;

// region 可持久化 01trie
int a[N];

template<int N, int SZ, int B>
struct Trie {
    int tr[SZ][2], mx_id[SZ], mem;
    int root[N + 1];

    inline Trie() {
        init();
    }

    inline void init() {
        root[0] = 0, mem = 0;
        tr[0][0] = tr[0][1] = mx_id[0] = 0;
    }

    inline int new_node() {
        int id = ++mem;
        tr[id][0] = tr[id][1] = mx_id[id] = 0;
        return id;
    }

    inline void insert(int id) {
        int k = root[id] = new_node();
        int p = id - 1 >= 0 ? root[id - 1] : 0;
        for (int i = B; i >= 0; i--) {
            int v = a[id] >> i & 1;
            tr[k][v] = new_node();
            if (p) {
                tr[k][v ^ 1] = tr[p][v ^ 1];
                p = tr[p][v];
            }
            mx_id[tr[k][v]] = id;
            k = tr[k][v];
        }
    }

    inline int query(int x, int L, int R) {
        int k = root[R];
        for (int i = B; i >= 0; i--) {
            int v = x >> i & 1;
            if (tr[k][v ^ 1] && mx_id[tr[k][v ^ 1]] >= L) k = tr[k][v ^ 1];
            else k = tr[k][v];
        }

        return x ^ a[mx_id[k]];
    }
};
// endregion

int n, Q;

Trie<N, N * 24, 24> tr;

void solve() {
    for (int i = 1; i <= n; i++) a[i] ^= a[i - 1];

    tr.init();
    for (int i = 0; i <= n; i++) tr.insert(i);
    while (Q--) {
        string op;
        cin >> op;
        if (op == "A") {
            int x;
            cin >> x;

            a[++n] = x;
            a[n] ^= a[n - 1];
            tr.insert(n);
        } else {
            int L, R, x;
            cin >> L >> R >> x;

            cout << tr.query(x ^ a[n], L - 1, R - 1) << "\n";
        }
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
        cin >> n >> Q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}