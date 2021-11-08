#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const int N = 30;

int n, m;
vector<int> g[N];
int du[N];
bitset<N> f[N];
int fail, succ, ti, T;
vector<int> ans;

void add(int u, int v) {
    g[u].push_back(v);
    du[v]++;
}

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i][k]) f[i] = f[i] | f[k];
        }
    }
}

void print() {
    for (int i = 0; i < n; i++) {
        cout << f[i] << endl;
    }
    cout << endl;
}

void check() {
//    print();

    // 有冲突
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (f[u][v] && f[v][u]) {
                fail = 1;
                ti = T;
                return;
            }
        }
    }

    // 有 未确定关系 的
    int flag = 0;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u != v && !f[u][v] && !f[v][u]) {
                flag = 1;
            }
        }
    }

    if (!flag) {
        succ = 1;
        ti = T;
    }
}

void topo() {
    ans.clear();
    queue<int> que;
    for (int i = 0; i < n; i++) {
        if (du[i] == 0) que.push(i);
    }

    while (!que.empty()) {
        int u = que.front(); que.pop();
        ans.push_back(u);

        for (int v: g[u]) {
            if (--du[v] == 0) que.push(v);
        }
    }
}

void solve() {
    for (int i = 0; i < n; i++) g[i].clear(), f[i].reset();
    memset(du, 0, sizeof du);
    fail = succ = ti = T = 0;
    while (m--) {
        T++;
        string str;
        cin >> str;
        if (fail || succ) continue;

        int u = str[0] - 'A', v = str[2] - 'A';
        add(u, v);
        f[u][v] = 1;

        floyd();
        check();
    }

    if (fail) {
        cout << "Inconsistency found after " + to_string(ti) + " relations." << endl;
    } else if (succ) {
        cout << "Sorted sequence determined after " + to_string(ti) + " relations: ";
        topo();
        for (int u: ans) cout << (char) (u + 'A');
        cout << "." << endl;
    } else {
        cout << "Sorted sequence cannot be determined." << endl;
    }

}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n >> m, n || m) {
        solve();
    }

    return 0;
}
