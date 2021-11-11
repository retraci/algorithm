#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1e5 + 10;

int n;
int va[N];

void solve() {
    sort(va + 1, va + 1 + n);

    int id = 1 + n >> 1;
    cout << va[id] << " ";
    for (int i = 1; i <= n - 1; i++) {
        if (i & 1) id += i;
        else id -= i;
        cout << va[id] << " ";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> va[i];
    }
    solve();

    return 0;
}