//
// Created by Ruslan Sirazhetdinov on 24.03.2020.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct edge {
    int a, b, cost;
};

int main(int argc, char **argv) {
    ifstream file(argv[1]);

    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return 1;
    }

    string line;
    getline(file, line);

    int n = stoi(line);
    vector<edge> e;

    for (int i = 0; i < n; ++i) {
        getline(file, line);
        istringstream iss(line);

        while (true) {
            int vertex, cost;

            iss >> vertex >> cost;

            if (iss.eof())
                break;

            edge new_edge{};
            new_edge.a = i;
            new_edge.b = vertex - 1;
            new_edge.cost = cost;
            e.push_back(new_edge);
        }
    }
    getline(file, line);
    int start = stoi(line) - 1;
    getline(file, line);
    int destination = stoi(line) - 1;

    //Algorithm

    int m = e.size();
    n = e.size();

    const int INF = 1000000000;

    vector<int> d (n, INF);
    d[start] = 0;
    vector<int> p (n, -1);
    for (;;) {
        bool any = false;
        for (int j=0; j<m; ++j)
            if (d[e[j].a] < INF)
                if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                    d[e[j].b] = d[e[j].a] + e[j].cost;
                    p[e[j].b] = e[j].a;
                    any = true;
                }
        if (!any)  break;
    }

    if (d[destination] == INF)
        cout << "N" << endl;
    else {
        vector<int> path;
        for (int cur=destination; cur!=-1; cur=p[cur])
            path.push_back (cur);
        reverse (path.begin(), path.end());

        cout << "Y" << endl;
        for (size_t i=0; i<path.size(); ++i)
            cout << path[i]+1 << " ";
        cout << endl << d[destination] << endl;
    }

    return 0;
}
