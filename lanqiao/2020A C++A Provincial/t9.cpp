// 超级胶水

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

int n;
int va[N];

void solve() {
    ll ans = 0;

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        ans += va[i] * sum;
        sum += va[i];
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; i++) scanf("%d", &va[i]);
    solve();

    return 0;
}