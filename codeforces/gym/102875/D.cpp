#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_set>

using namespace std;

const int N = 1e6 + 10, M = 110;

int t, n, K;
int vis[N];
unordered_set<int> st;
vector<int> f[M];
int g[N];
int ids[M];

void init() {
    st.insert(1);
    for (int i = 2; i <= 1e6; i++) {
        if (!vis[i]) {
            st.insert(i);
            for (int k = 2; k * i <= 1e6; k++) vis[k * i] = 1;
        }
    }

    for (int i = 1; i <= 1e6; i++) {
        for (int layer = 1; layer < M; layer++) {
            ids[layer]++;
            if (st.count(ids[layer])) {
                f[layer].push_back(i);
                g[i] = layer;
                break;
            }
        }
    }
}

void solve() {
    if (t == 1) {
        int mx = g[K], tt = 0;
        for (int i = 1; i <= mx - 1; i++) {
            int tmp = upper_bound(f[i].begin(), f[i].end(), n) - f[i].begin();
            tt += tmp;
        }
        tt += upper_bound(f[mx].begin(), f[mx].end(), K) - f[mx].begin();
        cout << tt << endl;
    } else {
        int tt = 0;
        int i = 1;
        for (; i < M; i++) {
            int tmp = upper_bound(f[i].begin(), f[i].end(), n) - f[i].begin();
            if (tt + tmp >= K) break;
            tt += tmp;
        }
        int rem = K - tt;
        cout << f[i][rem - 1] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    init();

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> t >> n >> K;
        solve();
    }

    return 0;
}