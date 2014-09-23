#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
 
int n,m;
int path[101][101];
int len[101],ls[101];
int room[101][2];
int ass[101][101];
 
int que[101];
int qf,qe;
void push(int a) {que[qe ++] = a;}
int pop() {return que[qf ++];}
void clear() {qf = qe = 0;}
bool empty() {return (qf >= qe);}
 
bool vis[101];
int tmp[101];
int solve() {
    int i,j,k,t;
 
    if (m == 0) return 0;
 
    memset(ass,0,sizeof(ass));
    memset(vis,0,sizeof(vis));
    memcpy(ls,len,sizeof(len));
    clear();
    for (i=1;i<=n;i++) {
        if (ls[i] == 1) push(i);
    }
 
    while (!empty()) {
        int now = pop();
        vis[now] = true;
 
        t = room[now][0] / 20;
        if (room[now][0] % 20) t ++;
        for (j=m-t;j>=0;j--) ass[now][j+t] = ass[now][j] + room[now][1];
        for (t--;t>=0;t--) ass[now][t] = 0;
 
        for (i=0;i<len[now];i++) {
            int next = path[now][i];
            if (vis[next]) continue;
            ls[next] --;
 
            ass[now][0] = ass[next][0] = 0;
            for (j=0;j<=m;j++) tmp[j] = max(ass[now][j],ass[next][j]);
            for (j=0;j<=m;j++) {
                for (k=0;k<=m;k++) {
                    if (j+k > m) break;
                    tmp[j+k] = max(tmp[j+k],ass[now][j]+ass[next][k]);
                }
            }
            for (j=0;j<=m;j++) ass[next][j] = tmp[j];
 
            if (ls[next] == 1) push(next);
        }
    }
 
    int ret = 0;
    for (i=1;i<=m;i++) ret = max(ret,ass[0][i]);
    return ret;
}
 
int main() {
    int i,j;
    while (scanf("%d %d",&n,&m)==2) {
        if (n==-1 && m==-1) break;
        for (i=1;i<=n;i++) scanf("%d %d",&room[i][0],&room[i][1]);
        for (i=0;i<=n;i++) len[i] = 0;
        for (i=0;i<n-1;i++) {
            int a,b;
            scanf("%d %d",&a,&b);
            path[a][ len[a]++ ] = b;
            path[b][ len[b]++ ] = a;
        }
        path[1][ len[1]++ ] = 0;
        printf("%d\n",solve());
    }
}
