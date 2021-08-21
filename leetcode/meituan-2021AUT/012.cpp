#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 10010;
const int M = 100010;

int n, m, q;
int va[N];
int lock[N];

void solve() {
    memset(va, 0, sizeof va);
    memset(lock, 0, sizeof lock);
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d%d", &x, &y);

            if (va[x] != -1 && !lock[va[x]] && !lock[y]) va[x] = y;
        } else if (op == 2) {
            int x;
            scanf("%d", &x);

            lock[x] = 1;
        } else if (op == 3) {
            int x;
            scanf("%d", &x);

            lock[x] = 0;
        } else if (op == 4) {
            int x;
            scanf("%d", &x);

            if (va[x] <= 0 || lock[va[x]]) {
                cout << -1 << endl;
            } else {
                cout << va[x] << endl;
                va[x] = -1;
            }
        } else {
            int x;
            scanf("%d", &x);

            if (va[x] == -1) va[x] = 0;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m >> q;
    solve();

    return 0;
}