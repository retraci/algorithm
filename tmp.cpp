#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct node {
    int x, p;
    bool operator < (const node &A) const {
        return x < A.x;
    }
} a[200001], b[200001];
int n, A[200001], B[200001], f[200001];

inline void insert(int x) {
    for (; x <= n; x += x & (-x))
        f[x]++;
}

int calc(int x) {
    int res = 0;
    for (; x; x -= x & (-x))
        res += f[x];
    return res;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i].x), a[i].p = i;
    sort(a + 1, a + n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1 || a[i].x != a[i - 1].x)
            ++cnt;
        A[a[i].p] = cnt;
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i].x), b[i].p = i;
    sort(b + 1, b + n + 1);
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1 || b[i].x != b[i - 1].x)
            ++cnt;
        B[b[i].p] = cnt;
    }
    long long ans = 0;
    int l = n;
    for (; l; ) {
        int r = l;
        for (; r && a[r].x == a[l].x; --r)
            ans += n - l;
        l = r;
    }
    cout << ans << "\n";
    l = n;
    for (; l; ) {
        int r = l;
        for (; r && b[r].x == b[l].x; --r)
            ans += n - l;
        l = r;
    }
    cout << ans << "\n";


    l = n;
    for (; l;) {
        int r = l;
        for (; r && a[r].x == a[l].x; --r)
            ans -= calc(B[a[r].p] - 1);
        r = l;
        for (; r && a[r].x == a[l].x; --r)
            insert(B[a[r].p]);
        l = r;
    }
    printf("%lld\n", 1LL * n * n - ans);
}