#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 300010;

int n;
string str;
int s[N];

void solve() {
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + (str[i - 1] == 'E' ? 1 : -1);
    }

    int ans = 0;
    int mi = 0x3f3f3f3f;
    for (int i = 0; i <= n; i++) {
        mi = min(mi, s[i]);
        ans = max(ans, s[i] - mi);
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> str;
    solve();

    return 0;
}