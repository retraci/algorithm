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
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2510;

int n, m, x;
int a[N];

void solve() {
    ll f[x + 1][n + 1];
    fill(&f[0][0], &f[x][n] + 1, -1e18);
    f[0][0] = 0;

    deque<int> que;
    for (int k = 1; k <= x; k++) {
        que = {};
        que.push_back(0);
        for (int i = 1; i <= n; i++) {
            while (!que.empty() && que.front() < i - m) que.pop_front();
            f[k][i] = f[k - 1][que.front()] + a[i];
            while (!que.empty() && f[k - 1][i] >= f[k - 1][que.back()]) que.pop_back();
            que.push_back(i);
        }
    }

    ll ans = *max_element(&f[x][n - m + 1], &f[x][n] + 1);
    cout << (ans < 0 ? -1 : ans) << "\n";
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
        cin >> n >> m >> x;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}