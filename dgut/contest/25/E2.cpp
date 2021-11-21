#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <time.h>
#include <cmath>

using namespace std;

#define ll long long
#define T0 50000.0  // 初始温度
#define T_end (1e-8)
#define q  0.98   // 退火系数
#define L 3000  // 每个温度时的迭代次数，即链长
#define M 33  // 最大城市数量

int n;
int city_list[M]; // 用于存放一个解
ll d[M][M];

// 距离函数
ll distance(int city1, int city2) {
    return d[city1][city2];
}

// 计算路径长度
ll path_len(int *arr) {
    ll path = 0; // 初始化路径长度
    for (int i = 0; i < n - 1; i++) {
        int index1 = *(arr + i);
        int index2 = *(arr + i + 1);
        ll dis = distance(index1, index2);
        path += dis;
    }
    return path; // 返回总的路径长度
}

// 初始化函数
void init() {
    // 初始化一个解
    for (int i = 0; i < n; i++) {
        city_list[i] = i + 1;
    }
}

// 产生一个新解
// 此处采用随机交叉两个位置的方式产生新的解
void create_new() {
    int pos1 = 0, pos2 = 0, temp;
    while (pos1 == 0 || pos2 == 0 || pos1 == n - 1 || pos2 == n - 1) {
        double r1 = ((double) rand()) / (RAND_MAX + 1.0);
        double r2 = ((double) rand()) / (RAND_MAX + 1.0);
        // 第一个交叉点的位置
        pos1 = (int) (n * r1);
        pos2 = (int) (n * r2);
    }

    // 交换两个点
    temp = city_list[pos1];
    city_list[pos1] = city_list[pos2];
    city_list[pos2] = temp;
}

void work2() {
    srand((unsigned) time(NULL)); // 初始化随机数种子
    double T;
    T = T0; // 初始温度
    init(); // 初始化一个解
    int city_list_copy[n]; // 用于保存原始解
    double f1, f2, df; // f1为初始解目标函数值，f2为新解目标函数值，df为二者差值
    double r; // 0-1之间的随机数，用来决定是否接受新解
    // 当温度低于结束温度时，退火结束
    while (T > T_end) {
        for (int i = 0; i < L; i++) {
            // 复制数组
            memcpy(city_list_copy, city_list, n * sizeof(int));
            // 产生新解
            create_new();
            f1 = path_len(city_list_copy);
            f2 = path_len(city_list);
            df = f2 - f1;
            // 以下是Metropolis准则
            if (df >= 0) {
                r = ((double) rand()) / (RAND_MAX);
                // 保留原来的解
                if (exp(-df / T) <= r) {
                    memcpy(city_list, city_list_copy, n * sizeof(int));
                }
            }
        }
        // 降温
        T *= q;
    }

    ll len = path_len(city_list); // 最优路径长度
    cout << len << endl;
}

void work() {
    int lim = 1 << n;
    ll f[n][lim];
    memset(f, 0x3f, sizeof f);

    f[0][1] = 0;
    for (int mask = 0; mask < lim; mask++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (mask >> v & 1) continue;
                int ns = mask | (1 << v);
                f[v][ns] = min(f[v][ns], f[u][mask] + d[u + 1][v + 1]);
            }
        }
    }

    cout << f[n - 1][lim - 1] << endl;
}

void solve() {
    if (n >= 18) work2();
    else work();
}


int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> d[i][j];
        }
    }
    solve();

    return 0;
}