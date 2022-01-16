#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
int vs[N], ve[N], vd[N];

int calc(int x) {
    if (x < 0) return 0;

    int ret = 0;
    for (int k = 0; k < n; k++) {
        int rb = min(ve[k], x);
        if (rb - vs[k] >= 0)
            ret += (rb - vs[k]) / vd[k] + 1;
    }

    return ret;
}

bool check(int mid) {
    return calc(mid) & 1;
}

void solve() {
    if (!check(INT_MAX)) {
        puts("There's no weakness.");
        return;
    }

    int left = 0, right = INT_MAX;
    while (left < right) {
        int mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

//    cout << endl << calc(1) << endl << endl;
    cout << left << " " << calc(left) - calc(left - 1) << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> vs[i] >> ve[i] >> vd[i];
        solve();
    }

    return 0;
}