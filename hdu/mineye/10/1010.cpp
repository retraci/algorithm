#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

int n, m;
ll h1[N], hd1[N], s1[N], sd1[N];
ll h2[N], hd2[N], s2[N], sd2[N];
double ch1[N], cs1[N], ch2[N], cs2[N];

bool check(ll mid) {
    for (int i = 0; i < n; i++) {
        ch1[i] = h1[i] + mid * hd1[i];
        cs1[i] = s1[i] + mid * sd1[i];

//        cout << ch1[i] << " " << cs1[i] << endl;
    }
    for (int i = 0; i < m; i++) {
        ch2[i] = h2[i] + mid * hd2[i];
        cs2[i] = s2[i] + mid * sd2[i];

//        cout << ch2[i] << " " << cs2[i] << endl;
    }

    int p1 = 0, p2 = 0;
    while (p1 < n && p2 < m) {
        double t1 = ch1[p1] / cs2[p2];
        double t2 = ch2[p2] / cs1[p1];

//        cout << p1 << " " << p2 << " " << t1 << " " << t2 << " ";

        if (t2 < t1) {
            ch1[p1] -= t2 * cs2[p2];

//            cout << ch1[p1] << endl;

            p2++;
        } else {
            ch2[p2] -= t1 * cs1[p1];

//            cout << ch2[p2] << endl;

            p1++;
        }
    }

//    cout << mid << " " << p1 << " " << n << endl;

    return p1 < n;
}

void solve() {
    ll lim = 1e12;
    ll left = 0, right = lim;
    while (left < right) {
        ll mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

    if (left == lim) puts("none");
    else cout << left << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            scanf("%lld%lld%lld%lld", &h1[i], &hd1[i], &s1[i], &sd1[i]);
//            h1[i] *= 1e5, hd1[i] *= 1e5, s1[i] *= 1e2, sd1[i] *= 1e2;
        }
        for (int i = 0; i < m; i++) {
            scanf("%lld%lld%lld%lld", &h2[i], &hd2[i], &s2[i], &sd2[i]);
//            h2[i] *= 1e5, hd2[i] *= 1e5, s2[i] *= 1e2, sd2[i] *= 1e2;
        }
        solve();
    }

    return 0;
}