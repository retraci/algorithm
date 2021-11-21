#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    long long sum = 0;
    for (int j = 1; j <= 123456; j++) sum += j;
    sum *= 123456;
    cout << sum << endl;

    return 0;
}