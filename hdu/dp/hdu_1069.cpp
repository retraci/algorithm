// HDU 1069 Monkey and Banana
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 200;

struct Block{
	int x,y,z;
} bs[maxn];

int n,len,ans;
int dp[maxn];				// 以 x 为底层可达的最大高度 

// 保证无后效性 
bool cmp(Block a,Block b) {
	if(a.x != b.x) return a.x < b.x;
	else return a.y < b.y;
}

int main() {
	int casee = 1;
	while(cin >> n && n) {
		int a,b,c;
		len = 0;
		ans = -1;
		for(int i=0;i<n;i++) {
			cin >> a >> b >> c;
			bs[len].x=a;bs[len].y=b;bs[len++].z=c;
			bs[len].x=a;bs[len].y=c;bs[len++].z=b;
			bs[len].x=b;bs[len].y=a;bs[len++].z=c;
			bs[len].x=b;bs[len].y=c;bs[len++].z=a;
			bs[len].x=c;bs[len].y=a;bs[len++].z=b;
			bs[len].x=c;bs[len].y=b;bs[len++].z=a;
		}
		sort(bs,bs+len,cmp);
		
		for(int i=0;i<len;i++) {
			cout << bs[i].x << " " << bs[i].y << endl;
		}

		for(int i=0;i<len;i++) {
			dp[i] = bs[i].z;
			for(int j=i-1;j>=0;j--) {
				if(bs[i].x>bs[j].x && bs[i].y>bs[j].y)
					dp[i] = dp[i]>bs[i].z+dp[j]?dp[i]:bs[i].z+dp[j];
			}
			ans = ans>dp[i]?ans:dp[i];
		}
		
		printf("case %d:maximum height=%d\n",casee++,ans);
	}
		
	return 0;
}
