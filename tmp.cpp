#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define mp make_pair
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

// region SA
template<int SZ>
struct SA {
    int n, sa[SZ + 10], rk[SZ + 10], prk[SZ * 2 + 10], id[SZ + 10], px[SZ + 10], cnt[SZ + 10];

    SA () {}

    // s 下标从 1 开始
    vector<int> get_sa(const string &s, int m = 300) {
        n = s.size() - 1;
        fill(cnt, cnt + m + 1, 0);
        fill(prk, prk + 2 * n + 1, 0);

        for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;

        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (int i = n; i >= n - k + 1; i--) id[++p] = i;
            for (int i = 1; i <= n; i++) {
                if (sa[i] - k >= 1) id[++p] = sa[i] - k;
            }

            fill(cnt, cnt + m + 1, 0);
            for (int i = 1; i <= n; i++) cnt[px[i] = rk[id[i]]]++;
            for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; i--) sa[cnt[px[i]]--] = id[i];

            for (int i = 1; i <= n; i++) prk[i] = rk[i];
            rk[sa[1]] = 1, p = 1;
            for (int i = 2; i <= n; i++) {
                int x = sa[i], y = sa[i - 1];
                rk[sa[i]] = prk[x] == prk[y] && prk[x + k] == prk[y + k] ? p : ++p;
            }

            if (p == n) {
                vector<int> res(n + 1);
                for (int i = 1; i <= n; i++) res[i] = sa[i];
                return res;
            }

            m = p;
        }
    }

    vector<int> get_h(const string &s) {
        vector<int> res(n + 1);
        int k = 0;
        for (int i = 1; i <= n; i++) {
            if (rk[i] == 0) continue;
            if (k) k--;
            int j = sa[rk[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            res[rk[i]] = k;
        }

        return res;
    }
};
// endregion

int rnd(int mod) {
    return mrnd() % mod;
}

int ask(ll L, ll R) {
    cout << L << " " << R << "\n";
    cout.flush();
    string ret;
    cin >> ret;
    return ret[0] == 'Y';
}

void solve(ll n, ll k) {
    ll L = 1, R = n;
    while (1) {
        while (R - L + 1 > 4 * k + 3) {
            ll md = L + R >> 1;
            if (ask(L, md)) R = md;
            else L = md + 1;
            L = max(1LL, L - k), R = min(n, R + k);
        }

        ll p = rnd(R - L + 1) + L;
        if (ask(p, p)) return;

        L = max(1LL, L - k), R = min(n, R + k);
    }
}

int main() {
    ll n, k;
    scanf("%lld%lld", &n, &k);
    solve(n, k);

    return 0;
}
