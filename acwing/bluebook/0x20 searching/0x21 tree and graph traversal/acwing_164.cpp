#include <bits/stdc++.h>

using namespace std;

const int N = 3e4 + 10;

int n, m;
int ver[N], head[N], ne[N], tot;
int du[N];
vector<int> seq;
bitset<N> f[N];

void addEdge(int a, int b) {
    ver[tot] = b, ne[tot] = head[a], head[a] = tot++;
    du[b]++;
}

void topsort() {
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (du[i] == 0) que.push(i);
    }

    while (!que.empty()) {
        int u = que.front(); que.pop();

        seq.push_back(u);

        for (int i = head[u]; ~i; i = ne[i]) {
            int v = ver[i];
            if (--du[v] == 0) que.push(v);
        }
    }
}

void solve() {
    topsort();

    for (int i = n - 1; i >= 0; i--) {
        int u = seq[i];
        f[u][u] = 1;

        for (int k = head[u]; ~k; k = ne[k]) {
            int v = ver[k];
            f[u] |= f[v];
        }
    }

    for (int i = 1; i <= n; i++) cout << f[i].count() << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    memset(head, -1, sizeof head);
    cin >> n >> m;
    for (int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        addEdge(a, b);
    }
    solve();

    return 0;
}