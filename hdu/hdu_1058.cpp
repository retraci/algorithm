// HDU 1058 Humble Numbers
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxn = 5900;

int n;
int dp[maxn];

int main() {
	
	while(scanf("%d",&n)!=EOF && n) {
		int t1 = n%10;
		int t2 = n%100;
		if(t==1 && t2!=11) printf("The %dst humble number is %d\n.",n,dp[n]);break;
		else if(t==2 && t2!=12) printf("The %dnd humble number is %d\n.",n,dp[n]);break;
		else if(t==3 && t2!=13) printf("The %drd humble number is %d\n.",n,dp[n]);break;
		else printf("The %dth humble number is %d\n.",n,dp[n]);
		
	}
	
	return 0;
}
