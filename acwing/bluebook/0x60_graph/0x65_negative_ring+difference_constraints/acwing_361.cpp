#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

const int N = 1010;
const double eps = 1e-4;

typedef pair<int, int> pii;

int n, m;
int vw[N];
vector<pii> g[N];
double dist[N];
int st[N];
int cnt[N];

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

bool check(double mid) {
    for (int i = 1; i <= n; i++) dist[i] = 0, cnt[i] = 0;
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        que.push(i);
        st[i] = 1;
    }

    while (!que.empty()) {
        int u = que.front(); que.pop();
        st[u] = 0;

        for (auto &[v, w]: g[u]) {
            if (dist[v] < dist[u] + vw[u] - mid * w) {
                dist[v] = dist[u] + vw[u] - mid * w;

                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return true;

                if (!st[v]) {
                    que.push(v);
                    st[v] = 1;
                }
            }
        }
    }

    return false;
}

void solve() {
    double left = 0, right = 1001;
    while (left + eps < right) {
        double mid = (left + right) / 2;
        if (check(mid)) left = mid;
        else right = mid;
    }

    cout << fixed << setprecision(2);
    cout << left << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> vw[i];
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    solve();

    return 0;
}