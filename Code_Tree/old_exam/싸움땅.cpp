#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n,m,k;
vector<int> map[21][21]; // Gun, 0 빈칸, 그외 공격력
int score[30];

int dx[]={-1,0,1,0}; // 북동남서
int dy[]={0,1,0,-1};

class PLAYER{
    public:
    int x,y,d,s,g;
    PLAYER(int x, int y, int d, int s,int g){
        this->x = x;
        this->y = y;
        this->d = d;
        this->s = s;
        this->g = g;
    }
};

vector<PLAYER> players;

void fight(int number){
    // round1
    int nowx = players[number].x;
    int nowy = players[number].y;
    int nowd = players[number].d;
    int nows = players[number].s;
    int nowg = players[number].g;
    
    int nx = nowx + dx[nowd];
    int ny = nowy + dy[nowd];
    if(nx<1||n<nx||ny<1||n<ny){ // 격자 밖인 경우 방향 반대로
        nowd -= 2;
        if(nowd == -1) nowd = 3;
        if(nowd == -2) nowd = 2;
        nx = nowx + dx[nowd];
        ny = nowy + dy[nowd];
    }

    players[number] = PLAYER(nx,ny,nowd,nows,nowg); // 전진
    
    // round2
    bool find = 0;

    int index; // 전진해서 만난 상대방 좌표
    int index_x;
    int index_y;

    for(int i=0; i<m; i++){ // 전진한 곳에 플레이어가 존재하는가 탐색
        if(i == number) continue; // 자기 자신 탐색은 제외
        if(players[number].x==players[i].x && players[number].y==players[i].y){
            // 플레이어가 존재한다면
            find = 1; // find
            index = i;
            index_x = players[i].x;
            index_y = players[i].y;
        }
    }

    if(find){ // 플레이어가 존재한다면
        // winner, loser를 선정한다
        int iam,you;
        iam = players[number].g + players[number].s;
        you = players[index].g + players[number].s;

        char winner,loser;
        if(iam!=you){
            if(iam>you) winner = 'i', loser = 'y';
            if(iam<you) winner = 'y', loser = 'i';
        }
        else{
            if(players[number].s < players[index].s) winner = 'y', loser = 'i';
            if(players[number].s > players[index].s) winner = 'i', loser = 'y';
        }

        // winner, loser에 따라 진행된다
        if(winner = 'i'){
            score[number] += abs(iam-you); // 승리자 점수흭득
            map[nx][ny].push_back(players[index].g); // 패배자의 권총은 격자에 두고
            players[index].g = 0; 
            int na = index_x + dx[players[index].d]; // 원래 방향 1전진
            int nb = index_x + dx[players[index].d];
            find = 0; // find는 격자밖이거나 1전진시 플레이가 잇을때
            if(na<1||n<na||nb<1||n<nb) find = 1 ; // 격자밖으로 나가거나
            for(int i=0; i<m; i++){ // 1전진때 플레이가 잇는 경우
                if(i == index) continue;
                if(na==players[i].x && nb==players[i].y){
                    find = 1;
                }
            }
            if(find){ // 90도를 회전하며 빈칸을 찾아 이동한다
                int d = players[index].d;
                while(find){
                    d ++;
                    if(d==4) d=0;
                    int nr = players[index].x + dx[d];
                    int nc = players[index].y + dy[d];
                    find = 0; // find는 빈칸이 아닌 경우 1
                    for(int i=0; i<m; i++){
                        if(i == index) continue;
                        if(nr==players[i].x||nc==players[i].y) {
                            find = 1; 
                            break;
                        }
                    }
                    if(!find){ // 빈칸을 찾은 경우
                        players[index].x = nr; // 패배자는 이동
                        players[index].y = nc;
                        players[index].d = d;
                    }
                }
            }
            else{
                players[index].x = na;
                players[index].y = nb;
            }
            
            // 승리자는 총을 비교해서 센 무기를 갖는다
            sort(map[nx][ny].begin(),map[nx][ny].end());
            int maxgun = map[nx][ny].back();
            map[nx][ny].pop_back();

            if(maxgun>players[number].g){
                map[nx][ny].push_back(players[number].g);
                players[number].g = maxgun;
            }
        }
        if(winner = 'y'){
            score[index] += abs(iam-you); // 승리자 점수흭득
            map[nx][ny].push_back(players[number].g); // 패배자의 권총은 격자에 두고
            players[number].g = 0; 
            int na = players[number].x + dx[players[number].d]; // 원래 방향 1전진
            int nb = players[number].x + dx[players[number].d];
            find = 0; // find는 격자밖이거나 1전진시 플레이가 잇을때
            if(na<1||n<na||nb<1||n<nb) find = 1 ; // 격자밖으로 나가거나
            for(int i=0; i<m; i++){ // 1전진때 플레이가 잇는 경우
                if(i == number) continue;
                if(na==players[i].x && nb==players[i].y){
                    find = 1;
                }
            }
            if(find){ // 90도를 회전하며 빈칸을 찾아 이동한다
                int d = players[number].d;
                while(find){
                    d ++;
                    if(d==4) d=0;
                    int nr = players[number].x + dx[d];
                    int nc = players[number].y + dy[d];
                    find = 0; // find는 빈칸이 아닌 경우 1
                    for(int i=0; i<m; i++){
                        if(i == number) continue;
                        if(nr==players[i].x||nc==players[i].y) {
                            find = 1;
                            break;
                        }
                    }
                    if(!find){ // 빈칸을 찾은 경우
                        players[number].x = nr; // 패배자는 이동
                        players[number].y = nc;
                        players[number].d = d;
                    }
                }
            }
            else{
                players[number].x = na;
                players[number].y = nb;
            }
            
            // 승리자는 총을 비교해서 센 무기를 갖는다
            sort(map[nx][ny].begin(),map[nx][ny].end());
            int maxgun = map[nx][ny].back();
            map[nx][ny].pop_back();

            if(maxgun>players[index].g){
                map[nx][ny].push_back(players[index].g);
                players[index].g = maxgun;
            }
        }
    }
    else{ // 플레이어가 존재하지 않는다면
        if(map[nx][ny][0]>0){ // 맵에 총이 있다면

            // 먼저 map에 존재하는 여러 총 중 가장 쎈 총을 고른다

            sort(map[nx][ny].begin(),map[nx][ny].end());
            int maxgun = map[nx][ny].back();
            map[nx][ny].pop_back();

            if(players[number].g>0){ // 플레이어가 총이 있을때
                if(maxgun > players[number].g){ // map에 있는 총이 더 쎄면
                    map[nx][ny].push_back(players[number].g);
                    players[number].g = maxgun;
                }    
            }
            else{ // 플레이어가 총이 없을때
                players[number].g = maxgun;
            }
        }
    }
    
}

int main() {
    cin >> n >> m >> k;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            int g; cin >> g;
            map[i][j].push_back(g); // Gun map
        }
    }
    for(int i=0; i<m; i++){
        int x,y,d,s;
        cin >> x >> y >> d >> s;
        players.push_back(PLAYER(x,y,d,s,0)); // players 초기세팅
    }

    for(int i=0; i<k; i++) { // k setp
        for(int j=0; j<m; j++){ // m(j)번째 player
            fight(j);
        }
    }
    for(int i=0; i<m; i++) cout << score[i] << ' ';
}
