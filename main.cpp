#include <iostream>
#include <vector>
#include "cmath"
#include <map>

using namespace std;

// 1)
void SetData(int &n, double &a, double &b){
    cout << "Podaj n ";
    cin >> n;

    cout << "Podaj a ";
    cin >> a;

    cout << "Podaj b ";
    cin >> b;
};

void SetNodes(vector<double> &nodesArr, int n, int a, int b){
    // equal distance
    double h = (b - a) / double(n);
    for (int i = 0; i <= n; i++){
        nodesArr.push_back(a + i * h);
    }
    // TODO: optimal distance
}


double InterpolationFunction(double x){
    return abs(cos(x) * x);
}

void fillNodesMap(std::map<double, double> &nodesMap, vector<double> nodesArr, int n){
    for(int i =0; i < n; i++)
        nodesMap[nodesArr[i]] = InterpolationFunction(nodesArr[i]);
}

double Lagrange(double pointX, std::map<double, double> &nodesMap){
    double result = 0;
    for(auto i : nodesMap){
        double jResult = 1;
        for(auto j : nodesMap){
            if(i.first != j.first){
                jResult *= (pointX - j.first) / (i.first- j.first);
            }
        }
        result += jResult * i.second;
    }
    return result;
}

void SetTargetPoints(vector<double> &targetPointsArr, int np, int a, int b) {
    double hp = (b - a) / np;
    for (int j = 0; j <= np; j++) {
        targetPointsArr.push_back(a + j * hp);
    }
}

void calculateLagrangeOnTargetPoints(std::map<double, double> &targetPointsInterpolationMap, vector<double> targetPointsArr, int np){
    for(int i =0; i < np; i++)
        targetPointsInterpolationMap[targetPointsArr[i]] = InterpolationFunction(targetPointsArr[i]);
}

    int main() {
        int n;
        double a, b;
        int np = 150;

        std::map<double, double> nodesMap;
        SetData(n, a, b);

        vector<double> nodesArr;
        SetNodes(nodesArr, n, a, b);

        fillNodesMap(nodesMap, nodesArr, n);

        vector<double> targetPointsArr;
        SetTargetPoints(targetPointsArr, np, a, b);

        std::map<double, double> targetPointsInterpolationMap;
        calculateLagrangeOnTargetPoints(targetPointsInterpolationMap, targetPointsArr, np);


        for (int i = 0; i < n + 1; i++)
            cout << nodesArr[i] << endl;

        return 0;
    }