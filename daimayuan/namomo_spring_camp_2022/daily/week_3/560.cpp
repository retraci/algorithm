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

string sa, sb;

bool check(string &t, int cnt, int cb[]) {
    string str = "";
    for (int i = 0; i < sb.size(); i++) {
        cb[sb[i] - '0']--;
        if (sb[i] == '0') {
            if (--cnt == 0) {
                str = sb.substr(i + 1, sb.size() - i - 1);
                break;
            }
        }
    }

    int j = 0;
    for (char ch : str) {
        if (j < t.size() && ch == t[j]) {
            j++;
        } else {
            cb[ch - '0']--;
        }
    }
    for (int i = 0; i <= 9; i++) {
        if (cb[i] != 0) return false;
    }
    return j == t.size();
}

void solve() {
    int n = sa.size();
    int lim = 1 << n;

    ull a = stoull(sa), b = stoull(sb);
    ull up = a, down = b;
    for (int mask = 0; mask < lim; mask++) {
        int ca[10] = {0};
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) ca[sa[i] - '0']++;
        }
        string nsa;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) continue;
            nsa += sa[i];
        }
        if (nsa.empty()) nsa = "0";
        ull na = stoull(nsa);
        ull nb = (__int128) b * na / a;
        if ((__int128) a * nb != (__int128) b * na) continue;

        string nsb = to_string(nb);
        int flag = 0, j = 0;
        for (char ch : sb) {
            if (j < nsb.size() && ch == nsb[j]) j++;
        }
        if (j != nsb.size()) flag = 1;

        int cb[10] = {0};
        for (char ch : sb) cb[ch - '0']++;
        for (char ch : nsb) cb[ch - '0']--;

        if (cb[0] < ca[0]) flag = 1;
        for (int i = 1; i <= 9; i++) {
            if (cb[i] != ca[i]) flag = 1;
        }
        int cnt = cb[0] - ca[0];
        if (cnt > 0 && !check(nsb, cnt, cb)) flag = 1;

        if (flag) continue;
        if (na < up && nb != 0) up = na, down = nb;
    }

    cout << up << " " << down << "\n";
}

void prework() {
    ull na = stoull("000");
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
        cin >> sa >> sb;
        solve();
    }

    return 0;
}