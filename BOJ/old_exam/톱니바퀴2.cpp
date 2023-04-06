#include <iostream>
#include <vector>
#include <deque>

using namespace std;

deque<deque<char>> dq(4, deque<char>(8));
int k;
vector<pair<int,int>> inst;
int sum;

void move(int number){
    char temp = dq[number-1].back();
    dq[number-1].pop_back();
    dq[number-1].push_front(temp);
}

void back_move(int number){
    char temp = dq[number-1].front();
    dq[number-1].pop_front();
    dq[number-1].push_back(temp);
}

void f(int number, int rotate){
    
    if(rotate==1) {
        if(number == 1){ // 1
            move(1);
            if(dq[0][2]!=dq[1][6]){ // 1,2
                back_move(2);
                if(dq[1][2]!=dq[2][6]){ // 2,3
                    move(3);
                    if(dq[2][2]!=dq[3][6]){ // 3,4
                        back_move(4);
                    }
                }
            }
        }
        if(number == 2){ // 2
            move(2);
            if(dq[0][2]!=dq[1][6]) back_move(1); // 1,2
            if(dq[1][2]!=dq[2][6]){ // 2,3
                back_move(3);
                if(dq[2][2]!=dq[3][6]){ // 3,4
                    move(4);
                }
            }
        }
        if(number == 3){ // 3
            move(3);
            if(dq[2][2]!=dq[3][6]) back_move(4); // 3,4
            if(dq[2][6]!=dq[1][2]){ // 2,3
                back_move(2);
                if(dq[2][6]!=dq[0][2]){ // 1,2
                    move(1);
                }
            }
        }
        if(number == 4){ // 4
            move(4);
            if(dq[3][6]!=dq[2][2]){ // 3,4
                back_move(3);
                if(dq[2][6]!=dq[1][2]){ // 2,3
                    move(2);
                    if(dq[1][6]!=dq[0][2]){ // 1,2
                        back_move(1);
                    }
                }
            }
        }
    }
    
    if(rotate==-1) {
        if(number == 1){ // 1
            back_move(1);
            if(dq[0][2]!=dq[1][6]){ // 1,2
                move(2);
                if(dq[1][2]!=dq[2][6]){ // 2,3
                    back_move(3);
                    if(dq[2][2]!=dq[3][6]){ // 3,4
                        move(4);
                    }
                }
            }
        }
        if(number == 2){ // 2
            back_move(2);
            if(dq[0][2]!=dq[1][6]) move(1); // 1,2
            if(dq[1][2]!=dq[2][6]){ // 2,3
                move(3);
                if(dq[2][2]!=dq[3][6]){ // 3,4
                    back_move(4);
                }
            }
        }
        if(number == 3){ // 3
            back_move(3);
            if(dq[2][2]!=dq[3][6]) move(4); // 3,4
            if(dq[2][6]!=dq[1][2]){ // 2,3
                move(2);
                if(dq[2][6]!=dq[0][2]){ // 1,2
                    back_move(1);
                }
            }
        }
        if(number == 4){ // 4
            back_move(4);
            if(dq[3][6]!=dq[2][2]){ // 3,4
                move(3);
                if(dq[2][6]!=dq[1][2]){ // 2,3
                    back_move(2);
                    if(dq[1][6]!=dq[0][2]){ // 1,2
                        move(1);
                    }
                }
            }
        }
    }
    
}

int main() {

    for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){ // 12시 방향부터 시계방향으로 n극 0 s극 1
            cin >> dq[i][j];
        }
    }
    
    /*for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){ // 디버깅
            cout << dq[i][j] <<' ';
        }
        cout << '\n';
    }*/
    
    cin >> k;
    
    for(int i=0; i<k; i++){
        int a, b; cin >> a >> b;
        inst.push_back({a,b}); // a는 톱니 번호 1은 시계 -1은 반시계
    }
    
    for(int i=0; i<k; i++) f(inst[i].first, inst[i].second);
    
    if(dq[0][0]=='1') sum += 1;
    if(dq[1][0]=='1') sum += 2;
    if(dq[2][0]=='1') sum += 4;
    if(dq[3][0]=='1') sum += 8;
    
    cout << sum << '\n';
}
