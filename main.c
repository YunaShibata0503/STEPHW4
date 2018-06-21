
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define N 7
#define M 4

//隣接リスト
int adjacent[N + 1][M] = {
    {0},
    {2, 3, 0},
    {1, 3, 4, 0},
    {1, 2, 5, 0},
    {2, 5, 6, 0},
    {3, 4, 7, 0},
    {4, 0},
    {5, 0},
};

int page[100]={0,1,2,3,4,5,6,7};
char *p[1000]={"ando","launguage","japanese","geographics","EU_","countries","Sandbox","paris"};


// 経路
typedef struct {
    int path[N];
    int len;
} Path;

// 現在地点を求める
int top(Path *p)
{
    return p->path[p->len - 1];
}

// 経路に頂点が含まれているか
bool visited(Path *p, int x)
{
    for (int i = 0; i < p->len; i++) {
        if (p->path[i] == x) return true;
    }
    return false;
}

// 経路の表示
void print_path(Path *p, int start)
{
    for (int i = 0; i < p->len; i++){
        printf("%d ",  start+p->path[i] - 1);
    }
    printf("\n");
}

// キュー
#define Q 64

Path buff[Q];
int  front, rear;

// 初期化
void init_queue(int start){
    buff[0].path[0] = start;
    buff[0].len = 1;
    rear = 1;
}

// データの取り出し
Path *deq(void){
    return &buff[front++];
}

// データの追加
void enq(Path *p, int x){
    buff[rear] = *p;
    buff[rear].path[p->len] = x;
    buff[rear++].len++;
}

// キューは空か
bool is_empty(void){
    return front == rear;
}

// 幅優先探索
void bfs(int start, int goal){
    printf("start=%d, goal=%d\n",start,goal);
    init_queue(start);
    printf("front=%d, rear=%d\n",front,rear);
    while (!is_empty()) {
        Path *p = deq();
        int x = top(p);
        printf("x=%d, p.path=%d,p.len=%d\n",x,p->path[N],p->len);
        if (x == goal) {
            print_path(p,start);
        }
        else {
            for (int i = 0; i < M; i++) {
                int y = adjacent[x][i];
                if (y == 0) break;
                if (!visited(p, y)) enq(p, y);
            }
        }
    }
}

//char型からint型に変換
int kazu(char a[]){
    int i,n=0;
    for(i=0;i<8;i++){
        if(strcmp(a,*(p+i))==0){
            printf("%s, %s",a,*(p+i));
            n=i;
            printf("%d  ",i);
            break;
        }
    }
    return n;
}

//startとfinish入力
int nyuuryoku_start(){
    char s[100];
    printf("何から何に行きたいですか？\nstart=");
    scanf("%s",s);
    int n=kazu(s);
    return n;
    
}

int nyuuryoku_finish(){
    char f[100];
    printf("finish=");
    scanf("%s",f);
    int m=kazu(f);
    return m;
}

int main(void)
{
    int start, goal;
    
    start=nyuuryoku_start();
    goal=nyuuryoku_finish();
    
    bfs(start, goal);
    return 0;
}
