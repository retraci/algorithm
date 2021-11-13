#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define ll long long

const int maxn = 1000010;

int n;
ll va[maxn];

void solve() {
    ll tar = 0;
    for (int i = 1; i <= n; i++) tar += va[i];
    tar /= n;

    for (int i = 1; i <= n; i++) va[i] -= tar;
    for (int i = 1; i <= n; i++) va[i] += va[i-1];

    nth_element(va+1, va+1+n/2, va+1+n);

    ll median = va[1+n/2];

    ll ans = 0;
    for (int i = 1; i <= n; i++) ans += abs(va[i] - median);

    cout << ans << endl;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%lld", &va[i]);
    solve();

    return 0;
}

