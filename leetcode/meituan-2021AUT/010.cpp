#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010;

int n, m;
int va[N];

bool check(int mid, int R) {
    int pre = -1;
    for (int i = 0; i < n; i++) {
        if (va[i] < mid || va[i] > R) {
            if (va[i] < pre) return false;
            pre = va[i];
        }
    }
    return true;
}

void solve() {
    int ans = 0;
    for (int R = m; R > 0; R--) {
        int left = 0, right = R;
        while (left < right) {
            int mid = right + left + 1 >> 1;
            if (check(mid, R)) left = mid;
            else right = mid - 1;
        }
        if (0 == left) break;
        ans += left;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> m >> n;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &va[i]);
    }
    solve();

    return 0;
}