#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <math.h>
#include <algorithm>


using namespace std;

struct graph{
    vector<vector<int>> neighbors;

    graph(vector<vector<int>> value){
        for (int i = 0; i < value.size(); ++i){
            vector<int> tmp;
            for (int j = 0; j < value[i].size(); ++j){
                tmp.insert(tmp.end(), value[i][j]);
            }
            neighbors.insert(neighbors.end(), tmp);
            }
    }

    graph(){
    }

    int get_degree(int vertex){
        return neighbors[vertex].size();
    }

    int get_neighbor(int vertex, int index){
        return neighbors[vertex][index];
    }

    int get_graph_size(){
        return neighbors.size();
    }
};

set<int> sample(int max_value, int count){
    set<int> s;
    for (int i = 0; i < count; ++i)
        s.insert(rand() % max_value);
    return s;
}
//Move to inside, problem with sorting
vector<vector<int>> q;

struct Peeling_process{
    graph G;
    double alpha;
    int Q;
    int n;
    int l;
    int t;

    vector<map<int, bool>> Already_called;
    vector<map<int, set<int>>> A;
    vector<map<int, set<int>>> P;
    vector<map<int, set<int>>> B;
    map<int, int> d;

    Peeling_process(graph value_G, double value_alpha){
        G = graph(value_G);
        alpha = value_alpha;
        Q = 0;
        n = G.get_graph_size();
        l = (log(n))/(log(3)-log(2));
        t = 10*n/(alpha * (log(n)/log(2)));
        q = vector<vector<int>>(l+2, vector<int>(n));
        Already_called = vector<map<int, bool>>(l+2);
        A = vector<map<int, set<int>>>(l+2);
        P = vector<map<int, set<int>>>(l+2);
        B = vector<map<int, set<int>>>(l+2);
        d = map<int, int>();

        //cout << alpha << " " << Q << " " << l << " " << t << endl;
    }

    void renew_peeling(double value_alpha){
        alpha = value_alpha;
        Q = 0;
        t = 10*n/(alpha * (log(n)/log(2)));
        q = vector<vector<int>>(l+2, vector<int>(n));
        Already_called = vector<map<int, bool>>(l+2);
        A = vector<map<int, set<int>>>(l+2);
        P = vector<map<int, set<int>>>(l+2);
        B = vector<map<int, set<int>>>(l+2);
        d = map<int, int>();
        return;
    }

    set<int> highest_cost(int size, int j, int v){
        auto b = B[j][v];
        vector<int> vect_b;
        for (auto x: b){
            vect_b.insert(vect_b.begin(), x);
        }
        sort(vect_b.begin(), vect_b.end(), [](int i, int j) { return (q[i]>q[j]); });
        set<int> result;
        for (int i = 0; i < size+1; ++i){
            result.insert(vect_b[i]);
        }
        return result;
    }

    void Peel_Vertex(graph G, int v, int j){
        if (Already_called[j][v]) return;
        Already_called[j][v] = true;
        if (j == 0){
            d[v] = G.get_degree(v);
            ++Q;
            if (d[v] <= 100*(log(n)*log(n)/((log(2)*log(2))))*alpha){
                q[1][v] = 0;
                A[1][v] = set<int>();
                return;
            }
            else{
                q[1][v] = d[v]/(6*alpha);
                return;
            }
        }
        if (j == 1){
            auto S = sample(d[v], d[v]/(6*alpha));
            Q += S.size();
            for (auto i: S){
                A[0][v].insert(G.get_neighbor(v, i));
            }
        }
        for (auto u: A[j-1][v]){
            Peel_Vertex(G, u, j-1);
            if (q[j][u] = 0){
                P[j][v].insert(u);
            }
        }
        std::set_difference(A[j-1][v].begin(), A[j-1][v].end(), P[j][v].begin(), P[j][v].end(),
                            inserter(B[j][v], B[j][v].end()));
        int size_H = 4 * log(n)/log(2) < B[j][v].size()?4*log(n)/log(2):B[j][v].size();
        auto H = highest_cost(size_H, j, v);
        std::set_difference(B[j][v].begin(), B[j][v].end(), H.begin(), H.end(),
                            inserter(A[j][v], A[j][v].end()));
        if (A[j][v].size() <= 8*(log(n)*log(n)/(log(2)*log(2))) - j*4*log(n)/log(2)){
            q[j+1][v] = 0;
            A[j+1][v] = set<int>();
        }
        else
        {
            q[j+1][v] = 0;
            for (auto u: A[j][v])
                q[j+1][v] += q[j][u];
        }
        return;
    }

    bool Peel(){
        vector<set<int>> X(l+2);
        X[0] = sample(n, t);
        for (int j = 0; j <= l; ++j){
            for (auto x: X[j]) {
                if ((j >= 1) && (Q + q[j][x] > 400*t))
                    return false;
                Peel_Vertex(G, x, j);
                if (q[j+1][x] != 0)
                    X[j+1].insert(x);
            }
        }
        return X[l+1].empty();
    }

    bool Peel_reduced_error(){
        for (int r = 0; r < 10*log(n); ++r){
            if (Peel()) return true;
        }
        return false;
    }
};

int Estimate_arborocity(graph G){
    int alpha = G.get_graph_size();
    Peeling_process p(G, alpha);
    while (alpha > 1){
        cout << alpha << endl;
        //Peeling_process p(G, alpha);
        if (!p.Peel_reduced_error()) return alpha;
        alpha = alpha/2;
        p.renew_peeling(alpha);
    }
    return 1;
}

vector<vector<int>> read_graph(){
    int n = 0;
    cin >> n;
    int d;
    vector<vector<int>> result;
    for (int i = 0; i < n; ++i){
        vector<int> tmp;
        cin >> d;
        int neig;
        for (int j = 0; j < d; ++j){
            cin >> neig;
            tmp.insert(tmp.end(), neig);
        }
        result.insert(result.end(), tmp);
    }
    return result;
}

int main() {
    auto value_G = read_graph();
    graph G(value_G);
    cout << "Algorithm is trying the following values:" << endl;
    //Peeling_process p_2(G, 1);
    int result = Estimate_arborocity(G);
    cout << "Final output is " << result;
    return 0;
}
