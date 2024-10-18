#include <iostream>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <fstream>

using namespace std;

double func(double x) {
    return sin(x);
}

double square(double a, double b, function<double(double)> func) {
    double x0 = (a + b) / 2;
    double f0 = func(x0);
    double area0 = (b - a) * f0;
    return area0;
}

double adapt_int(double a, double b, double eps, function<double(double)> func, double area, unordered_map<double, double>* points) {
    double x0 = (a + b) / 2;
    (*points)[x0] = b - a;
    
    double x11 = (a + x0) / 2;
    double f11 = func(x11);
    double area11 = (x0 - a) * f11;
    
    double x12 = (x0 + b) / 2;
    double f12 = func(x12);
    double area12 = (b - x0) * f12;
    
    double area1 = area11 + area12;
    
    if (fabs(area - area1) < eps) {
        return area;
    } 
    else {
        cout << x0 << endl;
        return adapt_int(a, x0, eps / 2, func, area11, points) + adapt_int(x0, b, eps / 2, func, area12, points);
    }
    
}

int main() {
    double a = 0;
    double b = M_PI;
    double eps = 0.01;
    double area = square(a, b, func);

    unordered_map<double, double> data;
    
    double integral = adapt_int(a, b, eps, func, area, &data);
    cout << "result:" << integral << endl;

    string filename="file_points.txt";
    ofstream fp;
    fp.open(filename,fstream::out);
    fp << "x0,segment,value" << endl;
    auto print_key_value = [](const auto& key, const auto& value)
    {
        std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
    };
        std::cout << "Iterate and print key-value pairs of unordered_map, being\n"
                 "explicit with their types:\n";
    
    for (const pair<const double, double>& n : data) {
        print_key_value(n.first, n.second);
        fp << n.first << "," << n.second << "," << func(n.first)<< endl;
    }
    fp.close();

    
  return 0;
}