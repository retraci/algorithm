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
#include <cassert>
#include <random>
#include <cmath>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region kmp
// s 下标从 1 开始
vector<int> get_ne(const string &s) {
    int n = s.size() - 1;
    vector<int> ne(n, 0);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[i] != s[j + 1]) j = ne[j];
        if (s[i] == s[j + 1]) j++;
        ne[i] = j;
    }

    return ne;
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;
const int MOD = 1e9 + 7;

int n;
string s;
int fa[23][N];

void solve() {
    n = s.size() - 1;
    auto ne = get_ne(s);

    for (int i = 1; i <= n; i++) fa[0][i] = ne[i];
    int mxb = __lg(n);
    for (int k = 1; k <= mxb; k++) {
        for (int i = 1; i <= n; i++) {
            fa[k][i] = fa[k - 1][fa[k - 1][i]];
        }
    }

    int ans = 1;
    for (int i = 1; i <= n; i++) {
        int j = i;
        for (int k = mxb; k >= 0; k--) {
            if (fa[k][j] > i / 2) j = fa[k][j];
        }

        int cnt = 0;
        for (int k = mxb; k >= 0; k--) {
            if (fa[k][j]) cnt += 1 << k, j = fa[k][j];
        }
        ans = 1LL * ans * (cnt + 1) % MOD;
    }
    cout << ans << "\n";
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
    cin >> _;
    while (_--) {
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}