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

int L, R;
int pr[N];

int pw(ll a, ll b, ll P) {
    ll res = 1;
    for (; b; b /= 2, a = a * a % P) {
        if (b % 2) {
            res = res * a % P;
        }
    }
    return int(res);
}

bool millerRabin(int n) {
    if (n == 2) return 1;
    if (pw(2, n - 1, n) == 1 && pw(4, n - 1, n) == 1) return 1;
    else return 0;
    return 1;
}

void solve() {
    vector<int> a;
    for (int i = L; i <= R; i++) {
        if (millerRabin(i)) a.push_back(i);
    }

    if (a.size() <= 1) {
        cout << "no";
        return;
    }

    int ci = 0, ans = 1e9, bi = 0, ans1 = 0;
    for (int i = 1; i < a.size(); i++) {
        if (a[i] - a[i - 1] < ans) {
            ans = a[i] - a[i - 1];
            ci = i;
        }

        if (a[i] - a[i - 1] > ans1) {
            ans1 = a[i] - a[i - 1];
            bi = i;
        }
    }
    printf("%d,%d are closest pair, %d,%d are most distant pair.", a[ci - 1], a[ci], a[bi - 1], a[bi]);
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
        cin >> L >> R;
        solve();
    }

    return 0;
}
