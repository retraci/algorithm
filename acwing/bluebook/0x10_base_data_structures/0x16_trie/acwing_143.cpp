#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10, M = 3e6 + 10;

int n;
int va[N];
int son[M][2], cnt[M], tt;

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int bi = x >> i & 1;
        int &s = son[p][bi];
        if (!s) s = ++tt;
        p = s;
    }

    cnt[p]++;
}

int query(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        int bi = x >> i & 1;
        if (son[p][!bi]) {
            res += 1 << i;
            p = son[p][!bi];
        } else {
            p = son[p][bi];
        }
    }

    return res;
}

void solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) insert(va[i]);
    for (int i = 1; i <= n; i++) ans = max(ans, query(va[i]));

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> va[i];
    }
    solve();

    return 0;
}