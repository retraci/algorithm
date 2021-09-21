#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n, m;
int va[5], vb[5];
int sa[5], sb[5];
int ans;
vector<int> vn;

int get_r(int x) { return (x - 1) / 2; }
int get_c(int x) { return (x - 1) % 2; }

void dfs(int cur) {
    if (cur >= 5) {
        int pa[5] = {0}, pb[5] = {0};
        for (int x : vn) pa[get_r(x)] = 1, pb[get_c(x)] = 1;
        if (pa[0] == sa[0] && pa[1] == sa[1] && pb[0] == sb[0] && pb[1] == sb[1]) ans++;
        return;
    }

    dfs(cur + 1);
    vn.push_back(cur);
    dfs(cur + 1);
    vn.pop_back();
}

void solve() {
    sa[0] = sa[1] = sb[0] = sb[1] = 0;
    for (int i = 0; i < n; i++) sa[va[i]] = 1;
    for (int i = 0; i < m; i++) sb[vb[i]] = 1;
    ans = 0;
    dfs(1);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> va[i];
        for (int i = 0; i < m; i++) cin >> vb[i];
        solve();
    }

    return 0;
}