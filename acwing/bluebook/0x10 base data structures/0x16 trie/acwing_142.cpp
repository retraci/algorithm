#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

int n, m;
int trie[N][26], cnt[N], tt;

void insert(string &str) {
    int p = 0;
    for (char ch : str) {
        int &s = trie[p][ch - 'a'];
        if (!s) s = ++tt;
        p = s;
    }
    cnt[p]++;
}

int query(string &str) {
    int p = 0, res = 0;
    for (char ch : str) {
        int &s = trie[p][ch - 'a'];
        if (!s) break;
        p = s;
        res += cnt[p];
    }

    return res;
}

void solve() {
    while (m--) {
        string str;
        cin >> str;
        cout << query(str) << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        insert(str);
    }
    solve();

    return 0;
}