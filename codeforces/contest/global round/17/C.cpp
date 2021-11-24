#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

int n;
int va[N], vb[N];

bool check(int mid) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt <= vb[i] && mid - cnt - 1 <= va[i]) cnt++;
    }
    return cnt >= mid;
}

void solve() {
    int left = 1, right = n;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i] >> vb[i];
        solve();
    }

    return 0;
}