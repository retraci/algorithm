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

string s;

void solve() {
    int n = s.size() - 1;

    vector<int> vis(26, 0);
    for (int i = 1; i <= n; i++) vis[s[i] - 'a'] = 1;
    int cnt = accumulate(vis.begin(), vis.end(), 0);

    int flag = 0;
    for (char u = 'a'; u <= 'z'; u++) {
        vector<int> a;
        for (int i = 1; i <= n; i++) {
            if (s[i] == u) a.push_back(i);
        }

        for (int i = 1; i < a.size(); i++) {
            int L = a[i - 1], R = a[i];
            vector<int> c(26, 0);
            for (int j = L; j <= R; j++) c[s[j] - 'a'] = 1;
            int sum = accumulate(c.begin(), c.end(), 0);
            if (sum != cnt) flag = 1;
        }
    }

    cout << (flag ? "NO" : "YES") << "\n";
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