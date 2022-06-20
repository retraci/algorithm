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

int n;
string s;

void solve() {
    int cnt = 0;
    vector<int> vis(n + 1);
    vector<int> a[n + 1];
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') {
            vis[i] = 1, cnt++;
        }
    }

    if (cnt == 0 || cnt & 1) {
        cout << "No" << "\n";
        return;
    }

    vector<int> lst;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) continue;

        a[i].push_back(i);
        int j = (i - 1 + 1) % n + 1;
        while (!vis[j]) {
            a[i].push_back(j);
            j = (j - 1 + 1) % n + 1;
        }
        lst.push_back((j - 1 - 1 + n) % n + 1);
    }

    vector<pii> ans;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) continue;

        for (int j = 1; j < a[i].size(); j++) {
            ans.push_back({a[i][j - 1], a[i][j]});
        }
    }
    for (int i = 1; i < lst.size(); i++) {
        ans.push_back({lst[0], lst[i]});
    }

    cout << "Yes" << "\n";
    for (auto [u, v] : ans) {
        cout << u << " " << v << "\n";
    }
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