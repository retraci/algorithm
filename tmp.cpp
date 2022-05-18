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
