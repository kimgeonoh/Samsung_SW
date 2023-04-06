#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n,m,k;
int arr[21][21], visit[21][21]; // map, 중복방지 방문처리
int dice[6]={2,1,5,6,4,3}; // 위아래, 왼오, index 3 주사위 아랫면
int d=0; // 동쪽 초기세팅, dx dy에 따라 동남서북 으로 움직인다
int sum;
vector<pair<int,int>> location; // dice의 좌표를 나타낸다

int dx[]={0,1,0,-1}; // 동남서북
int dy[]={1,0,-1,0};

int bfs(int r, int c){
    int cnt = 1;
    queue<pair<int,int>> q;
    q.push({r,c});
    
    while(!q.empty()){
        int nowx = q.front().first;
        int nowy = q.front().second;
        visit[nowx][nowy] = 1;
        q.pop();
        
        for(int i=0; i<4; i++){
            int nx = nowx + dx[i];
            int ny = nowy + dy[i];
            
            if(nx<1||n<nx||ny<1||m<ny) continue;
            if(arr[nx][ny]==arr[nowx][nowy]&&visit[nx][ny]==0) {
                q.push({nx,ny});
                cnt++;
                visit[nx][ny] = 1;
                // 디버깅 cout << "trace " << nx << ' ' << ny << '\n';
            }
            
        }
        
    }
    return cnt;
}

void score(int a, int b){
    int B = arr[a][b];
    int C = bfs(a,b);
    sum += B*C;
}

void rotate(char inst){     // d 바꾸기
    if(inst=='b'){ // 180도 
        d -= 2;
        if(d==-1) d=3;
        if(d==-2) d=2;
    } 
    if(inst=='c'){  // 90도 시계
        d++;
        if(d==4) d=0;
    }
    if(inst=='d') { // 90도 반시계
        d--;
        if(d==-1) d=3;
    }
}

void dice_rotate(int inst){   // dice 행렬 바꾸기
    if(inst==0){
        int temp = dice[5];
        dice[5] = dice[1];
        dice[1] = dice[4];
        dice[4] = dice[3];
        dice[3] = temp;
    }
    if(inst==1){
        int temp = dice[3];
        dice[3] = dice[2];
        dice[2] = dice[1];
        dice[1] = dice[0];
        dice[0] = temp;
    }
    if(inst==2){
        int temp = dice[4];
        dice[4] = dice[1];
        dice[1] = dice[5];
        dice[5] = dice[3];
        dice[3] = temp;
    }
    if(inst==3){
        int temp = dice[0];
        dice[0] = dice[1];
        dice[1] = dice[2];
        dice[2] = dice[3];
        dice[3] = temp;
    }
}

void f(int x, int y){
    
    location.pop_back();
    int nx = x + dx[d];
    int ny = y + dy[d];
    
    if(nx<1||n<nx||ny<1||m<ny){ // 1단계 반대
        rotate('b');
        nx = x + dx[d]; // 이동 방향 반대
        ny = y + dy[d];
        location.push_back({nx,ny});
        dice_rotate(d);
    }
    else{
        location.push_back({nx,ny}); // 1단계
        dice_rotate(d);
    }
    score(nx,ny); // 2단계
    
    int A = dice[3];  // 3단계
    int B = arr[nx][ny];
    if(A>B) rotate('c');
    if(A<B) rotate('d');
}

int main() {
    // f 함수를 여러번 반복하면서 진행된다. 각 동작은 모듈화 하였다

    cin >> n >> m >> k;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cin >> arr[i][j];
        }
    }
    
    location.push_back({1,1});
    
    for(int i=0; i<k; i++) {
        f(location[0].first,location[0].second);
        for(int k=0; k<21; k++){
            for(int j=0; j<21; j++){
                visit[k][j]=0;
            }
        }
        // 디버깅 cout << "location " << location[0].first << ' ' << location[0].second << '\n';
    }
    
    cout << sum << '\n';
    
    /* 디버깅 cout << d << '\n';
    for(int i=0; i<6; i++) cout << dice[i] << ' ';*/
}
