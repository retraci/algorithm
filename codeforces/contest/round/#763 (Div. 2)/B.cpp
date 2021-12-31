#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1010;

int n;
int ls[N], rs[N];
int idx[N];
int vis[N];
int ans[N];

void solve() {
    iota(idx, idx + n + 1, 0);
    sort(idx + 1, idx + n + 1, [&](auto &a, auto &b) {
        return rs[a] - ls[a] > rs[b] - ls[b];
    });

    memset(vis, 0, sizeof vis);
    for (int i = n; i >= 1; i--) {
        int id = idx[i];
        int L = ls[id], R = rs[id];

//        cout << L << " " << R << "\n";

        for (int k = L; k <= R; k++) {
            if (vis[k]) continue;
            vis[k] = 1;
            ans[id] = k;
        }
    }

    for (int i = 1; i <= n; i++) cout << ls[i] << " " << rs[i] << " " << ans[i] << "\n";
    cout << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> ls[i] >> rs[i];
        solve();
    }

    return 0;
}