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
using pll = pair<ll, ll>;

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 66;

int n, m;
int a[N];
map<pll, ll> memo;

int dfs(ll x, ll r) {
    if (memo.count({x, r})) return memo[{x, r}];
    if (x == n) return r / a[x];

    ll down = r / a[x + 1] * a[x + 1];
    ll up = (r + a[x + 1] - 1) / a[x + 1] * a[x + 1];

    ll res1 = (r - down) / a[x] + dfs(x + 1, down);
    ll res2 = (up - r) / a[x] + dfs(x + 1, up);

    return memo[{x, r}] = min(res1, res2);
}

void solve() {
    cout << dfs(1, m) << "\n";
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
//    cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}