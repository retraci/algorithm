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
const int N = 510;

int n;
int a[N];

void solve() {
    unordered_map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        cnt[a[i]]++;
    }
    for (auto [x, c] : cnt) {
        if (c & 1) {
            cout << -1 << "\n";
            return;
        }
    }

    deque<int> que;
    for (int i = 1; i <= n; i++) que.push_back(a[i]);
    vector<pii> ans;
    vector<int> ans2;
    int pos = 1;
    while (!que.empty()) {
        int tar = que.front(); que.pop_front();
        vector<int> tmp;
        while (que.front() != tar) {
            tmp.push_back(que.front()); que.pop_front();
        }
        que.pop_front();
        ans2.push_back(2 * (tmp.size() + 1));
        pos += tmp.size();

        for (int i = 0; i < tmp.size(); i++) ans.push_back({++pos, tmp[i]});
        for (int x : tmp) que.push_front(x);
        pos += 2;
    }

    cout << ans.size() << "\n";
    for (auto [p, x] : ans) cout << p << " " << x << "\n";
    cout << ans2.size() << "\n";
    for (auto x : ans2) cout << x << " ";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}