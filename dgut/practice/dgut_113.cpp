#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

int n;

void solve() {
    ll sum = 1;
    for (int i = 1; i <= n - 1; i++) sum = (sum + 1) * 2;

    cout << sum << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    while (cin >> n) solve();

    return 0;
}