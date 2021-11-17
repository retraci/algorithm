// HDU 1024 Max Sum Plus Plus
// m子段和的最大值
#include <iostream>
#include <algorithm>
#include <cstring>

#define INF 0x3f3f3f3f

using namespace std;

const int maxn = 1000010;

int n,m;
int a[maxn];
int dp[maxn];				// 分 i 个子段， j 个数字，且一定包含 j
int maxx[maxn];				// 记录 1 ~ j-1 的最大值

int main() {
	while(~scanf("%d%d",&m,&n)) {
		memset(dp,0,sizeof dp);
		memset(maxx,0,sizeof maxx);

		for(int i=1; i<=n; i++)
			scanf("%d",&a[i]);

		int temp = -INF;			// 记录前一个的最大值
		for(int j=1; j<=n; j++) {
			if(dp[j-1]>0)
				dp[j] = dp[j-1]+a[j];
			else 
				dp[j] = a[j];
			maxx[j-1] = temp;
			temp = max(dp[j],temp);
		}

		for(int i=2; i<=m; i++) {
			temp = -INF;
			for(int j=i; j<=n; j++) {
				// j 为 j-1的同一组与 j 独自一组 (这种有着以 1 结尾到 以 j-1 结尾
				dp[j] = max(dp[j-1],maxx[j-1])+a[j];
				maxx[j-1] = temp;
				temp = max(dp[j],temp);
			}
		}
		cout << temp << endl;
	}

	return 0;
}
