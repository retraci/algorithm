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

int A[1000005] = {0}, B[1000005] = {0}, C[1000005] = {0};

void solve() {
    string a, b;
    cin >> a >> b;

    bool flag = false;
    if (a == b) cout << "0";
    int alen = a.length();
    int blen = b.length();
    if (alen < blen) {
        swap(a, b);
        flag = true;
    } else if (alen == blen) {
        if (b > a) {
            swap(a, b);
            flag = true;
        }
    }
    alen = a.length();
    blen = b.length();
    for (int i = 0; i <= alen; i++) {
        A[alen - i] = a[i] - '0';
    }
    for (int j = 0; j <= blen; j++) {
        B[blen - j] = b[j] - '0';
    }
    int clen = 1;
    while (clen <= alen) {
        C[clen] = A[clen] - B[clen];
        if (C[clen] < 0) {
            while (C[clen] < 0) {
                C[clen] += 10;
                A[clen + 1]--;
            }
        }
        clen++;
    }
    while (C[clen] == 0) clen--;
    if (flag) cout << "-";
    for (int t = clen; t > 0; t--) cout << C[t];
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
        solve();
    }

    return 0;
}
