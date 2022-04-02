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

const int N = 310;

int n;
int a[N], b[N], d[N];
vector<int> lsh;

int get_id(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    lsh = {};
    for (int i = 1; i <= n; i++) {
        lsh.push_back(a[i]);
        lsh.push_back(b[i]);
    }

    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());

    for (int i = 1; i <= n; i++) {
        a[i] = get_id(a[i]) + 1;
        b[i] = get_id(b[i]) + 1;
    }
}

void solve() {
    init();

    int nl = lsh.size();
    int f[nl + 1][nl + 1];
    memset(f, 0x3f, sizeof f);
    for (int L = 0; L <= nl; L++) {
        for (int R = 0; R < L; R++) {
            f[L][R] = 0;
        }
    }
    for (int len = 1; len <= nl; len++) {
        for (int L = 1; L + len - 1 <= nl; L++) {
            int R = L + len - 1;

            int mx = -1, id = -1;
            for (int i = 1; i <= n; i++) {
                if (a[i] >= L && b[i] <= R) {
                    if (d[i] > mx) {
                        mx = d[i];
                        id = i;
                    }
                }
            }
            if (id == -1) {
                f[L][R] = 0;
                continue;
            }

            for (int i = a[id]; i <= b[id]; i++) {
                f[L][R] = min(f[L][R], f[L][i - 1] + f[i + 1][R] + d[id]);
            }
        }
    }

    cout << f[1][nl] << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> d[i];

        solve();
    }

    return 0;
}