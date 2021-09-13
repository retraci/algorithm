#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
string sa, sb;

void solve() {
    int ans = 0;
    int vis[2] = {0}, cnt = 0;
    for (int i = 0; i < n; i++) {
        vis[0] = vis[1] = cnt = 0;
        int j = i;
        while (j < n) {
            if (!vis[sa[j] - '0']) {
                vis[sa[j] - '0'] = 1;
                cnt++;
            }
            if (!vis[sb[j] - '0']) {
                vis[sb[j] - '0'] = 1;
                cnt++;
            }

            // 凑齐 0, 1
            if (cnt == 2) { j++; break; }
            // 只有 1
            if (cnt == 1 && vis[1]) { j++; continue; }
            // 只有 0
            if (cnt == 1 && vis[0]) {
                if (j + 1 < n && (sa[j + 1] == '1' && sb[j + 1] == '1')) { j++; continue; }
                else { j++; break; }
            }
        }

//        cout << i << " " << j << " " << cnt << endl;

        if (!(cnt == 1 && vis[1])) ans += cnt;
        i = j - 1;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        cin >> sa >> sb;
        solve();
    }

    return 0;
}