// HDU 2896 ²¡¶¾ÇÖÏ®
// AC×Ô¶¯»ú
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	node *nxt[95];
	node *fail;
	int id;
	node() {
		memset(nxt,NULL,sizeof(nxt));
		fail = NULL;
		id = 0;
	}
};

node * root;
int mark[510];

void init() {
	root = new node;
}

void insert(char *str,int id) {
	int len = strlen(str);
	node *p = root;
	int ch;
	for(int i=0; i<len; i++) {
		ch = str[i]-33;
		if(p->nxt[ch] == NULL) {
			p->nxt[ch] = new node;
		}
		p = p->nxt[ch];
	}
	p->id = id;
}

void get_fail() {
	node *fa;
	queue<node*> q;
	q.push(root);
	while(!q.empty()) {
		fa = q.front();
		q.pop();
		for(int i=0; i<95; i++) {
			if(fa->nxt[i]) {
				node *p = fa->fail;
				while(p && p->nxt[i]==NULL) p = p->fail;
				fa->nxt[i]->fail = p?p->nxt[i]:root;
				q.push(fa->nxt[i]);
			}
		}
	}
}

int query (char *str) {
	node *p = root;
	int len = strlen(str);
	int ch;
	int flag = 0;
	for(int i=0; i<len; i++) {
		ch = str[i]-33;
		while(p && p->nxt[ch]==NULL) p = p->fail;
		p = p?p->nxt[ch]:root;
		node *t = p;
		while(t != NULL && !mark[t->id]) {
//			cout << t->id << endl;
			if(t->id>0) {
				mark[t->id] = 1;
				flag = 1;
			}
			t = t->fail;
		}
	}
	return flag;
}

int main() {
	init();
	char str[10010];
	int n,m;
	scanf("%d\n",&n);
	for(int i=1; i<=n; i++) {
		gets(str);
		insert(str,i);
	}
	get_fail();
	scanf("%d\n",&m);
	int tot = 0;
	for(int i=1; i<=m; i++) {
		memset(mark,0,sizeof(mark));
		gets(str);
		if(query(str)) {
			tot++;
			printf("web %d:",i);
			int cnt = 0;
			for(int j=1; j<=n; j++) {
				if(mark[j]) {
					printf(" %d",j);
					cnt++;
				}
				if(cnt>=3) break;
			}
			cout << endl;
		}
	}
	printf("total: %d\n",tot);

	return 0;
}
