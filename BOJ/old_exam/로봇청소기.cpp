#include <iostream>
#include <queue>

using namespace std;

int n,m;
int r,c,d;
int arr[50][50]; // 0 빈칸 1 벽 2 주어지지않은 맵
int visit[50][50]; // 0 청소안함 1 청소함

int dx[]={-1,0,1,0}; // 북동남서
int dy[]={0,1,0,-1};

void move(){
    
    queue<pair<int,int>> q;
    q.push({r,c});
    
    while(!q.empty()){
        
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        if(visit[x][y]==0) visit[x][y] = 1; // 청소안한곳인 경우 청소해주자
        
        bool find = 0; // 2,3 case 가르기
        
        for(int i=0; i<4; i++){  // 4방향을 돌면서
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if(arr[nx][ny]>0) continue;  // 맵을 벗어난, 벽인 경우 무시
            
            if(visit[nx][ny]==0&&arr[nx][ny]==0) find = 1; // 3번 case, 다 청소가 된 경우
        }
            
        if(find) { // 3번 case, 청소가 안된 빈칸이 있는경우
            d--;
            if(d==-1) d=3;
            int a = x + dx[d];
            int b = y + dy[d];
            if(visit[a][b]==0&&arr[a][b]==0){
                q.push({a,b});
            }
            else{
                q.push({x,y});
                
            }
        }
        
        else{ // 2번
            
            int back_d = d-2; // 후진
            if(back_d==-1) back_d=3;
            if(back_d==-2) back_d=2;
                
            int a = x + dx[back_d]; // 후진으로 움직인 칸 좌표 a,b
            int b = y + dy[back_d];
                
            if(arr[a][b]==0){// 방향유지한채로 한 칸 후진할 수 잇는 경우
                q.push({a,b});
            }
        }
    }
}

int main() {
    cin >> n >> m;
    cin >> r >> c >> d;
    for(int i=0; i<50; i++){ // 초기설정
        for(int j=0; j<50; j++){
            arr[i][j] = 2;
            visit[i][j] = 0;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> arr[i][j];
        }
    }
    
    move();

    int sum = 0;
    
    for(int i=0; i<50; i++){
        for(int j=0; j<50; j++){
            sum += visit[i][j];
        }
    }
    
    cout << sum << '\n';
}
