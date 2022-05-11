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
using ai6 = array<int, 6>;

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int M = 5;
const int B = 3000;

int n, m;
ai6 a[N];
int nl;
vector<int> lsh;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) lsh.push_back(a[i][j]);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) a[i][j] = get(a[i][j]) + 1;
    }
}

void solve() {
    init();

    sort(a + 1, a + n + 1, [&](auto &a, auto &b) {
        return a[0] < b[0];
    });

    vector<int> v[nl + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x = a[i][j];
            v[x].push_back(i);
        }
    }

    vector<int> id(nl + 1);
    vector<bitset<N>> bs;
    for (int i = 1; i <= nl; i++) {
        if (v[i].size() >= B) {
            bitset<N> bit;
            for (int t : v[i]) bit.set(t);
            bs.push_back(bit);
            id[i] = bs.size() - 1;
        }
    }

    int ans = 2e9 + 1;
    for (int i = 1; i <= n; i++) {
        bitset<N> f;
        for (int j = 1; j <= m; j++) {
            int x = a[i][j];
            if (v[x].size() >= B) {
                f |= bs[id[x]];
            } else {
                for (int t : v[x]) f.set(t);
            }
        }

        f.flip();
        f.reset(0);
        int j = f._Find_first();
        if (j <= n) ans = min(ans, a[i][0] + a[j][0]);
    }

    cout << (ans == 2e9 + 1 ? -1 : ans) << "\n";
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
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) cin >> a[i][j];
            cin >> a[i][0];
        }
        solve();
    }

    return 0;
}