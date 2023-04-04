#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> v;
int b,c;
vector<int> answer;

int main(void) {
    cin >> n;
    for(int i=0; i<n; i++){
        int x; cin >> x;
        v.push_back(x);
    }
    cin >> b >> c;
    
    while(!v.empty()){
        
        int cnt=0, val=0;
        int p = v.back();
        
        v.pop_back();
        
        if(p<=b) cnt ++;
        else {
            cnt++;
            int temp = p-b;
            val = temp / c;
            if(temp%c>0) val++;
        }
        
        answer.push_back(cnt+val);
        
    }
    
    int final = 0;
    for(int i=0; i<answer.size(); i++){
        final += answer[i];
    }
    cout << final;
}
