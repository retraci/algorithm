#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

/*----------------------------------------*/

const int N = 1e5 + 10;

int ps[N], cs[N], tt;

void divide(int n) {
    tt = -1;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            ps[++tt] = i, cs[tt] = 0;
            while (n % i == 0) cs[tt]++, n /= i;
        }
    }
    if (n > 1) ps[++tt] = n, cs[tt] = 1;
}
