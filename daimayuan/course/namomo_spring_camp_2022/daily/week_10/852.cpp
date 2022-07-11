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

const int N = 1010;

int n;
int a[N];
int f[20010];

int calc(int x) {
    int res = 0, pos = n;
    while (x) {
        while (a[pos] > x) pos--;
        res += x / a[pos];
        x %= a[pos];
    }
    return res;
}

void solve() {
    int mx = *max_element(a + 1, a + n + 1);
    fill(f + 1, f + 2 * mx + 1, 1e9);
    for (int i = 1; i <= n; i++) {
        for (int j = a[i]; j <= 2 * mx; j++) {
            f[j] = min(f[j], f[j - a[i]] + 1);
        }
    }

    vector<int> b(2 * mx + 1, 1e9);
    for (int i = 1; i <= 2 * mx; i++) b[i] = calc(i);

    int flag = 0;
    for (int i = 1; i <= 2 * mx; i++) {
        if (b[i] > f[i]) flag = 1;
    }

    cout << (flag ? "No" : "Yes") << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}