#include <cstdio>

using namespace std;

const int maxn = 500010;

int n;
long long cnt;
int va[maxn], vb[maxn];

void merge(int l, int r) {
    if (l >= r) return;

    int mid = l + r >> 1;

    merge(l, mid);
    merge(mid+1, r);

    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (j > r || i <= mid && va[i] <= va[j]) {
            vb[k] = va[i++];
        } else {
            vb[k] = va[j++];
            cnt += mid - i + 1;
        }
    }

    for (int k = l; k <= r; k++) va[k] = vb[k];
}

void solve() {
    cnt = 0;

    merge(0, n-1);

    printf("%lld\n", cnt);
}

int main() {
    while (~scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++) scanf("%d", &va[i]);
        solve();
    }

    return 0;
}

