#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n;
int arr[20][20];
vector<pair<int,int>> shark_location;
int shark_size = 2;
int shark_feed;
int t;

int dx[]={0,-1,0,1};
int dy[]={1,0,-1,0};

void move(int a,int b){
    // 상어가 크기가 작은 물고기가 있는 곳까지 이동하는 경로를 찾기
    // 경로를 BFS로 찾고 최단 비용을 갖는 경로로 상어를 이동시킨다. 
    // 이동시킬때 shark_location, t 업데이트
    
    int dist=1e9;
    vector<pair<int,pair<int,int>>> v; // dist, x,y로 dist를 통한 sorting
    queue<pair<int,int>> q;
    int visit[20][20];
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){ // 초기 세팅
            visit[i][j]=0;
        }
    }
    q.push({a,b}); 
    
    while(!q.empty()){
        
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        for(int i=0; i<4; i++){
            int nx = x + dx[i]; 
            int ny = y + dy[i];
            
            if(nx<0||n<=nx||ny<0||n<=ny) continue;
            if(shark_size>=arr[nx][ny] && visit[nx][ny]==0) { // 지나갈 수 있는 곳
                q.push({nx,ny});
                visit[nx][ny]=visit[x][y]+1;
                if(shark_size>arr[nx][ny] && arr[nx][ny]>0 ){ // 먹을 수 있다면
                    if(dist>=visit[nx][ny]){  // dist의 최소값만 넣기
                        dist = visit[nx][ny];
                        v.push_back({dist,{x,y}});
                    }
                }
            }
        }
    }
    
    
    if(!v.empty()){
        sort(v.begin(),v.end()); // 가장 최소 dist, 가장 왼쪽
        int minx = v[0].second.first; 
        int miny = v[0].second.second;
        arr[minx][miny]=0;
        shark_feed++;
        if(shark_feed == shark_size){
            shark_feed = 0;
            shark_size++; 
        }
        t += v[0].first;
        shark_location.push_back({minx,miny});
    }
}

int main() {
    
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> arr[i][j];
            if(arr[i][j]==9) {
                shark_location.push_back({i,j});
                arr[i][j]==0;
            }
        }
    }
    
    while(!shark_location.empty()){
        int shx = shark_location[0].first; 
        int shy = shark_location[0].second;
        shark_location.pop_back();
        move(shx,shy);
    }
    
    cout << t << '\n';
    
}
