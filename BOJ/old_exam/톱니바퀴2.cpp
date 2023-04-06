#include <iostream>
#include <vector>

using namespace std;

char arr[4][8];
vector<pair<int,int>> inst;

void move(int number){
    char temp = arr[number-1][7];
    for(int i=7; 0<i; i--) arr[number-1][i] = arr[number-1][i-1];
    arr[number-1][0] = temp;
}

void back_move(int number){
    char temp = arr[number-1][0];
    for(int i=0; i<7; i++) arr[number-1][i] = arr[number-1][i+1];
    arr[number-1][7] = temp;
}

void f(int number, int rotate){
    
    bool find12 = 0, find23 = 0, find34 = 0;
    if(arr[0][2] != arr[1][6]) find12 = 1;
    if(arr[1][2] != arr[2][6]) find23 = 1;
    if(arr[2][2] != arr[3][6]) find34 = 1;
    
    if(rotate == 1) {
        
        if(number == 1){
            move(1);
            if(find12) {
                back_move(2);
                if(find23) {
                    move(3);
                    if(find34) {
                        back_move(4);
                    }
                }
            }
        }
        if(number == 2){
            move(2);
            if(find12) {
                back_move(1);
            }
            if(find23){
                back_move(3);
                if(find34) {
                    move(4);
                }
            }
        }
        if(number == 3){
            move(3);
            if(find23) {
                back_move(2);
                if(find12) {
                    move(1);
                    
                }
            }
            if(find34) {
                back_move(4);
            }
        }
        if(number == 4){
            move(4);
            if(find34) {
                back_move(3);
                if(find23) {
                    move(2);
                    if(find12) {
                        back_move(1);
                    }
                }
            }
        }
        
    }
    
    if(rotate == -1){
        
        if(number == 1){
            back_move(1);
            if(find12) {
                move(2);
                if(find23) {
                    back_move(3);
                    if(find34) {
                        move(4);
                    }
                }
            }
        }
        if(number == 2){
            back_move(2);
            if(find12) {
                move(1);
            }
            if(find23){
                move(3);
                if(find34) {
                    back_move(4);
                }
            }
        }
        if(number == 3){
            back_move(3);
            if(find23) {
                move(2);
                if(find12) {
                    back_move(1);
                    
                }
            }
            if(find34) {
                move(4);
            }
        }
        if(number == 4){
            back_move(4);
            if(find34) {
                move(3);
                if(find23) {
                    back_move(2);
                    if(find12) {
                        move(1);
                    }
                }
            }
        }
        
    }
    
}

int main() {

    for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){ // 12시 방향부터 시계방향, n극 0, s극 1
            cin >> arr[i][j];
        }
    }
    
    int k; cin >> k;
    
    for(int i=0; i<k; i++){
        int a, b; cin >> a >> b;
        inst.push_back({a,b}); // a:톱니 번호, b:방향 1시계 -1반시계
    }
    
    for(int i=0; i<k; i++) f(inst[i].first, inst[i].second);
    
    int sum = 0;
    if(arr[0][0]=='1') sum += 1;
    if(arr[1][0]=='1') sum += 2;
    if(arr[2][0]=='1') sum += 4;
    if(arr[3][0]=='1') sum += 8;
    
    cout << sum << '\n';
}
