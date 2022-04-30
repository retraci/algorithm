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

const int N = 4e4 + 10;
const int MOD = 1e9 + 7;

int n;
int f[N];

void solve() {
    cout << f[n] << "\n";
}

bool check(int x) {
    string s1 = to_string(x);
    string s2 = string(s1.rbegin(), s1.rend());

    return s1 == s2;
}

void prework() {
    vector<int> a;
    for (int i = 1; i <= 4e4; i++) {
        if (check(i)) a.push_back(i);
    }

    f[0] = 1;
    for (int x : a) {
        for (int j = x; j <= 4e4; j++) {
            f[j] += f[j - x];
            f[j] %= MOD;
        }
    }
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
        solve();
    }

    return 0;
}