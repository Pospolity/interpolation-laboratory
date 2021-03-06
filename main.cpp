#include <iostream>
#include <vector>
#include "cmath"
#include <map>
#include <fstream>

using namespace std;

// 1)
void SetData(int &n, double &a, double &b){
    //cout << "Podaj n ";
    //cin >> n;

    cout << "Podaj a ";
    cin >> a;

    cout << "Podaj b ";
    cin >> b;
};

enum nodesDistanceStrategy {EQUAL = 1, OPTIMAL = 2};

void SetNodes(vector<double> &nodesArr, int n, int a, int b, nodesDistanceStrategy distance){
    switch(distance){
        case EQUAL: {
            double h = (b - a) / double(n);
            for (int i = 0; i <= n; i++){
                nodesArr.push_back(a + i * h);
            }
            break;
        }
        case OPTIMAL: {
            double firstPart = 0.5 * (a + b);
            double secondPart = 0.5 * (b - a);
            auto cosFunc = [n](auto i )->auto { return cos((2.0 * i + 1.0)/(2.0 * n + 2.0) * M_PI); };
            for(int i =0; i <= n; i++){
                nodesArr.push_back(firstPart + secondPart*cosFunc(i));
            }
            break;
        }

    }
}


double InterpolationFunction(double x){
    return abs(cos(x) * x);
}

void fillNodesMap(std::map<double, double> &nodesMap, vector<double> nodesArr, int n){
    for(int i =0; i <= n; i++)
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
    for(int i =0; i <= np; i++)
        targetPointsInterpolationMap[targetPointsArr[i]] = InterpolationFunction(targetPointsArr[i]);
}

void calculateLagrangeOnTargetPoints(std::map<double, double> &targetPointsLagrangeMap, vector<double> &targetPointsArr, int np, std::map<double, double> &nodesMap){
    for(int i =0; i <= np; i++)
        targetPointsLagrangeMap[targetPointsArr[i]] = Lagrange(targetPointsArr[i], nodesMap);
}

    int main() {
        int n;
        double a, b;
        int np = 150;

        SetData(n, a, b);

        int nArr[] = {7, 8, 15, 18};

        ofstream toFile;
        toFile.open("data.csv");

        for (int i = 0; i < 4; i++) {
            n = nArr[i];

            vector<double> nodesArr;
            SetNodes(nodesArr, n, a, b, OPTIMAL);

            std::map<double, double> nodesMap;
            fillNodesMap(nodesMap, nodesArr, n);

            vector<double> targetPointsArr;
            SetTargetPoints(targetPointsArr, np, a, b);

            std::map<double, double> targetPointsInterpolationMap;
            calculateInterpolationOnTargetPoints(targetPointsInterpolationMap, targetPointsArr, np);

            std::map<double, double> targetPointsLagrangeMap;
            calculateLagrangeOnTargetPoints(targetPointsLagrangeMap, targetPointsArr, np, nodesMap);

            cout << "x:" << endl;
            for (int i = 0; i <= n; i++)
                cout << nodesArr[i] << "    ";

            cout << endl;

            cout << "f(x):" << endl;
            for (int i = 0; i <= n; i++)
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
            toFile << "n = " << n << ":" << endl;

            toFile << "x;";
            for (int i = 0; i <= n; i++)
                toFile << nodesArr[i] << ";";

            toFile << endl;

            toFile << "f(x);";
            for (int i = 0; i <= n; i++)
                toFile << nodesMap[nodesArr[i]] << ";";

            toFile << endl;

            toFile << "xpj;";
            for (int i = 0; i <= np; i++)
                toFile << targetPointsArr[i] << ";";

            toFile << endl;

            toFile << "f(xpj);";
            for (int i = 0; i <= np; i++)
                toFile << targetPointsInterpolationMap[targetPointsArr[i]] << ";";

            toFile << endl;

            toFile << "Ln(xpj);";
            for (int i = 0; i <= np; i++)
                toFile << targetPointsLagrangeMap[targetPointsArr[i]] << ";";

            toFile << endl << endl;
        }
        toFile.close();

        return 0;
    }