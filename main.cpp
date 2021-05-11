#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include<cmath>
#include <vector>
using namespace std;
int convertString(char sequenceDNA){
    int seq;
    if (sequenceDNA == 'G'){
        seq = 1;
    }
    else if (sequenceDNA == 'A'){
        seq = 2;
    }
    else if (sequenceDNA == 'T'){
        seq = 3;
    }
    else{
        seq = 4;
    }
    return seq;
}

double macarena(double one_macarena, double two_macarena, double three_macarena){
    double ayyyyy = 0;
    if(one_macarena >= two_macarena && one_macarena >= three_macarena){
        ayyyyy = one_macarena;
    }
    else if(two_macarena >= one_macarena && two_macarena >= three_macarena){
        ayyyyy = two_macarena;
    }
    else{
        ayyyyy = three_macarena;
    }
    return ayyyyy;
}

struct Score{
    double value;
    //vector{0,0,0}
};

int main(int argc, char *argv[]) {
    //variables
    double temp1 = -1.0;
    double temp2 = -1.0;
    double temp3 = -1.0;
    //define x and y as string
    int xsize = 0;
    int ysize = 0;
    cout << "Enter string x:";
    //AGCATAATACCCCTATACTGT
    string xstr = "";
    cin >> xstr;
    xsize = xstr.size();
    cout << "Enter string y:";
    //GTGCAATCGCTGGCGGCGTAG
    string ystr = "";
    cin >> ystr;
    ysize = ystr.size();
    //initialize arrays that x and y will be stored in as integers
    int xarr[xstr.size()];
    int yarr[ystr.size()];
    //Convert string to int array
    for (int i = 0; i < xstr.size(); i++){
        xarr[i] = convertString(xstr[i]);
    }
    for (int i = 0; i < ystr.size(); i++){
        yarr[i] = convertString(ystr[i]);
    }
    //test for loops
    for(int i = 0; i < xsize;i++){
        cout << xarr[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < ysize;i++){
        cout << yarr[i] << " ";
    }
    cout << endl;
    //create matrix
    int xmatrix = xsize+1;
    int ymatrix = ysize+1;
    double matrix[xmatrix][ymatrix];
    //initialize
    for (int i = 0; i < xmatrix; i++){
        for (int j = 0; j < ymatrix; j++){     
            matrix[i][j] = 0;
        }
    }
    int ix = 0;
    int iy = 0;
    // cout << iy << endl;
    cout << xmatrix << endl;
    cout << ymatrix << endl;
    while(ix < xmatrix){
        //base case
        if(ix == 0){
            if(iy == 0){
                matrix[ix][iy] = 0;
                iy= iy+1;
            }
            else if (ix == 0 && iy < ymatrix){
                double temp = (double)(matrix[ix][iy-1]);
                matrix[ix][iy] = temp - 0.2;
                iy++;
            }
            if(iy == ymatrix){
                ix++;
                iy = 0;
            }
        }
        else{
            if(iy == 0){
                double temp = (double)(matrix[ix-1][iy]);
                matrix[ix][iy] = temp - 0.2;
                iy++;
            }
            else{
                //check if letters match - yes
                if(xarr[ix-1] == yarr[iy-1]){
                    matrix[ix][iy] = matrix[ix-1][iy-1] + 1.0;
                }
                //check if letters match - no
                else{
                    //diagonal
                    double temp1;
                    if(((xarr[ix-1] == 2) &&(yarr[iy-1] == 3)) || ((xarr[ix-1] == 3) &&(yarr[iy-1] == 2)) || ((xarr[ix-1] == 4) &&(yarr[iy-1] == 1)) || ((xarr[ix-1] == 1) &&(yarr[iy-1] == 4))){
                        temp1 = matrix[ix-1][iy-1] - 0.15;
                        if (abs(temp1) < 0.001) temp1 = 0;
                    }
                    else{
                        temp1 = matrix[ix-1][iy-1] - 0.1;
                        if (abs(temp1) < 0.001) temp1 = 0;
                    }
                    //top
                    temp2 = matrix[ix-1][iy] - 0.2;
                    if (abs(temp2) < 0.001) temp2 = 0;
                    //left
                    temp3 = matrix[ix][iy-1] - 0.2;
                    if (abs(temp3) < 0.001) temp3 = 0;
                    matrix[ix][iy] = macarena(temp1, temp2, temp3);
                }
                iy++;
            }
            if(iy == ymatrix){
                ix++;
                iy = 0;
            }
        }
        // else{
        //     ix = xmatrix;
        //     iy = ymatrix;
        //     cout << "exit" << endl;
        // }
    }
    //test matrix
    for (int i = 0; i < xmatrix; i++){
        for (int j = 0; j < ymatrix; j++){  
            cout.precision(4);   
            cout << setw(5) << setfill(' ') << matrix[i][j] << " ";
        }
        cout << endl;
    }

    double sim_score = matrix[xmatrix-1][ymatrix-1];
    cout << "The simailarity score is: " << sim_score << endl;

    return 0;
}
