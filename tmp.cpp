#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>

// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

using namespace std;
#define int long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
#define eb emplace_back
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef double db;
constexpr int P = 20101009;
using i64=long long;
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
};

const int N=1e7,M=1e7+10;
Z f[M],mu[M],g[M];
bool vis[M];
VI pri;


Z sum(int x,int y){
    return (x*(x+1)/2)%P*(y*(y+1)/2%P)%P;
}

void solve() {
}

void prework() {
}

signed main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    IOS

    f[1]=1;
    for (int i=2;i<=N;++i){
        if (!vis[i]) pri.pb(i),f[i]=i-1LL*i*i%P;
        for (int j:pri){
            if (i*j>N) break;
            vis[i*j]=1;
            if (i%j==0){
                f[i*j]=f[i]*j;
                break;
            }
            f[i*j]=f[i]*f[j];
        }
    }
    for (int i=2;i<=N;++i) f[i]=f[i-1]+f[i];

    int n,m;
    Z ans;
    cin>>n>>m;
    if (n>m) swap(n,m);
    for (int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=(f[r]-f[l-1]) * sum(n/l,m/l);
    }
    for (int i = 1; i <= N; i++) cout << f[i].val() << "\n";

    cout<<ans.val();


    return 0;
}