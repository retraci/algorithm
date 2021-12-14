#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct node {
    int x, p;
    bool operator < (const node &A) const {
        return x < A.x;
    }
} a[200001], b[200001];
int n, A[200001], B[200001], f[200001];

inline void insert(int x) {
    for (; x <= n; x += x & (-x))
        f[x]++;
}

int calc(int x) {
    int res = 0;
    for (; x; x -= x & (-x))
        res += f[x];
    return res;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

}