#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

ll n, m, va[N], vb[N], cnt[4], s[4][N], tmp[N];

bool check(ll mid) {
    memcpy(tmp, vb, sizeof tmp);

    ll round = mid / n, rem = mid % n;
    cnt[1] = s[1][n] * round + s[1][rem];
    cnt[2] = s[2][n] * round + s[2][rem];
    cnt[3] = s[3][n] * round + s[3][rem];

    // 用3, 变为偶数
    for (int i = 1; i <= m && cnt[3] > 0; i++) {
        if (tmp[i] >= 3 && tmp[i] & 1) {
            tmp[i] -= 3;
            cnt[3]--;
        }
    }

    // 用3, 一次用2个, 保证偶数
    for (int i = 1; i <= m && cnt[3] >= 2; i++) {
        ll need = tmp[i] / 6 * 2;
        ll used = min(need, cnt[3]);
        tmp[i] -= 3 * used;
        cnt[3] -= used;

        // 保证偶数
        if (used > 0 && cnt[3] == 0) {
            if (tmp[i] & 1) {
                cnt[3]++;
                tmp[i] += 3;
                break;
            }
        }
    }

    // 用3, 从多的开始扣
    // tip: cnt[3] 最多是2, 如果 m 为1, 需要跑2轮
    sort(tmp + 1, tmp + 1 + m, greater<int>());
    for (int i = 1; i <= m && cnt[3] > 0; i++) {
        if (tmp[i] == 0) continue;
        tmp[i] = max(0LL, tmp[i] - 3);
        cnt[3]--;
    }
    for (int i = 1; i <= m && cnt[3] > 0; i++) {
        if (tmp[i] == 0) continue;
        tmp[i] = max(0LL, tmp[i] - 3);
        cnt[3]--;
    }

    // 用2
    for (int i = 1; i <= m && cnt[2] > 0; i++) {
        ll need = tmp[i] / 2;
        ll used = min(need, cnt[2]);
        tmp[i] -= 2 * used;
        cnt[2] -= used;
    }
    // 用2
    for (int i = 1; i <= m && cnt[2] > 0; i++) {
        if (tmp[i] == 0) continue;
        tmp[i] = max(0LL, tmp[i] - 2);
        cnt[2]--;
    }

    // 用1
    ll need = 0;
    for (int i = 1; i <= m; i++) {
        need += tmp[i];
    }

    return need <= cnt[1];
}

void solve() {
    memset(s, 0, sizeof s);
    for (int i = 1; i <= n; i++) {
        s[1][i] = s[1][i - 1] + (va[i] == 1);
        s[2][i] = s[2][i - 1] + (va[i] == 2);
        s[3][i] = s[3][i - 1] + (va[i] == 3);
    }

    ll sum = 0;
    for (int i = 1; i <= m; i++) sum += vb[i];
    ll left = m, right = sum;
    while (left < right) {
        ll mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

    printf("%lld\n", left);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &va[i]);
        }
        scanf("%lld", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%lld", &vb[i]);
        }
        solve();
    }

    return 0;
}