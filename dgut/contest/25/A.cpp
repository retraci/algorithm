#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

const int N = 1e6 + 10;

int n;
pii va[N];

void solve() {
    sort(va + 1, va + 1 + n);

    for (int i = 1; i <= n; i++) {
        auto &[_, id] = va[i];
        if (id == 1) {
            cout << i << endl;
        }
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
        int sum = 0;
        for (int _ = 0; _ < 5; _++) {
            int tmp = 0;
            cin >> tmp;
            sum += tmp;
        }
        va[i] = {-sum, i};
    }
    solve();

    return 0;
}