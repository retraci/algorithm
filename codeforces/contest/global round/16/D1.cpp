#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;

const int N = 310;

int n, m;
int va[N];
int idx[N];

void solve() {
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < m; i++) idx[i] = i;

    sort(idx, idx + m, [&](int a, int b) {
        return va[a] < va[b];
    });

//    for (int i = 0; i < m; i++) cout << va[idx[i]] << " ";
//    cout << endl;

    for (int i = 0; i < m; i++) {
        int idxx = idx[i], a = va[idxx];

//        cout << i << " " << idxx << " " << a << endl;

        mp[a].push_back(i);
    }
    for (auto &[k, v] : mp) {
        sort(v.begin(), v.end());
    }

    int ans = 0;
    int vis[m];
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < m; i++) {
        int idxx = mp[va[i]].back(); mp[va[i]].pop_back();
        int cnt = 0;
        for (int j = 0; j < idxx; j++) cnt += vis[j];
        vis[idxx] = 1;

//        cout << "# " << idxx << " " << cnt << endl;

        ans += cnt;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            cin >> va[i];
        }
        solve();
    }

    return 0;
}