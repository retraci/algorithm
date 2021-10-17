#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110;

int n;
int va[N];

bool check(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return true;
    }
    return false;
}

void solve() {
    int sum = 0;
    for (int i = 1; i <= n; i++) sum += va[i];

    if (check(sum)) {
        cout << n << endl;
        for (int i = 1; i <= n; i++) cout << i << " ";
        cout << endl;
    } else {
        cout << n - 1 << endl;
        int id = 0;
        for (int i = 1; i <= n; i++) {
            if (check(sum - va[i])) id = i;
        }
        for (int i = 1; i <= n; i++) {
            if (i != id) cout << i << " ";
        }
        cout << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> va[i];
        }
        solve();
    }

    return 0;
}

