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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

int n, m;
string str;

void solve() {
    vector<int> s(n * m + 1);
    for (int i = 1; i <= n * m; i++) s[i] = s[i - 1] + str[i] - '0';

    vector<int> ans(n * m + 1);
    vector<int> f(n * m + 1);
    for (int i = 1 ; i <= n * m; i++) {
        int p = max(0, i - m);
        int cur = s[i] - s[p];
        f[i] = f[p] + (cur > 0);
        ans[i] += f[i];
    }

    int cur = 0;
    vector<int> g(m);
    for (int i = 1; i <= n * m; i++) {
        int x = (i - 1) % m;
        if (!g[x] && str[i] == '1') g[x] = 1, cur++;
        ans[i] += cur;
    }

    for (int i = 1; i <= n * m; i++) cout << ans[i] << " ";
    cout << "\n";
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
        cin >> n >> m;
        cin >> str;
        str = ' ' + str;
        solve();
    }

    return 0;
}