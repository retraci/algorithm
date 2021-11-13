#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 15;

int n = 12;

int d[maxn], f[maxn];

void solve() {
    d[1] = 1;

    for (int i = 2; i <= n; i++) {
        d[i] = 2 * d[i-1] + 1;
    }

    memset(f, 0x3f, sizeof(f));
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; i-j >= 1; j++) {
            f[i] = min(f[i], 2 * f[j] + d[i-j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << f[i] << endl;
    }
}

int main() {
    solve();

    return 0;
}

