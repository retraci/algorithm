#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ull unsigned long long

const int N = 300000 + 10;
const ull BASE = 131;

int n;
string s;
int sa[N];
ull h[N], p[N];

ull get(int L, int R) {
    return h[R] - h[L - 1] * p[R - L + 1];
}

int get_prefix_len(int a, int b) {
    int left = 0, right = min(n - a + 1, n - b + 1);
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (get(a, a + mid - 1) == get(b, b + mid - 1)) left = mid;
        else right = mid - 1;
    }

    return left;
}

void solve() {
    n = s.size();
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * BASE + s[i - 1];
        p[i] = p[i - 1] * BASE;
        sa[i] = i;
    }

    sort(sa + 1, sa + 1 + n, [&](int &a, int &b) {
        int len = get_prefix_len(a, b);
        int av = a + len - 1 < n ? s[a + len - 1] : -1;
        int bv = b + len - 1 < n ? s[b + len - 1] : -1;
        return av < bv;
    });

    for (int i = 1; i <= n; i++) {
        cout << sa[i] - 1 << " ";
    }
    cout << endl;

    cout << 0 << " ";
    for (int i = 2; i <= n; i++) {
        cout << get_prefix_len(sa[i], sa[i - 1]) << " ";
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> s;
    solve();

    return 0;
}