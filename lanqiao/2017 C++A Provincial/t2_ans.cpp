#include<bits/stdc++.h>
using namespace std;

char *start="012345678";//声明两个字符类型的指针，表示初始状态和目标状态
char *target="087654321";

struct StateAndLevel{//声明结构体，状态和层次
    char *state;//当前状态，即对应此时的字符串
    int level; //层次 ，即走了几步
    int pos0;//0的初始位置
    StateAndLevel(char* state,int level,int pos0):state(state),level(level),pos0(pos0){}//构造函数
};

struct cmp{//声明结构体，用于和set进行比较
    bool operator()(char *a,char *b){
        return strcmp(a,b)<0;//表示比较结果不相等
    }
};

//声明队列和set集合
queue<StateAndLevel>q;
set<char*,cmp>allState;//cmp是加的比较

//交换的函数
void swap(char *s,int a,int b){
    char t=s[a];
    s[a]=s[b];
    s[b]=t;
}

void addNei(char* state,int pos,int newPos,int le){//添加邻居
    char *new_state=(char *)malloc(9*sizeof(char));//为新的状态分配内存空间
    strcpy(new_state,state);//将state拷贝到new-state中
    swap(new_state,pos,newPos);//交换
    if(allState.find(new_state)==allState.end()){//set内找不到重复元素就执行
        allState.insert(new_state);//把新的状态添加到set集合中
        q.push(StateAndLevel(new_state,le+1,newPos));//将新的状态放在队列的末端
    }
}

int main(){
    q.push(StateAndLevel(start,0,0));//初始状态，层次为0，放到队列中
    while(!q.empty()){//如果队列不为空，就执行循环
        StateAndLevel sal=q.front();//访问队列头结点
        char *state=sal.state;//声明状态
        int le=sal.level;//声明层次
        int pos0=sal.pos0;//声明0的位置
        allState.insert(state); //添加到set避免重复

        if(strcmp(state,target)==0){//退出循环的出口，状态和目标状态相同执行
            printf("%d",le);
            return 0;
        }

        int new_pos=(pos0-1+9)%9;//空盘与右边第一个盘子交换
        addNei(state,pos0,new_pos,le);
        new_pos=(pos0+1+9)%9;//空盘与左第一个盘子交换
        addNei(state,pos0,new_pos,le);
        new_pos=(pos0-2+9)%9;//空盘右二交换
        addNei(state,pos0,new_pos,le);
        new_pos=(pos0+2+9)%9;//空盘左二交换
        addNei(state,pos0,new_pos,le);
        q.pop();//弹出队列第一个元素
    }
    return 0;
}