#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ull unsigned long long

const int N = 1000010;
const ull BASE = 131;

int n, m;
string s;
ull h[N], p[N];

ull get(int L, int R) {
    return h[R] - h[L - 1] * p[R - L + 1];
}

void solve() {
    n = s.size();
    h[0] = 0, p[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * BASE + s[i - 1] - 'a';
        p[i] = p[i - 1] * BASE;
    }

    cin >> m;
    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        ull hash1 = get(a, b), hash2 = get(c, d);
        cout << (hash1 == hash2 ? "Yes" : "No") << endl;
    }
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