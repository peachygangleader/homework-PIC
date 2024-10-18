#include <iostream>
#include <functional>
#include <cmath>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

double func(double x) {
    return sin(x);
}

double rectangles(double a, double b, int n, function<double(double)> f){
    double h = (b - a) / n;
    double sum = 0;
    for (size_t i = 0; i<n; i++){
        double x_i = a + i * h;
        sum += f(x_i);   
    }
    return sum * h;
}

double trapec(double a, double b, int n, function<double(double)> f){
    double h = (b - a) / n;
    double sum = 0;
    for (size_t i = 0; i<n-1; i++){
        double x_i = a + i * h;
        double x_i1 = a + (i+1) * h;
        sum += f(x_i) + f(x_i1);   
    }
    return sum * h/2;
}

double monte_carlo(double a, double b, int n, function<double(double)> f){
    double h = (b - a) / n;
    random_device rd;
    uniform_real_distribution<double>myinterval(a, b);
    double sum = 0;
    for (size_t i = 0; i<n-1; i++){
        double x_i = myinterval(rd);
        sum += f(x_i);   
    }
    return sum * h;
}

int main() {

    double a = 0;
    double b = M_PI;
    int n = 10;
    
    chrono::steady_clock::time_point begin;
    chrono::steady_clock::time_point end;
    
    string filename="file.txt";
    ofstream fp;
    fp.open(filename,fstream::out);
    fp << "n,t_pr,t_tr,t_mc,eps_pr,eps_tr,eps_mc" << endl;
    double t1, t2, t3;
    double real_res = 2.0;
    
    for (size_t  n = 10; n <= 10000; n = n + 10) {
        begin = chrono::steady_clock::now();
        double res1 = rectangles(a, b, n, func);
        end = std::chrono::steady_clock::now();
        t1 = chrono::duration_cast<chrono::microseconds>(end - begin).count();
        
        begin = chrono::steady_clock::now();
        double res2 = trapec(a, b, n, func);
        end = std::chrono::steady_clock::now();
        t2 = chrono::duration_cast<chrono::microseconds>(end - begin).count();
    
        begin = chrono::steady_clock::now();
        double res3 = monte_carlo(a, b, n, func);
        end = std::chrono::steady_clock::now();
        t3 = chrono::duration_cast<chrono::microseconds>(end - begin).count();

        fp << n << "," << t1 << "," << t2 << "," << t3 << "," << fabs(res1 - real_res) << "," << fabs(res2 - real_res) << "," << fabs(res3 - real_res) << endl;

    }
    fp.close();
    
    /*begin = chrono::steady_clock::now();
    double res1 = rectangles(a, b, n, func);
    end = std::chrono::steady_clock::now();
    
    cout << "Прямоугольники: " << res1 << endl;
    cout<<"Время: "<< chrono::duration_cast<chrono::microseconds>(end - begin).count() << " [µs]" <<endl;
    
    begin = chrono::steady_clock::now();
    double res2 = trapec(a, b, n, func);
    end = std::chrono::steady_clock::now();
    
    cout << "Трапеции: " << res2 << endl;
    cout<<"Время: "<< chrono::duration_cast<chrono::microseconds>(end - begin).count() << " [µs]" <<endl; 

    begin = chrono::steady_clock::now();
    double res3 = monte_carlo(a, b, n, func);
    end = std::chrono::steady_clock::now();
    
    cout << "Монте-Карло: " << res3 << endl;
    cout<<"Время: "<< chrono::duration_cast<chrono::microseconds>(end - begin).count() << " [µs]" <<endl; */
    
    return 0;
}