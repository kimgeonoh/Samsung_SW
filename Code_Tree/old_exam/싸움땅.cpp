#include <iostream>
#include <vector>

using namespace std;

int n,m,k;
int map[21][21]; // Gun, 0 빈칸, 그외 공격력
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
    if(nx<1||n<nx||ny<1||n<ny){ // 격자 밖인 경우
        nowd -= 2;
        if(nowd == -1) nowd = 3;
        if(nowd == -2) nowd = 2;
        nx = nowx + dx[nowd];
        ny = nowy + dy[nowd];
    }

    players[number] = PLAYER(nows,nowd,nx,ny); // 전진

    cout << players[number].x << players[number].y << players[number].d << '\n';

    /*for(int i=0; i<m; i++){
        if()
    }*/
    
}

int main() {
    cin >> n >> m >> k;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin >> map[i][j]; // Gun Map
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
