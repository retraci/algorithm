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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

ll a[6], b[6];

void work(int i, int j) {
    ll mi = min(a[i], b[j]);
    a[i] -= mi, b[j] -= mi;
    b[j - i] += mi;
}

void solve() {
    int flag = 0;
    for (int i = 1; i <= 5; i++) work(i, i);
    flag |= a[5] > 0;

    work(4, 5);
    flag |= a[4] > 0;

    b[3] += b[5], b[2] += b[5];
    work(2, 2), work(3, 3);
    work(3, 4);
    flag |= a[3] > 0;

    b[2] += 2 * b[4];
    b[2] += b[3], b[1] += b[3];
    work(2, 2), work(1, 1);
    flag |= a[2] > 0;

    b[1] += 2 * b[2];
    work(1, 1);
    flag |= a[1] > 0;

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
        for (int i = 1; i <= 5; i++) cin >> a[i];
        for (int i = 1; i <= 5; i++) cin >> b[i];
        solve();
    }

    return 0;
}