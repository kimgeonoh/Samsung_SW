#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define NM 25
priority_queue<int> map[NM][NM];
struct P {
    int x, y, d, atk;
    int gun, score;
    bool operator<(const P &ot) const {
        if (atk + gun != ot.atk + ot.gun) return atk + gun < ot.atk + ot.gun;
        return atk < ot.atk;
    }
    int operator-(const P &ot) {
        return atk + gun - ot.atk - ot.gun;
    }
} fighters[35];
int N, M, K;
void input() {
    // Input
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int x;
            cin >> x;
            map[i][j].push(x);
        }
    }
    for (int i = 1; i <= M; i++) {
        cin >> fighters[i].x >> fighters[i].y >> fighters[i].d >> fighters[i].atk;
    }
}
int dir[4][2] = {{-1, 0},
                 {0,  1},
                 {1,  0},
                 {0,  -1}};
void move(int i) {
    // i 번 사람이 규칙에 맞게 이동함
    int d = fighters[i].d;
    int nx = fighters[i].x + dir[d][0], ny = fighters[i].y + dir[d][1];
    if (nx < 1 || ny < 1 || nx > N || ny > N) {
        d ^= 2;
        fighters[i].d ^= 2;
        nx = fighters[i].x + dir[d][0], ny = fighters[i].y + dir[d][1];
    }
    fighters[i].x = nx, fighters[i].y = ny;
}
int conflict(int x, int y, int i) {
    // 현재 (x, y)에 있는 사람
    for (int j = 1; j <= M; j++) {
        if (i == j) continue;
        if (x == fighters[j].x &&
            y == fighters[j].y) {
            return j;
        }
    }
    return 0;
}
void pick_gun(int i) {
    // i 번 사람이 현재 위치에서 총을 주움
    int x = fighters[i].x, y = fighters[i].y;
    if (map[x][y].empty()) {
        fighters[i].gun = 0;
    } else {
        fighters[i].gun = map[x][y].top();
        map[x][y].pop();
    }
}
void drop_gun(int i) {
    // i 번 사람이 현재 위치에 총을 내려놓음
    int x = fighters[i].x, y = fighters[i].y;
    map[x][y].push(fighters[i].gun);
    fighters[i].gun = 0;
}
void loser(int i) {
    // 패배자에 대한 처리
    // 1. 총 떨구기
    drop_gun(i);
    // 2. 네 방향을 시계 방향으로 돌면서 갈 곳을 찾음
    int d = fighters[i].d;
    int nx = fighters[i].x + dir[d][0], ny = fighters[i].y + dir[d][1];
    while (nx < 1 || ny < 1 || nx > N || ny > N || conflict(nx, ny, i) != 0) {
        d = (d + 1) % 4;
        nx = fighters[i].x + dir[d][0], ny = fighters[i].y + dir[d][1];
    }
    fighters[i].d = d;
    fighters[i].x = nx, fighters[i].y = ny;
    // 3.
    pick_gun(i);
}
void winner(int i) {
    // 승리자에 대한 처리
    drop_gun(i);
    pick_gun(i);
}
void fight(int i, int j) {
    // i번 사람이랑 j번 사람이 싸움!
    if (fighters[i] < fighters[j]) {  // j 번 승리
        fighters[j].score += fighters[j] - fighters[i];
        loser(i);
        winner(j);
    } else {
        fighters[i].score += fighters[i] - fighters[j];
        loser(j);
        winner(i);
    }
}
void pro() {
    while (K--) {
        for (int i = 1; i <= M; i++) {
            move(i);
            int j = conflict(fighters[i].x, fighters[i].y, i);
            if (j != 0) { // 만약 싸움이 일어났다면
                fight(i, j);
            } else {  // 싸움이 일어나지 않았다면,
                drop_gun(i);
                pick_gun(i);
            }
        }
    }
    for (int i = 1; i <= M; i++) {
        cout << fighters[i].score << " ";
    }
}
int main() {
    input();
    pro();
    return 0;
}
