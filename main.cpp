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
    //left, diaganol, top
    double arrows[3];
};

int main(int argc, char *argv[]) {
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
    //create matrix
    int xmatrix = xsize+1;
    int ymatrix = ysize+1;
    Score matrix[xmatrix][ymatrix];
    //initialize
    for (int i = 0; i < xmatrix; i++){
        for (int j = 0; j < ymatrix; j++){     
            matrix[i][j].value = 0;
        }
    }
    int ix = 0;
    int iy = 0;

    while(ix < xmatrix){
        double temp1 = 0;
        double temp2 = 0;
        double temp3 = 0;
        for(int i = 0; i < 3; i++){
            matrix[ix][iy].arrows[i] = -100;
        }
        
        //base case
        if(ix == 0){
            if(iy == 0){
                matrix[ix][iy].value = 0;
                //arrows does not change
            }
            else if (ix == 0 && iy < ymatrix){
                double temp = (double)(matrix[ix][iy-1].value);
                matrix[ix][iy].value = temp - 0.2;
                //left arrow only
                matrix[ix][iy].arrows[0] = temp - 0.2;
            }
        }
        else{
            if(iy == 0){
                double temp = (double)(matrix[ix-1][iy].value);
                matrix[ix][iy].value = temp - 0.2;
                temp2 = temp - 0.2;
            }
            else{
                //check if letters match - yes
                if(xarr[ix-1] == yarr[iy-1]){
                    temp1 = matrix[ix-1][iy-1].value + 1.0;
                    matrix[ix][iy].value = matrix[ix-1][iy-1].value + 1.0;
                }
                //check if letters match - no
                else{
                    //diagonal
                    if(((xarr[ix-1] == 2) &&(yarr[iy-1] == 3)) || ((xarr[ix-1] == 3) &&(yarr[iy-1] == 2)) || ((xarr[ix-1] == 4) &&(yarr[iy-1] == 1)) || ((xarr[ix-1] == 1) &&(yarr[iy-1] == 4))){
                        temp1 = matrix[ix-1][iy-1].value - 0.15;
                        if (abs(temp1) < 0.001) temp1 = 0;
                    }
                    else{
                        temp1 = matrix[ix-1][iy-1].value - 0.1;
                        if (abs(temp1) < 0.001) temp1 = 0;
                    }
                    //top
                    temp2 = matrix[ix-1][iy].value - 0.2;
                    if (abs(temp2) < 0.001) temp2 = 0;
                    //left
                    temp3 = matrix[ix][iy-1].value - 0.2;
                    if (abs(temp3) < 0.001) temp3 = 0;
                    //macarena function gets the largest

                    matrix[ix][iy].value = macarena(temp1, temp2, temp3);
                }
            } 
            if(temp1 != -100){
                matrix[ix][iy].arrows[1] = temp1;
            }
            if(temp2 != -100){
                matrix[ix][iy].arrows[2] = temp2;
            }
            if(temp3 != -100){
                matrix[ix][iy].arrows[0] = temp3;
            }
        }
        iy++;
        if(iy == ymatrix){
                ix++;
                iy = 0;
        }
    }
    //test matrix
    for (int i = 0; i < xmatrix; i++){
        for (int j = 0; j < ymatrix; j++){  
            cout.precision(4);   
            cout << setw(5) << setfill(' ') << matrix[i][j].value << " ";
        }
        cout << endl;
    }
    //backtrack
    ix = xmatrix - 1;
    iy = ymatrix - 1;
    vector<double> alignment;
    while(ix !=0 && iy != 0){
        double max = -100;
        int count = 0;
        for (int k = 0; k < 3; k++){
            if (matrix[ix][iy].arrows[k] > max){
                max = matrix[ix][iy].arrows[k];
                count = k;
            }
        }
        alignment.push_back(max);
        if(count == 0){
            iy--;
        }
        else if(count ==2){
            ix--;
        }
        else{
            iy--;
            ix--;
        }
    }
    alignment.push_back(matrix[0][0].value);
    double sim_score = matrix[xmatrix-1][ymatrix-1].value;
    cout << "The simailarity score is: " << sim_score << endl;
    cout << " One alignment: ";
    for (int i = 0; i < alignment.size(); i++){
        if(i == alignment.size() -1){
            cout << alignment.at(i) << endl;
        }
        cout << alignment.at(i) << ", " ;
    }
    return 0;
}
