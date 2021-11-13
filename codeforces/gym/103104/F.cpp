#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;

const int N = 3e5 + 10;

int n, m;
int va[N], vb[N];
int cnt[31];
unordered_map<int, int> mp;

void calc(int x) {
    for (int i = 30; i >= 0; i--) {
        cnt[i] += x >> i & 1;
    }
}

void solve() {
    for (int i = 30; i >= 0; i--) mp[1 << i] = i;
    for (int i = 0; i < n; i++) calc(va[i]);

    int ans = 0;
    sort(vb, vb + m);
    for (int i = 0; i < m; i++) {
        int bi = mp[vb[i]];
        if (cnt[bi] > 0) {
            cnt[bi]--;
            ans++;
        } else {
            int up = bi + 1;
            while (up <= 30) {
                if (cnt[up] > 0) break;
                up++;
            }
            if (up > 30) break;

            cnt[up]--;
            for (int i = up - 1; i >= bi; i--) cnt[i]++;
            ans++;
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> va[i];
    for (int i = 0; i < m; i++) cin >> vb[i];
    solve();

    return 0;
}