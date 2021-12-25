#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1e5 + 10;

int n;
string s1, s2;

void solve() {
    int c1 = 0, c2 = 0, f1 = 0, f2 = 0;
    for (int i = 0; i < n; i++) {
        if (s1[i] == s2[i]) c2++;
        else c1++;
        f1 += s1[i] == '1';
        f2 += s2[i] == '1';
    }

    if (f1 == 0) {
        if (f2 == 0) cout << 0 << "\n";
        else cout << -1 << "\n";
        return;
    }

    int ans = 1e9;
    if (f1 == f2 && c1 % 2 == 0) ans = min(ans, c1);
    if (n - f1 + 1 == f2 && c2 % 2 == 1) ans = min(ans, c2);

    cout << (ans == 1e9 ? -1 : ans) << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        cin >> s1 >> s2;
        solve();
    }

    return 0;
}