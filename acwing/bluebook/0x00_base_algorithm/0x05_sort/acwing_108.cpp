#include <cstdio>

using namespace std;

const int maxn = 510;

int n, tot;
int va[maxn*maxn];
int vb[maxn*maxn];
int vc[maxn*maxn];
int cnt;
int cnt1, cnt2;

void merge(int* vv, int l, int r) {
    if (l >= r) return;

    int mid = l + r >> 1;
    merge(vv, l, mid);
    merge(vv, mid+1, r);

    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (j > r || i <= mid && vv[i] <= vv[j]) {
            vc[k] = vv[i++];
        } else {
            vc[k] = vv[j++];
            cnt += mid - i + 1;
        }
    }

    for (int k = l; k <= r; k++) vv[k] = vc[k];
}

void solve() {
    if (tot == 0) {
        puts("TAK");
        return;
    }

    cnt = 0;
    merge(va, 0, tot-1);
    cnt1 = cnt & 1;

    cnt = 0;
    merge(vb, 0, tot-1);
    cnt2 = cnt & 1;

    if (cnt1 == cnt2) puts("TAK");
    else puts("NIE");
}

int main() {
    int tmp;
    while (~scanf("%d", &n)) {
        tot = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &tmp);
                if (tmp == 0) continue;
                va[tot++] = tmp;
            }
        }

        tot = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &tmp);
                if (tmp == 0) continue;
                vb[tot++] = tmp;
            }
        }

        solve();
    }

    return 0;
}

