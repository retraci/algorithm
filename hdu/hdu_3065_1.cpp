// HDU 3065 病毒侵入持续中
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int trie[50010][26],fail[50010],flag[50010],tn;
char pat[1010][55];
int mark[1010];
int n;
char str[2000010];

void insert(char *s,int id) {
	int now = 0;
	for(int i=0; s[i]; i++) {
		int ch = s[i]-'A';
		if(trie[now][ch] == 0) trie[now][ch] = ++tn;
		now = trie[now][ch];
	}
	flag[now] = id;
}

void get_fail() {
	memset(fail,0,sizeof(fail));
	fail[0] = -1;
	queue<int> q;
	for(int i=0; i<4; ++i) {
		if(trie[0][i]) q.push(trie[0][i]);
	}
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		for(int i=0; i<4; ++i) {
			if(trie[now][i]) {
				int p = trie[fail[now]][i];
				while(p!=-1 && trie[p][i]==0) p = fail[p];
				fail[trie[now][i]] = p!=-1?trie[p][i]:0;
				q.push(trie[now][i]);
			}
		}
	}
}

void query(char *str) {
	int p = 0;
	int len = strlen(str);
	int ch;
	for(int i=0; i<len; i++) {
		ch = str[i]-'A';
		if(ch>=26 || ch<0) {
			p = 0;
			continue;
		}
		while(p!=-1 && trie[p][ch]==0) p = fail[p];
		p = p!=-1?trie[p][ch]:0;
		int temp = p;
		while(temp != -1) {
			if(flag[temp] != 0) 
				mark[flag[temp]]++;
			temp = fail[temp];
		}
	}
}

int main() {
	while(~scanf("%d",&n)) {
		memset(mark,0,sizeof(mark));
		for(int i=1; i<=n; i++) {
			scanf("%s",pat[i]);
			insert(pat[i],i);
		}
		get_fail();
		scanf("%s",str);
		query(str);
		for(int i=1; i<=n; i++) {
			if(mark[i]) {
				printf("%s: %d\n",pat[i],mark[i]);
			}
		}
	}

	return 0;
}
