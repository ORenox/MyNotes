#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>


using namespace std;

// ¿Qué hace using namespace std;?

// Normalmente, vector, cout, cin, endl, etc. pertenecen al namespace std:

// en proyectos grandes suele recomendarse no hacer esto porque puedes generar conflictos de nombres.

// Una alternativa muy buena es importar solamente lo que necesitas:
//using std::vector;
// using std::cout;
// using std::endl;

int CutRod( const  vector<int>& p , int n){

        if (n == 0){
            return 0;
        }

        int q = INT_MIN;

        for( int i = 1 ; i<=n ; i++ ){
            q = max(q , p[i] + CutRod(p, n - i));
        }

        return q;
    };

int main(){

    vector<int> p = {
    0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30,
    32, 35, 39, 42, 45, 49, 52, 55, 59, 62,
    65, 69, 72, 75, 79, 82, 85, 89, 92, 95,
    99, 102, 105, 109, 112, 115, 119, 122, 125, 129,
    132, 135, 139, 142, 145, 149, 152, 155, 159, 162,
    165, 169, 172, 175, 179, 182, 185, 189, 192, 195,
    199, 202, 205, 209, 212, 215, 219, 222, 225, 229,
    232, 235, 239, 242, 245, 249, 252, 255, 259, 262,
    265, 269, 272, 275, 279, 282, 285, 289, 292, 295,
    299, 302, 305, 309, 312, 315, 319, 322, 325, 329
    };

    int rod = 40;

    cout<<"El precio es: " << CutRod(p,rod)<<endl;

    return 0;
}