#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

int n;

void solve() {
    ll sum = 0;
    for (int i = 1; i <= n; i += 2) sum += i;

    cout << sum << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    solve();

    return 0;
}