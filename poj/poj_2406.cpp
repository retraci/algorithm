// POJ 2406 Power Strings
// Ñ­»·×Ö·û´®
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1e6+10;
char s[MAXN];
int nxt[MAXN];
int len;

void get_next() {
	int i=0,j=-1;
	nxt[0] = -1;
	while(i<len) {
		if(j==-1 || s[i]==s[j]) nxt[++i] = ++j;
		else j = nxt[j];
	}
}

int main() {
	while(scanf("%s",s) && s[0]!='.') {
		len = strlen(s);
		get_next();
		if(len%(len-nxt[len])) 
			printf("1\n");
		else 
			printf("%d\n",len/(len-nxt[len]));
		
	}

	return 0;
}


