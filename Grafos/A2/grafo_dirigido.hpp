#include <bits/stdc++.h>
using namespace std;

class GrafoDirigido
{
public:
    vector<string> rotulos;
    vector<vector<int>> adj;
    int V;
    int E;

    GrafoDirigido(string arquivo)
    {
        char data[100];
        ifstream infile(arquivo);

        infile >> data;
        //cout << data << endl;

        E = 0;
        infile >> V;
        adj.resize(V);

        string line;
        while (getline(infile, line))
        {
            if (line == "*arcs")
            {
                 break;
            } else {
                istringstream iss(line);
                //https://regex101.com/r/nQyp5c/1
                line = regex_replace(line, regex("(\\d+)\\s+(?:\"(.+)\"|([^\\n]))"), "$2$3");
                //cout << line << endl;
                rotulos.push_back(line);
            }
        }

        /*for (auto i : rotulos)
            cout << i << endl;*/

        while (getline(infile, line))
        {
            istringstream iss(line);
            int a, b, c;

            if (!(iss >> a >> b >> c)) {} else
            {
                //cout << a << " " << b << " " << c << endl;
                adicionarAresta(a, b);
                E++;
            }
        }
    }

    int qtdVertices()
    {
        return V;
    }

    int qtdArestas()
    {
        return E;
    }

    int grau(int v)
    {
        return adj[v-1].size();
    }

    string rotulo(int v)
    {
        return rotulos[v];
    }

    vector<int> vizinhos(int v)
    {
        vector<int> vizinhanca;
        for (auto vizinho : adj[v-1])
        {
            vizinhanca.push_back(vizinho+1);
        }
        return vizinhanca;
    }

    bool haAresta(int u, int v)
    {
        int vertice;
        for (auto vertice : adj[u-1])
        {
            if ((v - 1) == vertice)
            {
                return true;
            }
        }
        return false;
    }

    void adicionarAresta(int u, int v)
    {
        adj[u-1].push_back(v-1);
        //cout << "U" << endl;
    }

    void imprimirGrafo()
    {
        int v;
        float w;
        for (int u = 0; u < V; u++)
        {
            cout << "Vértice " << u+1 << " está conectado com \n";
            for (auto v : adj[u])
            {
                cout << "\tVértice " << v+1 << "\n";
            }
            cout << "\n";
        }
    }

    void dfs()
    {
        vector<bool> C;
        vector<int> T;
        vector<int> F;
        vector<int> A;

        int tempo = 0;

        for(int i = 0; i < V; i++)
        {
            C.push_back(false);
            T.push_back(numeric_limits<int>::max());
            F.push_back(numeric_limits<int>::max());
            A.push_back(-1);
        }

        for(int u = 0; u < V; u++)
        {
            if (C[u] == false)
            {
                dfsVisit(u, C, T, A, F, tempo);
            }
        }
    }

    void dfsVisit(int& v, vector<bool> C, vector<int>& T, vector<int>& A, vector<int>& F, int& tempo)
    {
        C[v] = true;
        tempo = tempo + 1;
        T[v] = tempo;
        for (auto u : vizinhos(v+1))
        {
            if (C[u] == false)
            {
                A[u] = v;
                dfsVisit(u, C, T, A, F, tempo);
            }
        }
        tempo = tempo + 1;
        F[v] = tempo;
    }
};
