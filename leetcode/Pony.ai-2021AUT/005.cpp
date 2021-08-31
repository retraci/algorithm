#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1010;

int n, A, B, K;
ll g[N][N];
ll dist[N][N];

bool check(int mid) {
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = min({
                g[i][j],
                g[i][A] + mid + g[B][j],
                g[i][B] + mid + g[A][j]});
        }
    }

    ll mx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mx = max(mx, dist[i][j]);
        }
    }
    return mx + mid < K;
}

void solve() {
    int left = -1, right = 1e9;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lld", &g[i][j]);
        }
    }
    cin >> A >> B >> K;
    solve();

    return 0;
}