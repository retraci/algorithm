#include <bits/stdc++.h>

using namespace std;

const int N = 10010;

int n;
int vx[N], vy[N];

int calc(int *vv) {
    sort(vv, vv + n);

    int res = 0;
    for (int i = 0; i < n; i++) res += abs(vv[i] - vv[n / 2]);

    return res;
}

void solve() {
    sort(vx, vx + n);
    for (int i = 0; i < n; i++) vx[i] -= i;

    int ret = calc(vx) + calc(vy);

    cout << ret << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> vx[i] >> vy[i];
    solve();

    return 0;
}