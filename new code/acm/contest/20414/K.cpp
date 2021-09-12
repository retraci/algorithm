#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

const int N = 1e5 + 10;

typedef pair<int, int> PII;

vector<PII> ans[N];
int n;
bool vis[N];
int a[N];

void solve() {
    memset(vis, 0, sizeof vis);

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        int tmpp = i;
        vector<int> tmp;
        while (!vis[tmpp]) {
            vis[tmpp] = 1;
            tmp.push_back(tmpp);
            tmpp = a[tmpp];
        }

        if (tmp.size() == 1) continue;

        if (tmp.size() == 2) {
            ans[1].push_back({tmp[0], tmp[1]});
        } else {
            for (int l = 1, r = tmp.size() - 1; l < r; l++, r--) {
                if (l >= r) break;
                ans[1].push_back({tmp[l], tmp[r]});
                int tmppp = tmp[l];
                tmp[l] = tmp[r];
                tmp[r] = tmppp;
            }

            for (int l = 0, r = tmp.size() - 1;; l++, r--) {
                if (l >= r) break;
                ans[2].push_back({tmp[l], tmp[r]});
            }
        }
    }

    int sn = 0;
    for (int i = 1; i <= 2; i++) {
        if (ans[i].size()) {
            sn++;
        }
    }

    cout << sn << endl;
    for (int i = 1; i <= sn; i++) {
        cout << ans[i].size() << " ";
        for (auto k : ans[i]) {
            cout << k.first << ' ' << k.second << " ";
        }
        cout << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    solve();

    return 0;
}