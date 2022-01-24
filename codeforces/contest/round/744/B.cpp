#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 55;

int n;
int va[N];
int vb[N], tmp[N];
int ans[N];

void solve() {
    for (int i = 0; i < n; i++) vb[i] = va[i];
    sort(vb, vb + n);

    for (int i = 0; i < n; i++) {
        int tar = vb[i];
        int j = i;
        while (j < n && tar != va[j]) j++;

        int len = n - i;
        ans[i] = j - i;
        memcpy(tmp, va, sizeof va);
        for (int k = i; k < n; k++) {
            int id = (k - i - ans[i] + len) % len + i;
//            cout << tmp[id] << " " << va[k] << " " << id << " " << k << endl;
            tmp[id] = va[k];
        }

        memcpy(va, tmp, sizeof va);
//
//        for (int k = 0; k < n; k++) {
//            cout << va[k] << " ";
//        }
//        cout << endl;
    }
//    cout << endl;

    int cnt = n - 1;
    for (int i = 0; i < n - 1; i++) if (ans[i] == 0 || ans[i] == n - i) cnt--;
    cout << cnt << endl;
    for (int i = 0; i < n - 1; i++) {
        if (ans[i] == 0 || ans[i] == n - i) continue;
        cout << i + 1 << " " << n << " " << ans[i] << endl;
    }
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
        for (int i = 0; i < n; i++) {
            cin >> va[i];
        }
        solve();
    }

    return 0;
}