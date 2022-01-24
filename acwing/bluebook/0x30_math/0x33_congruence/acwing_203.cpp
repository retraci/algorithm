#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

int a, b;

int exgcd(int a, int b, ll &x, ll &y) {
    if (b == 0) { x = 1, y = 0; return a; }
    int d = exgcd(b, a % b, x, y);
    int z = x; x = y; y = z - (a / b) * y;
    return d;
}

void solve() {
    ll x, y;
    exgcd(a, b, x, y);
    int ans = (x % b + b) % b;
    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> a >> b;
    solve();

    return 0;
}