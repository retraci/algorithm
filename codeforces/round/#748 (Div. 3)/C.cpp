#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 4e5 + 10;

ll n, K;
ll va[N];
ll s[N];

void solve() {
    sort(va + 1, va + K + 1, greater<>());
    s[0] = 0;
    for (int i = 1; i <= K; i++) s[i] = s[i - 1] + (n - va[i]);

//    for (int i = 1; i <= K; i++) cout << s[i] << " ";
//    cout << endl;

    int ans = 0;
    for (int i = 0; i <= K; i++) {
        if (s[i] > n - 1) break;
        ans = i;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> K;
        for (int i = 1; i <= K; i++) cin >> va[i];
        solve();
    }

    return 0;
}