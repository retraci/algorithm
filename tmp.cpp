#include<bits/stdc++.h>

using namespace std;
#define int long long
int n, m, step, a[300000];

bool check(int k) {
    if (k == 1) return m != 0;
    int x = k / 2, y = (k + 1) / 2, s1 = 0, s2 = 0;
    for (int i = 1; i <= x; ++i) s1 += a[i];
    for (int i = x + 1; i <= k; ++i) s2 += a[i];
    for (int i = x + 1; i + y - 1 <= m; ++i) {
        int now = x * (2 * a[i] - x - 1) / 2 - s1 + s2 - y * (2 * a[i] + y - 1) / 2;
        if (now <= step) return 1;
        s1 = s1 + a[i] - a[i - x];
        s2 = s2 - a[i] + a[i + y];
    }
    return 0;
}

string s;

signed main() {
    cin >> s;
    n = s.size();
    s = ' ' + s;
    cin >> step;
    for (int i = 1; i <= n; ++i)
        if (s[i] == 'Y') a[++m] = i;
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }
    cout << l - 1;
}