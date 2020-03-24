#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    ifstream file(argv[1]);

    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return 1;
    }

    string line;
    getline(file, line);

    int n = stoi(line);

    vector<vector<int> > w(n , vector<int> (n));
    for (int i = 0; i < w.size(); ++i) {
        for (int j = 0; j < w[i].size(); ++j) {
            w[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < n; ++i) {
        getline(file, line);
        istringstream iss(line);

        while (true) {
            int vertex, cost;

            iss >> vertex >> cost;

            if (iss.eof())
                break;

            w[i][vertex - 1] = cost;
        }
    }
    getline(file, line);
    int start = stoi(line) - 1;
    getline(file, line);
    int destination = stoi(line) - 1;

    bool visited[n];
    int min_distance_to[n];

    for (int i = 0; i < n; i++)
    {
        min_distance_to[i] = w[start][i];
        visited[i] = false;
    }
    min_distance_to[start] = 0;
    int min_cost_vertex = 0, next = 0;
    for (int i = 0; i < n; i++)
    {
        int min=INT_MAX;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && min_distance_to[j] < min)
            {
                min = min_distance_to[j];
                min_cost_vertex = j;
            }
        }
        next = min_cost_vertex;
        visited[next] = true;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j]
                && w[next][j] != INT_MAX
                && min_distance_to[next] != INT_MAX
                && (min_distance_to[next] + w[next][j] < min_distance_to[j]))
            {
                min_distance_to[j] = min_distance_to[next] + w[next][j];
            }
        }
    }

    if (min_distance_to[destination] == INT_MAX) {
        cout << "N" << endl;
        return 0;
    } else {
        cout << "Y" << endl;
    }


    // Path recovery
    int current = destination;
    int path[n];
    path[0] = current + 1;
    int step = 1;
    int weight = min_distance_to[current];

    while (current != start)
    {
        for (int i = 0; i < n; i++)
        {
            if (w[i][current] != INT_MAX)
            {
                int distance = weight - w[i][current];
                if (distance == min_distance_to[i])
                {
                    weight = distance;
                    current = i;
                    path[step] = i + 1;
                    step++;
                }
            }
        }
    }

    for (int i = step - 1; i >= 0; i--)
        cout << path[i] << " ";

    cout << endl << min_distance_to[destination] << endl;

    return 0;
}
