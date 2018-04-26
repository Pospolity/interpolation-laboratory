#include <iostream>
#include <vector>
#include "cmath"
#include <map>
#include <fstream>

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
    double hp = (b - a) / (double)np;
    for (int j = 0; j <= np; j++) {
        targetPointsArr.push_back(a + j * hp);
    }
}

void calculateInterpolationOnTargetPoints(std::map<double, double> &targetPointsInterpolationMap, vector<double> &targetPointsArr, int np){
    for(int i =0; i < np; i++)
        targetPointsInterpolationMap[targetPointsArr[i]] = InterpolationFunction(targetPointsArr[i]);
}

void calculateLagrangeOnTargetPoints(std::map<double, double> &targetPointsLagrangeMap, vector<double> &targetPointsArr, int np, std::map<double, double> &nodesMap){
    for(int i =0; i < np; i++)
        targetPointsLagrangeMap[targetPointsArr[i]] = Lagrange(targetPointsArr[i], nodesMap);
}

    int main() {
        int n;
        double a, b;
        int np = 150;

        SetData(n, a, b);

        vector<double> nodesArr;
        SetNodes(nodesArr, n, a, b);

        std::map<double, double> nodesMap;
        fillNodesMap(nodesMap, nodesArr, n);

        vector<double> targetPointsArr;
        SetTargetPoints(targetPointsArr, np, a, b);

        std::map<double, double> targetPointsInterpolationMap;
        calculateInterpolationOnTargetPoints(targetPointsInterpolationMap, targetPointsArr, np);

        std::map<double, double> targetPointsLagrangeMap;
        calculateLagrangeOnTargetPoints(targetPointsLagrangeMap, targetPointsArr, np, nodesMap);

        cout << "x:" << endl;
        for (int i = 0; i <= n ; i++)
            cout << nodesArr[i] << "    ";

        cout << endl;

        cout << "f(x):" << endl;
        for (int i = 0; i <= n ; i++)
            cout << nodesMap[nodesArr[i]] << "    ";

        cout << endl;

        cout << "xpj:" << endl;
        for (int i = 0; i <= np; i++)
            cout << targetPointsArr[i] << "  ";

        cout << endl;

        cout << "f(xpj):" << endl;
        for (int i = 0; i <= np; i++)
            cout << targetPointsInterpolationMap[targetPointsArr[i]] << "  ";

        cout << endl;

        cout << "Ln(xpj):" << endl;
        for (int i = 0; i <= np; i++)
            cout << targetPointsLagrangeMap[targetPointsArr[i]] << "   ";




        // save to file

        ofstream toFile;
        toFile.open("data.csv");

        toFile << "x:" << endl;
        for (int i = 0; i <= n ; i++)
            toFile << nodesArr[i] << ";";

        toFile << endl;

        toFile << "f(x):" << endl;
        for (int i = 0; i <= n ; i++)
            toFile << nodesMap[nodesArr[i]] << ";";

        toFile << endl;

        toFile << "xpj:" << endl;
        for (int i = 0; i <= np; i++)
            toFile << targetPointsArr[i] << ";";

        toFile << endl;

        toFile << "f(xpj):" << endl;
        for (int i = 0; i <= np; i++)
            toFile << targetPointsInterpolationMap[targetPointsArr[i]] << ";";

        toFile << endl;

        toFile << "Ln(xpj):" << endl;
        for (int i = 0; i <= np; i++)
            toFile << targetPointsLagrangeMap[targetPointsArr[i]] << ";";

        toFile.close();

        return 0;
    }