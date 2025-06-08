#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define ll long long int

struct Vertice {
    ll No;
    ll Grau;
    set<ll> Adj;

    Vertice(ll Indicador = 0) {
        this->No = Indicador;
        this->Grau = 0;
    }
};

class Grafos {
public:
    ll QV;       
    ll QE;       
    Vertice* Vert;

    
    Grafos(ll V) {
        this->QV = V;
        this->QE = 0;
        this->Vert = new Vertice[V]();
        for (ll i = 0; i < this->QV; i++)
            this->Vert[i].No = i;
    }

    void Inserir_Aresta_(int V, int W) {
        if (V != W && Vert[V].Adj.find(W) == Vert[V].Adj.end()) {
            this->QE++;
            Vert[V].Adj.insert(W);
            Vert[W].Adj.insert(V);
            Vert[V].Grau++;
            Vert[W].Grau++;
        }
    }

    void Remover_Aresta_(int V, int W) {
        if (Vert[V].Adj.find(W) != Vert[V].Adj.end()) {
            this->QE--;
            Vert[V].Adj.erase(W);
            Vert[W].Adj.erase(V);
            Vert[V].Grau--;
            Vert[W].Grau--;
        }
    }

    void DFS(int V, vector<bool>& visitado) {
        visitado[V] = true;
        for (int viz : Vert[V].Adj)
            if (!visitado[viz])
                DFS(viz, visitado);
    }

    bool Aresta_Eh_Ponte(int V, int W) {
        vector<bool> visitado1(QV, false);
        DFS(V, visitado1);
        int alc1 = count(visitado1.begin(), visitado1.end(), true);

        Remover_Aresta_(V, W);
        vector<bool> visitado2(QV, false);
        DFS(V, visitado2);
        int alc2 = count(visitado2.begin(), visitado2.end(), true);

        Inserir_Aresta_(V, W);

        return alc2 < alc1;
    }

    void Algoritmo_Fleury() {
        int inicio = -1;
        int impares = 0;

        for (int i = 0; i < QV; i++) {
            if (Vert[i].Grau % 2 != 0) {
                impares++;
                if (inicio == -1) inicio = i;
            }
        }

        if (impares != 0 && impares != 2) {
            cout << "\n[!] O grafo NÃO possui caminho nem circuito euleriano.\n";
            return;
        }

        if (inicio == -1)
            for (int i = 0; i < QV; i++)
                if (!Vert[i].Adj.empty()) {
                    inicio = i;
                    break;
                }

        cout << "\nCaminho Euleriano:\n";
        Fleury(inicio);
        cout << endl;
    }

    void Fleury(int V) {
        for (auto it = Vert[V].Adj.begin(); it != Vert[V].Adj.end(); ) {
            int W = *it;
            if (!Aresta_Eh_Ponte(V, W) || Vert[V].Adj.size() == 1) {
                cout << V + 1 << " -> ";
                Remover_Aresta_(V, W);
                Fleury(W);
                return;
            } else {
                ++it;
            }
        }
        cout << V + 1;
    }

    void Imprimir_Grafo_() {
        cout << "\nGrafo - Lista de Adjacência:\n";
        for (ll V = 0; V < QV; V++) {
            cout << "  " << V+1 << ":";
            for (auto& adj : Vert[V].Adj)
                cout << " " << adj+1;
            cout << endl;
        }
    }

    ~Grafos() {
        delete[] Vert;
    }
};

int main() {
    Grafos G(5);  

    // Inserindo arestas
    G.Inserir_Aresta_(0, 1);
    G.Inserir_Aresta_(1, 2);
    G.Inserir_Aresta_(2, 3);
    G.Inserir_Aresta_(3, 0);
    G.Inserir_Aresta_(0, 2);  

    G.Imprimir_Grafo_();
    G.Algoritmo_Fleury();

    return 0;
}
