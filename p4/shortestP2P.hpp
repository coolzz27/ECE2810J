#include <climits>
#include <iostream>
#include <list>
#include <vector>
// You are not allowed to include additional libraries

#define INF INT_MAX

using namespace std;

class ShortestP2P {
public:
    ShortestP2P() {}

    /* Read the dist from stdin
       * The input has the following format:
       *
       * Firstline: 1 unsigned int, the total number of verticies, X.
       * Secondline: 1 unsigned int, the total number of edges between vertices, Y.
       * A set of Y lines, each line contains tuple of 2 unsigned int and 1 int (not unsigned int!), in the format of: A(point 1, unsigned) B(point 2, unsigned) dist(distance, int)
       *
       * Example:
       * 4
       * 4
       * 0 1 5
       * 1 2 -1
       * 2 3 4
       * 3 1 6
       * 
       * 
       * 
       *
       * Vertices that are not connected have a infinitly large distance. You may use INF (previously defined at the top of this cope snippet) for infinitly large distance.
       * 
       * Special: when the dist is not proper, where there exist any pair of vertices whose minimum distance does not exist, terminate immediately by printing:
       * cout << "Invalid dist. Exiting." << endl;
       *
       * Note: vertex pairs that are not connected, which have infinitely large distances are not considered cases where "minimum distances do not exist".
       */
    void readGraph() {
        unsigned int v, e;
        cin >> v >> e;
        dist = vector<vector<int>>(v, vector<int>(v, INF));
        for (unsigned int i = 0; i < e; i++) {
            unsigned int src, dest;
            int weight;
            cin >> src >> dest >> weight;
            dist[src][dest] = weight;
        }
        for (unsigned int i = 0; i < v; i++) {
            dist[i][i] = 0;
        }
        detect_negative_cycle();
    }

    /* Input: 2 vertices A and B
       * Output: distance between them.
       * cout << dist << endl;
       *
       * When the A and B are not connected print INF:
       * cout << "INF" << endl;
       */
    void distance(unsigned int A, unsigned int B) {
        if (dist[A][B] == INF) {
            cout << "INF" << endl;
        } else {
            cout << dist[A][B] << endl;
        }
    }

private:
    // internal data and functions.
    vector<vector<int>> dist;

    void detect_negative_cycle() {
        for (unsigned int k = 0; k < dist.size(); k++) {
            for (unsigned int i = 0; i < dist.size(); i++) {
                for (unsigned int j = 0; j < dist.size(); j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF
                        && dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        // cout << "dist" << i << " " << j << "updated from " << dist[i][j] << " to "
                        //  << dist[i][k] + dist[k][j] << endl;
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
                if (dist[i][i] < 0) {
                    cout << "Invalid graph. Exiting." << endl;
                    exit(0);
                }
            }
        }
    }
};
