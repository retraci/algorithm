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
using ai3 = array<int, 3>;

// region trie
template<int SZ>
struct Trie {
    int ne[SZ + 10][26], cnt[SZ + 10], mem;

    Trie() {}

    void init(int _n) {
        fill(&ne[0][0], &ne[_n][25] + 1, 0);
        fill(cnt, cnt + _n + 1, 0);
        mem = 0;
    }

    void ins(string &s) {
        int u = 0;
        for (char ch : s) {
            int &v = ne[u][ch - 'a'];
            if (!v) v = ++mem;
            u = v;
        }

        cnt[u]++;
    }

    int qr(string &s) {
        int u = 0, res = 0;
        for (char ch : s) {
            int &v = ne[u][ch - 'a'];
            if (!v) break;
            u = v;
            res += cnt[u];
        }

        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 110;
const int M = 3e5 + 10;

int n, m;
string a[N];
int ans;
Trie<M> tr;

int dfs(int u) {
    int res = tr.cnt[u];

    vector<int> tmp;
    for (char i = 'a'; i <= 'z'; i++) {
        int v = tr.ne[u][i - 'a'];
        if (!v) continue;

        tmp.push_back(dfs(v));
    }

    sort(tmp.begin(), tmp.end());
    for (int x : tmp) {
        if (x + res <= m) res += x;
        else ans++;
    }
    return res;
}

void solve() {
    tr.init(M);
    for (int i = 1; i <= n; i++) tr.ins(a[i]);

    int r = dfs(0);

    cout << ans + (r > 0) << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}