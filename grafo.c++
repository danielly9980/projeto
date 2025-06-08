#include <iostream>
#include <vector>

using namespace std;

class Grafo {
public:
    int V; 
    vector<vector<int>> adj; 

    Grafo(int V) {
        this->V = V;
        adj.resize(V, vector<int>(V, 0));
    }

    void adicionarAresta(int u, int v) {
        adj[u][v]++;
        adj[v][u]++;
    }

    void removerAresta(int u, int v) {
        adj[u][v]--;
        adj[v][u]--;
    }

    void dfs(int v, vector<bool>& visitado) {
        visitado[v] = true;
        for (int i = 0; i < V; i++)
            if (adj[v][i] > 0 && !visitado[i])
                dfs(i, visitado);
    }

    bool arestaEhPonte(int u, int v) {
        if (adj[u][v] == 0) return false;

        // Se for a única aresta, pode usar
        int count = 0;
        for (int i = 0; i < V; i++) count += adj[u][i];
        if (count == 1) return false;

        // Verifica conectividade antes de remover
        vector<bool> visitado1(V, false);
        dfs(u, visitado1);
        int alcançáveis1 = 0;
        for (bool v : visitado1) if (v) alcançáveis1++;

        removerAresta(u, v);
        vector<bool> visitado2(V, false);
        dfs(u, visitado2);
        int alcançáveis2 = 0;
        for (bool v : visitado2) if (v) alcançáveis2++;
        adicionarAresta(u, v); 

        return alcançáveis2 < alcançáveis1;
    }

    void fleury(int u) {
        for (int v = 0; v < V; v++) {
            if (adj[u][v] > 0 && !arestaEhPonte(u, v)) {
                cout << u + 1 << " -> ";
                removerAresta(u, v);
                fleury(v);
                return;
            }
        }

        for (int v = 0; v < V; v++) {
            if (adj[u][v] > 0) {
                cout << u + 1 << " -> ";
                removerAresta(u, v);
                fleury(v);
                return;
            }
        }

        cout << u + 1;
    }

    void encontrarCaminhoEuleriano() {
        int impar = 0;
        int inicio = 0;
        for (int i = 0; i < V; i++) {
            int grau = 0;
            for (int j = 0; j < V; j++)
                grau += adj[i][j];
            if (grau % 2 == 1) {
                impar++;
                inicio = i;
            }
        }

        if (impar != 0 && impar != 2) {
            cout << "[!] O grafo NÃO tem caminho nem circuito euleriano.\n";
            return;
        }

        cout << "\nCaminho Euleriano:\n";
        fleury(inicio);
        cout << endl;
    }

    void imprimirMatriz() {
        cout << "\nMatriz de Adjacência:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                cout << adj[i][j] << " ";
            cout << endl;
        }
    }
};


int main() {
    Grafo G(5);


    G.adicionarAresta(0, 1);
    G.adicionarAresta(1, 2);
    G.adicionarAresta(2, 3);
    G.adicionarAresta(3, 0);
    G.adicionarAresta(0, 2);

    G.imprimirMatriz();
    G.encontrarCaminhoEuleriano();

    return 0;
}
