#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double b = 2.0;
double gamma_mg = 1.0;
double n = 8.79;

double der(double x, double x_prev){
    double ret = ((b*x_prev)/(pow(x_prev,n) + 1.0)) - gamma_mg*x;
    return ret;
}

void Mackey_glass(double &x, double x_tm, double d_xtm, double x_tmn, double d_xtmn) {
    int tm = 2;
    double h = 1e-2;
    double k[4];
    double cur = x;
    double prev = x_tm;

    for (int i = 0; i < 4; i++) {
        k[i] = der(cur,prev)*h;
        if(i == 0 || i == 1){
            cur = x + 0.5 * k[i];
            prev = x_tm * 0.5 + x_tmn * 0.5 + d_xtm * 0.005 * 0.25 - d_xtmn * 0.005 * 0.25;
        }
        else if(i == 2) {
            cur = x + k[i];
            prev = x_tmn;
        }
    }
    x += (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
}
int main(){
    //delay 200
    double xs[201];
    double dxs[201];

    for (int i = 0; i < 201; i++) {
        xs[i] = 0.5;
        dxs[i] = 0.0;
    }
    double x = 0.5;
    string filename = "simulation_MackeyGlass.csv";
    ofstream datafile(filename);
    datafile << "Time,x,y\n";
    datafile <<0<<","<<x << "\n";
    double y;
    for (int i = 0; i < 100000; i++){
        Mackey_glass(x,xs[i % 201],dxs[i%201],xs[(i+1)%201],dxs[(i+1)%201]);
        y = xs[i % 201];
        dxs[i%201] = der(x,xs[(i+1)%201]);
        xs[i%201] = x;
        datafile << 0.01*(i+1)<<","<<x <<","<<y<< "\n";
    }
    datafile.close();
    return 0;
}
