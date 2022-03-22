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

// region 自然溢出字符串hash
const ull P = 10000721;

int n;
string s;
ull h[N], p[N];

ull get(int L, int R) {
    return h[R] - h[L - 1] * p[R - L + 1];
}

void init_hash() {
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * P + s[i];
        p[i] = p[i - 1] * P;
    }
}
// endregion

void solve() {
    init_hash();
    ll cnt = 0, lef = n;
    ll c1 = 0, len = 0, flag = 0;
    ull c2 = 0;

    for (int i = 1; i <= n; i++) {
        c1 += s[i] == '(' ? 1 : -1;
        if (c1 < 0) flag = 1;
        c2 += s[i] * p[len];
        len++;

        if (!flag && c1 == 0 || len >= 2 && c2 == get(i - len + 1, i)) {
            lef -= len, cnt++;
            len = 0, c1 = 0, c2 = 0, flag = 0;
        }
    }

    cout << cnt << " " << lef << "\n";
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
    cin >> T;
    while (T--) {
        cin >> n >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}