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
#include <random>

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

int n;
string s;

void solve() {
    vector<int> b;
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j <= n && s[j] == s[i]) j++;
        int sz = j - i;
        b.push_back(sz);
        i = j - 1;
    }

    int ans1 = 0, ans2 = 0;
    int c1 = 0;
    for (int i = 0; i < b.size(); i++) {
        if (b[i] != 1) continue;

        ans2++, c1++;
        if (i - 1 >= 0 && b[i - 1] & 1) b[i]++;
        else if (i + 1 < b.size() && b[i + 1] & 1) b[i + 1]++;
        else if (i - 1 >= 0) b[i - 1]++;
        else b[i + 1]++;
    }

    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j <= n && s[j] == s[i]) j++;
        int sz = j - i;

        if (sz & 1) i = j, ans1++;
        else i = j - 1;
    }

    for (int i = 0; i < b.size(); i++) {
        if (~b[i] & 1 || b[i] == 1) continue;

        int j = i + 1, flag = 0;
        while (~b[j] & 1) j++, flag |= b[j] == 2;
        if (flag) ans2 += 2;
        int gap = j - i;

        i = j;
    }

    cout << ans1 << " " << b.size() - ans2 - c1 << "\n";
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}