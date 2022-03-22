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

// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 1e4 + 10;

int n;
string a[N];
string str;

int tr[N * 50][26], cnt[N * 50], mem;
int ne[N * 50];

void insert(string &s) {
    int u = 0;
    for (char ch : s) {
        if (!tr[u][ch - 'a']) tr[u][ch - 'a'] = ++mem;
        u = tr[u][ch - 'a'];
    }
    cnt[u]++;
}

void build() {
    queue<int> que;
    for (int i = 0; i < 26; i++) {
        if (tr[0][i]) que.push(tr[0][i]);
    }

    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (int i = 0; i < 26; i++) {
            int &v = tr[u][i];

            if (!v) {
                v = tr[ne[u]][i];
            } else {
                ne[v] = tr[ne[u]][i];
                que.push(v);
            }
        }
    }
}

void solve() {
    fill(&tr[0][0], &tr[n * 50][25] + 1, 0);
    fill(&cnt[0], &cnt[n * 50] + 1, 0);
    fill(&ne[0], &ne[n * 50] + 1, 0);
    mem = 0;

    for (int i = 1; i <= n; i++) insert(a[i]);
    build();

    int ans = 0, j = 0;
    for (char ch : str) {
        j = tr[j][ch - 'a'];

        int p = j;
        while (p) {
            ans += cnt[p];
            cnt[p] = 0;
            p = ne[p];
        }
    }
    cout << ans << "\n";
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
    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        cin >> str;
        solve();
    }

    return 0;
}