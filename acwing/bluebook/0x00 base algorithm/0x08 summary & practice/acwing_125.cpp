#include <bits/stdc++.h>

using namespace std;

const int N = 50010;

int n;
int vw[N], vs[N], vi[N];

bool cmp(int a, int b) {
    return vw[a] + vs[a] < vw[b] + vs[b];
}

void solve() {
    for (int i = 0; i < n; i++) vi[i] = i;
    sort(vi, vi + n, cmp);

    int ans = -0x3f3f3f3f;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int idx = vi[i];
        ans = max(ans, sum - vs[idx]);
        sum += vw[idx];
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> vw[i] >> vs[i];
    }
    solve();

    return 0;
}