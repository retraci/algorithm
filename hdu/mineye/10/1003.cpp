#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n, i, max1 = -1, ans = 0;
int a[201], k[700*700];


void chai(int t, int tot) {
    int i;
    if (tot == n) {
        int sum = a[1], num = 0;
        for (i = 2; i <= t - 1; i++) {
            num += sum * a[i];
            sum += a[i];
        }
        k[num] = 1;
        if (num > max1) max1 = num;
        return;
    }
    for (i = a[t - 1]; i <= (n - tot); i++) {
        if (i == 0) continue;
        a[t] = i;
        chai(t + 1, tot + i);
        a[t] = 0;
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
        memset(k, 0, sizeof k);
        chai(1, 0);
        a[0] = 0;
        for (i = 0; i <= max1; i++) {
            if (k[i] == 1) cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
