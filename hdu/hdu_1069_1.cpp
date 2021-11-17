// HDU 1069 Monkey And Banana
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Block {
	int x,y,z;
	Block(int xx,int yy,int zz):x(xx),y(yy),z(zz) {
	}
	bool operator < (const Block &t) const {
		if(x!=t.x) return x < t.x;
		else return y < t.y;
	}
};

const int maxn = 200;

int n;
int dp[maxn];
vector<Block> v;

int main() {
	int casee = 1;
	int x,y,z;
	while(~scanf("%d",&n) && n) {
		v.clear();
		for(int i=0; i<n; i++) {
			scanf("%d%d%d",&x,&y,&z);
			v.push_back(Block(x,y,z));
			v.push_back(Block(x,z,y));
			v.push_back(Block(y,x,z));
			v.push_back(Block(y,z,x));
			v.push_back(Block(z,x,y));
			v.push_back(Block(z,y,x));
		}
		sort(v.begin(),v.end());
//		for(int i=0;i<v.size();i++) {
//			printf("%d %d %d\n",v[i].x,v[i].y,v[i].z);
//		}
		for(int i=0;i<v.size();i++) {
			dp[i] = v[i].z;
			for(int j=0;j<i;j++) {
				if(v[i].x>v[j].x && v[i].y>v[j].y) {
					dp[i] = max(dp[i],v[i].z+dp[j]);
				}
			}
		}
		int ans = 0;
		for(int i=0;i<v.size();i++) {
			ans = max(ans,dp[i]);
		}
		printf("Case %d: maximum height = %d\n",casee++,ans);
	}

	return 0;
}
