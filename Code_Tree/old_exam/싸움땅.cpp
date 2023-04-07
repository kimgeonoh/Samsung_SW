#include <iostream>
#include <vector>

using namespace std;

int n,m,k;
vector<int> map[21][21]; // Gun, 0 빈칸, 그외 공격력
int score[30];

int dx[]={-1,0,1,0}; // 북동남서
int dy[]={0,1,0,-1};

class PLAYER{
    public:
    int x,y,d,s;
    PLAYER(int s, int d, int x, int y){
        this->s = s;
        this->d = d;
        this->x = x;
        this->y = y;
    }
    bool operator <(PLAYER &other){
        return this->s < other.s;
    }
};

vector<PLAYER> players;

void fight(int number){
    int nowx = players[number].x;
    int nowy = players[number].y;
    int nowd = players[number].d;
    int nows = players[number].s;
    
    int nx = nowx + dx[nowd];
    int ny = nowy + dy[nowd];
    if(nx<1||n<nx||ny<1||n<ny){ // 격자 밖인 경우 방향 반대로
        nowd -= 2;
        if(nowd == -1) nowd = 3;
        if(nowd == -2) nowd = 2;
        nx = nowx + dx[nowd];
        ny = nowy + dy[nowd];
    }

    players[number] = PLAYER(nows,nowd,nx,ny); // 전진
    
    bool find = 0;

    int index;
    int index_x;
    int index_y;

    for(int i=0; i<m; i++){ // 전진한 곳에 플레이어가 존재하는가 탐색
        if(i == number) continue; // 자기 자신 탐색은 제외
        if(players[number].x==players[i].x && players[number].y==players[i].y){
            // 플레이어가 존재한다면
            find = 1; // find
            index = i;
            index_x = players[number].x;
            index_y = players[number].y;
        }
    }

    if(find){ // 플레이어가 존재한다면
        ㅇ
    }
    else{ // 플레이어가 존재하지 않는다면
        
    }
    
}

int main() {
    cin >> n >> m >> k;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            int g; cin >> g;
            map[i][j].push_back(g); // Gun Map
        }
    }
    for(int i=0; i<m; i++){
        int x,y,d,s;
        cin >> x >> y >> d >> s;
        players.push_back(PLAYER(s,d,x,y));
    }

    for(int i=0; i<k; i++) { // k setp
        for(int j=0; j<m; j++){ // m(j)번째 player
            fight(j);
        }
    }
    for(int i=0; i<m; i++) cout << score[i] << ' ';
}
