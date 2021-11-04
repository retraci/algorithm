#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "err_ovl_ambiguous_call"
using namespace std;

typedef pair<int, int> pii;

const int N = 1e5 + 10;

int Q;
pii vo[N];
int n;
vector<int> g[N];
int vw[N], tw;
unordered_map<int, int> mp;

void add(int u, int v) {
    g[u].push_back(v);
}

void dfs(int u) {
//    cout << u << endl;
    vw[u] = ++tw;
    for (int v: g[u]) dfs(v);
}

void solve() {
    n = 1;
    for (int i = 1; i <= Q; i++) {
        auto &[op, a] = vo[i];
        if (op == 1) add(a, ++n);
    }

    dfs(1);
    for (int i = 1; i <= n; i++) mp[vw[i]] = i;

    set<int> st;
    int m = 1;
    st.insert(vw[1]);
    for (int i = 1; i <= Q; i++) {
        auto &[op, a] = vo[i];
        if (op == 1) {
            st.insert(vw[++m]);
//            cout << "add: " << m << endl;
        } else {
            int w = vw[a];
            st.erase(w);
            cout << mp[*st.begin()] << endl;
        }
    }

}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> Q;
    for (int i = 1; i <= Q; i++) {
        int op, a;
        cin >> op >> a;
        vo[i] = {op, a};
    }
    solve();

    return 0;
}
#pragma clang diagnostic pop