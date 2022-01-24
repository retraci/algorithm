#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100010;

int n;
int va[maxn];

void solve() {
    sort(va, va + n);

    int mid = va[n / 2];

    int ans = 0;
    for (int i = 0; i < n; i++) ans += abs(mid - va[i]);

    cout << ans << endl;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) scanf("%d", &va[i]);
    solve();

    return 0;
}

