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

// region SAM
template<int N, int M>
struct SAM {
    struct Node {
        int len, link;
        int nxt[M];
    };

    int n, mem, lst;
    int cnt[N * 2 + 10];
    Node st[N * 2 + 10];
    int h[N * 2 + 10], ne[N * 2 + 10], e[N * 2 + 10], edm;

    SAM() {}

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    int new_node() {
        int id = ++mem;
        st[id].len = st[id].link = 0;
        for (int i = 0; i < M; i++) st[id].nxt[i] = 0;
        cnt[id] = 0;
        return id;
    }

    void init(int _n) {
        n = _n, mem = 0;
        lst = new_node();
    }

    // c: [0, m - 1]
    void extend(int c) {
        int cur = new_node();
        st[cur].len = st[lst].len + 1, cnt[cur] = 1;

        int p = lst;
        while (p && !st[p].nxt[c]) {
            st[p].nxt[c] = cur;
            p = st[p].link;
        }

        if (!p) {
            st[cur].link = 1;
        } else {
            int q = st[p].nxt[c];
            if (st[q].len == st[p].len + 1) {
                st[cur].link = q;
            } else {
                int cl = new_node();
                st[cl] = st[q];
                st[cl].len = st[p].len + 1;
                while (p && st[p].nxt[c] == q) {
                    st[p].nxt[c] = cl;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = cl;
            }
        }

        lst = cur;
    }

    void dfs(int u) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];

            dfs(v);
            cnt[u] += cnt[v];
        }
    }

    void build() {
        fill(h, h + 2 * n + 1, -1), edm = 0;
        for (int i = 2; i <= mem; i++) add(st[i].link, i);
    }

    void get_cnt() {
        dfs(1);
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 10010;

int n;
string s[12];
SAM<N, 26> sam;

void dfs(int u, vector<int> &cur) {
    for (int i = sam.h[u]; ~i; i = sam.ne[i]) {
        int v = sam.e[i];

        dfs(v, cur);

        int t = min(sam.st[u].len, cur[v]);
        cur[u] = max(cur[u], t);
    }
}

void solve() {
    sam.init(s[1].size());
    for (char ch : s[1]) sam.extend(ch - 'a');
    sam.build();

    vector<int> ans(sam.mem + 1, 1e9), cur(sam.mem + 1, 0);
    for (int i = 2; i <= n; i++) {
        fill(cur.begin(), cur.end(), 0);
        int u = 1, len = 0;
        for (char ch : s[i]) {
            int c = ch - 'a';
            while (u > 1 && !sam.st[u].nxt[c]) u = sam.st[u].link, len = sam.st[u].len;
            if (sam.st[u].nxt[c]) u = sam.st[u].nxt[c], len++;
            cur[u] = max(cur[u], len);
        }

        dfs(1, cur);
        for (int j = 1; j <= sam.mem; j++) ans[j] = min(ans[j], cur[j]);
    }

    int mx = *max_element(ans.begin() + 1, ans.end());
    cout << mx << "\n";
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
        for (int i = 1; i <= n; i++) cin >> s[i];
        solve();
    }

    return 0;
}