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
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 110;

int n;
string str;

void solve() {
    unordered_set<int> st;
    int tt;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += str[k] - '0';
            }
            if (i == 1 && j == n) tt = sum;
            if (sum > 0) st.insert(sum);
        }
    }

    if (tt == 0 && str.size() - 1 >= 2) {
        cout << "YES" << "\n";
        return;
    }

    for (int x : st) {
        int flag = 0, i = 1;
        int cnt = 0;

        while (i <= n) {
            if (str[i] == '0') {
                i++;
                continue;
            }

            int sum = 0;
            while (i <= n && sum < x) sum += str[i++] - '0';
            if (sum != x) {
                flag = 1;
                break;
            }
            cnt++;
        }

        if (!flag && cnt >= 2) {
            cout << "YES" << "\n";
            return;
        }
    }

    cout << "NO" << "\n";
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
        cin >> n;
        cin >> str;
        str = ' ' + str;
        solve();
    }

    return 0;
}