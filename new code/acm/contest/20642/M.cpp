#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>

using namespace std;

struct Node {
    string cur;
    unordered_map<string, int> son;
};

const int N = 110;

int n, m;
string va[N], vb[N];
vector<string> pa[N], pb[N];
Node trie[N * 1010];
int tag[N * 1010], tt;
int dp[N * 1010];

void insert(vector<string> &vp, int t) {
    int root = 0;
    for (string &s: vp) {
        if (!trie[root].son.count(s)) trie[root].son[s] = ++tt;
        root = trie[root].son[s];
        trie[root].cur = s;
    }
    tag[root] = t;
}

int dfs2(int root) {
    int flag = 0;
    if (tag[root] == 2) return 0;

    for (auto &[k, v] : trie[root].son) {
        if (dfs2(v) == 0) flag = 1;
        dp[root] += dp[v];
    }

    if (flag) {
        return 0;
    } else {
        if (root != 0) dp[root] = 1;
        return 1;
    }
}

void solve() {
    for (int k = 0; k < n; k++) {
        pa[k].clear();
        string &s = va[k];
        int len = s.size();
        for (int i = 0; i < len; i++) {
            int j = i;
            while (j < len && s[j] != '/') j++;
            pa[k].push_back(s.substr(i, j - i));
            i = j;
        }
    }

    for (int k = 0; k < m; k++) {
        pb[k].clear();
        string &s = vb[k];
        int len = s.size();
        for (int i = 0; i < len; i++) {
            int j = i;
            while (j < len && s[j] != '/') j++;
            pb[k].push_back(s.substr(i, j - i));
            i = j;
        }
    }

    tt = 0;
    for (int i = 0; i < N * 1010; i++) trie[i].son.clear();
    memset(tag, 0, sizeof tag);
    for (int i = 0; i < n; i++) insert(pa[i], 1);
    for (int i = 0; i < m; i++) insert(pb[i], 2);

    memset(dp, 0, sizeof dp);
    dfs2(0);
    cout << dp[0] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> va[i];
        for (int i = 0; i < m; i++) cin >> vb[i];
        solve();
    }

    return 0;
}
