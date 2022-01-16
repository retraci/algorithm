#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define ll long long

const int maxn = 500010;

int n, m;
ll t;
ll va[maxn], vb[maxn];
ll tmp[maxn];

bool check(int left, int mid, int right) {
    for (int i = mid; i < right; i++) vb[i] = va[i];
    sort(vb + mid, vb + right);

    int i = left, j = mid;
    for (int k = left; k < right; k++) {
        if (j >= right || i < mid && vb[i] <= vb[j]) tmp[k] = vb[i++];
        else tmp[k] = vb[j++];
    }

    ll sum = 0;
    i = left, j = right - 1;
    for (int k = 0; k < m && i < j; k++, i++, j--) {
        sum += (tmp[i] - tmp[j]) * (tmp[i] - tmp[j]);
    }

    return sum <= t;
}

void solve() {
    ll ans = 0;

    // 区间左开右闭
    int left = 0, right = 0;
    while (right < n) {
        ll step = 1;
        while (step) {
            if (right + step <= n && check(left, right, right + step)) {
                right += step;
                step <<= 1;
                if (right >= n) break;

                // 归并排序的结果，va不能改变，因为step可能会变短
                for (int i = left; i < right; i++) vb[i] = tmp[i];

            } else {
                step >>= 1;
            }
        }
        left = right;
        ans++;
    }

    cout << ans << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d%d%lld", &n, &m, &t);
        for (int i = 0; i < n; i++) scanf("%lld", &va[i]);
        solve();
    }

    return 0;
}

