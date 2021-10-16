#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll n;

void solve() {
    ll tmp = n;
    ll sum = 0;
    while (tmp) {
        ll x = tmp % 10;
        tmp /= 10;
        sum += x * x * x;
    }

    cout << (sum == n ? 1 : 0) << endl;
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