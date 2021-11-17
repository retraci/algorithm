#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 110;

typedef pair<int, int> pii;

int n, m;
pii va[N];
int d[N];

void solve() {
    for (int i = 1; i <= m; i++) {
        auto &[a, b] = va[i];
        for (int j = a; j <= b; j++) d[j]++;
    }

    for (int i = 1; i <= n; i++) {
        if (d[i] != 1) {
            cout << i << " " << d[i] << endl;
            return;
        }
    }
    cout << "YES" << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        va[i] = {a, b};
    }
    solve();

    return 0;
}