#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1e5 + 10;

int n;
int va[N];
int vis[N];

void solve() {
    for (int i = 1; i <= n; i++) vis[i] = 0;
    sort(va + 1, va + n + 1);
    for (int i = 1; i <= n; i++) {
        if (va[i] <= n) vis[va[i]] = 1;
    }

    unordered_map<int, int> cnt;
    vector<int> vb;
    for (int i = 1; i <= n; i++) {
        if (++cnt[va[i]] > 1 || va[i] > n) vb.push_back(va[i]);
    }

    int ans = vb.size();
    int tar = 1;
    for (int x : vb) {
        while (tar <= n && vis[tar]) tar++;
        if (x <= 2 * tar) {
            cout << -1 << "\n";
            return;
        }
        vis[tar] = 1;
    }

    cout << ans << "\n";
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
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}