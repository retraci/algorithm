#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_set>
#include <ctime>
#include <random>

using namespace std;

#define ll long long

ll x1, y11, z1, x2, y2, z2;
int va[10], vb[10];
unordered_set<int> st;

ll calc1(ll x, ll y, ll z) {
    return 1000LL * x - y * y - z * z < 0;
}

ll calc2(ll x, ll y, ll z) {
    return 1000LL * y - x * x - z * z < 0;
}

ll calc3(ll x, ll y, ll z) {
    return 1000LL * z - y * y - x * x < 0;
}

ll calc4(ll x, ll y, ll z) {
    return -1000LL * x - y * y - z * z < 0;
}

ll calc5(ll x, ll y, ll z) {
    return -1000LL * y - x * x - z * z < 0;
}

ll calc6(ll x, ll y, ll z) {
    return -1000LL * z - y * y - x * x < 0;
}

int get_hash(int *v) {
    return (v[5] << 5) + (v[4] << 4) + (v[3] << 3) + (v[2] << 2) + (v[1] << 1) + v[0];
}

void solve() {
    va[0] = calc1(x1, y11, z1);
    va[1] = calc2(x1, y11, z1);
    va[2] = calc3(x1, y11, z1);
    va[3] = calc4(x1, y11, z1);
    va[4] = calc5(x1, y11, z1);
    va[5] = calc6(x1, y11, z1);

//    st.insert(get_hash(va));

    vb[0] = calc1(x2, y2, z2);
    vb[1] = calc2(x2, y2, z2);
    vb[2] = calc3(x2, y2, z2);
    vb[3] = calc4(x2, y2, z2);
    vb[4] = calc5(x2, y2, z2);
    vb[5] = calc6(x2, y2, z2);

//    st.insert(get_hash(vb));

    int flag = 0;
    for (int i = 0; i < 6; i++) {
        if (va[i] != vb[i]) flag = 1;
    }

    if (!flag) puts("Yes");
    else puts("No");
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

//    work();

    int T;
    cin >> T;
    while (T--) {
        cin >> x1 >> y11 >> z1 >> x2 >> y2 >> z2;
        solve();
    }

    return 0;
}