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
const int N = 5010;

int n;
int a[N], b[N];
int c1[N], c2[N];

void solve() {
    for (int i = 1; i <= n; i++) c1[a[i]]++;
    for (int i = 1; i <= n; i++) c2[b[i]]++;
    for (int i = 1; i <= 5e3; i++) {
        if (c1[i] != c2[i]) {
            cout << "No" << "\n";
            return;
        }
    }
    for (int i = 1; i <= 5e3; i++) {
        if (c1[i] >= 2) {
            cout << "Yes" << "\n";
            return;
        }
    }

    int ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            ans1 += a[i] < a[j];
            ans2 += b[i] < b[j];
        }
    }
    if (ans1 % 2 == ans2 % 2) cout << "Yes" << "\n";
    else cout << "No" << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}