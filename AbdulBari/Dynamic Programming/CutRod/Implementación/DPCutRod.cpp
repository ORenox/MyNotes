#include<iostream>
#include<vector>
#include<climits>

#include <utility>

using namespace std;



int Memoized_cutRod_aux( const vector<int>& p, int n, vector<int>& r){
    int q ;
    if(r[n] >= 0){ //Solución previamente calculada
        return r[n];
    }

    if(n == 0 ){ //Caso base, ningún corte
        q=0;
    }else {
        q=INT_MIN;
        
        for( int i = 1; i<=n ; i++){// i is the position of the ûrst cut
            q = max(q, p[i] + Memoized_cutRod_aux(p,n-i,r));
        }
    }

    r[n]=q; //recordar la solución para un valor n

    return q;
}

int Memoized_cutRod( const vector<int>& p, int n){
    vector<int> r(n+1);  //va a guardar las soluciones ya calculadas

    for( int i = 0; i<=n ; i++){
        r[i]=INT_MIN;   //Relleno los espacios del vector con -inf
    }

    return Memoized_cutRod_aux(p,n,r);
}



//--------------------------------------------------

int BottomUp_cut_rod( const vector<int> p, int n){

    vector<int> r(n+1);
    r[0]=0;

    for(int j = 1 ; j<=n ; j++){
        int q = INT_MIN;
        for(int i = 1 ; i<=j; i++){
            q = max(q, p[i] + r[j-i]); //el corte i + su complementario que ya está guardado en r
        }
        r[j]=q;
    }

    return r[n];

}

//--------------------------------------------------------

pair<vector<int>, vector<int>> extended_bottom_up_cutRod( const vector<int>& p, int n){

    vector<int> r(n+1);
    vector<int> s(n+1);

    r[0]=0;

    for( int j = 1 ; j<=n ; j++){
        int q=INT_MIN;

        for( int i = 1; i<=j ; i++){
            if(q< p[i] + r[j-i]){
                q = p[i] + r[j-i];
                s[j] = i;
            }
        }
        r[j]=q;
    }

    return {r,s};
}

void imprimirVector(vector<int>& s ){
    cout << "[";
    for (int i = 0; i < s.size(); i++) {
        cout << s[i];

        if (i < s.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void print_cut_rod_solution(const vector<int>& p, int n){
    auto [r, s] = extended_bottom_up_cutRod(p, n);
    imprimirVector(s);
    while(n>0){
        cout<<s[n]<<" ";
        n = n - s[n];
    }
}

int main() {

    vector<int> p = {
    0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30,
    1, 1, 1, 1, 1, 1, 52, 55, 59, 62,
    1, 1, 1, 1, 1, 1, 1, 9, 2, 95,
    99, 102, 105, 109, 112, 115, 119, 122, 125, 129,
    132, 135, 139, 142, 145, 149, 152, 155, 159, 162,
    165, 169, 172, 175, 179, 182, 185, 189, 192, 195,
    199, 202, 205, 209, 212, 215, 219, 222, 225, 229,
    232, 235, 239, 242, 245, 249, 252, 255, 259, 262,
    265, 269, 272, 275, 279, 282, 285, 289, 292, 295,
    299, 302, 305, 309, 312, 315, 319, 322, 325, 329
    };

    int rod = 25;

    cout<<"El precio es para un rod : "<< rod<< " es : " << BottomUp_cut_rod(p,rod)<<endl;
    cout<<"El precio es para un rod : "<< rod<< " es : " << Memoized_cutRod(p,rod)<<endl;
    print_cut_rod_solution(p,rod);
    return 0;
}
