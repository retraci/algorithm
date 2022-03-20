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

int n, Q, P;
ll a[N], b[N], c[N], d[N];
int fib[N];
int cnt;

void init() {
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= n + 1; i++) fib[i] = (fib[i - 1] + fib[i - 2]) % P;
}

void upd(int id, int v) {
    if (id <= 0 || id > n) return;

    if (d[id] == 0) cnt--;
    d[id] += v;
    d[id] = (d[id] % P + P) % P;
    if (d[id] == 0) cnt++;
}

void solve() {
    init();

    for (int i = 1; i <= n; i++) {
        c[i] = a[i] - b[i];
        c[i] = (c[i] % P + P) % P;
    }
    d[1] = c[1];
    cnt += d[1] == 0;
    for (int i = 2; i <= n; i++) {
        d[i] = c[i] - c[i - 1] - c[i - 2];
        d[i] = (d[i] % P + P) % P;
        cnt += d[i] == 0;
    }

    while (Q--) {
        string op;
        int L, R;
        cin >> op >> L >> R;
        if (op == "A") {
            upd(L, 1);
            upd(R + 1, -fib[R - L + 2]);
            upd(R + 2, -fib[R - L + 1]);
        } else {
            upd(L, -1);
            upd(R + 1, fib[R - L + 2]);
            upd(R + 2, fib[R - L + 1]);
        }

        cout << (cnt == n ? "Yes" : "No") << "\n";
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
        cin >> n >> Q >> P;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}