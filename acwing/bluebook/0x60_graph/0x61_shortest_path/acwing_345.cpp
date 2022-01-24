#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct Edge {
    int u, v, w;
};

const int N = 210;
const int M = 1e6 + 10;

int K, m, s, t;
int n;
vector<int> lsh;
vector<Edge> es;
int f[N][N];
int ans[N][N];

// 强制走 n 条边的最短路
//void bellman_ford(int s) {
//    memset(dist, 0x3f, sizeof dist);
//    dist[s] = 0;
//    for (int i = 1; i <= n; i++) {
//        memcpy(dist2, dist, sizeof dist2);
//        memset(dist, 0x3f, sizeof dist);
//        for (auto &[u, v, w]: es) {
//            dist[v] = min(dist[v], dist2[u] + w);
//            dist[u] = min(dist[u], dist2[v] + w);
//        }
//    }
//}

// 强制走 K 个边
void floyd(int a[][N], int b[][N]) {
    // temp数组作为相乘的结果
    static int temp[N][N];
    memset(temp, 0x3f, sizeof temp);

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[i][j] = min(temp[i][j], a[i][k] + b[k][j]);
            }
        }
    }

    memcpy(a, temp, sizeof temp);
}

void ksm() {
    memset(ans, 0x3f, sizeof ans);
    for (int i = 0; i < n; i++) ans[i][i] = 0;

    while (K) {
        if (K & 1) floyd(ans, f);
        floyd(f, f);
        K >>= 1;
    }
}

void add(int u, int v, int w) {
    es.push_back({u, v, w});
    lsh.push_back(u), lsh.push_back(v);
}

int get_idx(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    sort(lsh.begin(), lsh.end());
    lsh.erase(unique(lsh.begin(), lsh.end()));
    n = lsh.size();
    for (auto &[u, v, w]: es) {
        u = get_idx(u);
        v = get_idx(v);
    }
    s = get_idx(s), t = get_idx(t);
}

void solve() {
    init();

    // 走了一条边的, 所以f[i][i]不为0
    memset(f, 0x3f, sizeof f);
    for (auto &[u, v, w]: es) {
        f[u][v] = f[v][u] = min(f[u][v], w);
    }

    ksm();
    printf("%d\n", ans[s][t]);

    // T 了
//    bellman_ford(s);
//    printf("%d\n", dist[t]);
}

template<typename T>
inline void rd(T &x) {
    T ret = 0, sgn = 1;
    char c = getchar();
    while (!isdigit(c)) sgn = (c == '-' ? -1 : 1), c = getchar();
    while (isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
    x = (sgn == -1 ? -ret : ret);
}


int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

//    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    rd(K), rd(m), rd(s), rd(t);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        rd(w), rd(u), rd(v);
        add(u, v, w);
    }
    solve();

    return 0;
}