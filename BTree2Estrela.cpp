// B* tree
#include <bits/stdc++.h>
using namespace std;
  

#define N 4 // Orden del ARbol
  
struct node {
  
    // chave de nós N-1
    int key[N - 1];
      
    // filho of 'N' length
    struct node* child[N];
      
    // Declarar se é folha ou não; se nó
    // é uma folha, isleaf=1 senão isleaf=0
    int isleaf;
      
    // Conta o número de chaves preenchidas em um nó
    int n;
      
    // Mantém o controle do nó pai
    struct node* parent;
};
  
// Esta função procura a folha
// no qual inserir o elemento 'k'
struct node* searchforleaf(struct node* root, int k, 
                     struct node* parent, int chindex)
{
    if (root) {
  
        // Se a raiz passada for um nó folha, então
        // k pode ser inserido neste próprio nó
        if (root->isleaf == 1)
            return root;
              
        // Se a raiz passada não for um nó folha,
        // implicando que há um ou mais filhos
        else {
            int i;
              
          /*Se a chave inicial da raiz passada for maior que 
          o elemento a ser inserido, precisamos inserir em uma 
          nova folha à esquerda da raiz*/
            if (k < root->key[0])
                root = searchforleaf(root->child[0], k, root, 0);
                  
            else 
            {
                // Encontra a primeira chave cujo valor é maior
                 // que o valor de inserção
                 // e insere no filho dessa chave
                for (i = 0; i < root->n; i++)
                    if (root->key[i] > k)
                        root = searchforleaf(root->child[i], k, root, i);
                          
                // Se todas as chaves forem menores que a inserção
                 // valor da chave, inserido à direita da última chave
                if (root->key[i - 1] < k)
                    root = searchforleaf(root->child[i], k, root, i);
            }
        }
    }
    else {
          
       // Se a raiz passada for NULL (não existe tal
         // nó filho para pesquisar), então crie uma nova folha
         // nó nesse local
        struct node* newleaf = new struct node;
        newleaf->isleaf = 1;
        newleaf->n = 0;
        parent->child[chindex] = newleaf;
        newleaf->parent = parent;
        return newleaf;
    }
}
  
struct node* insert(struct node* root, int k)
{
    if (root) {
        struct node* p = searchforleaf(root, k, NULL, 0);
        struct node* q = NULL;
        int e = k;
          
        // Se o nó folha estiver vazio, simplesmente
         // adiciona o elemento e retorna
        for (int e = k; p; p = p->parent) { 
            if (p->n == 0) {
                p->key[0] = e;
                p->n = 1;
                return root;
            }
            // Se o número de chaves preenchidas for menor que o máximo
            if (p->n < N - 1) {
                int i;
                for (i = 0; i < p->n; i++) {
                    if (p->key[i] > e) {
                        for (int j = p->n - 1; j >= i; j--)
                            p->key[j + 1] = p->key[j];
                        break;
                    }
                }
                p->key[i] = e;
                p->n = p->n + 1;
                return root;
            }
              
           // Se o número de chaves preenchidas for igual ao máximo
             // e não é root e há espaço no pai
            if (p->n == N - 1 && p->parent && p->parent->n < N) {
                int m;
                for (int i = 0; i < p->parent->n; i++)
                    if (p->parent->child[i] == p) {
                        m = i;
                        break;
                    }
                      
                // Se o irmão direito é possível
                if (m + 1 <= N - 1) 
                {
                    //q é o irmão certo
                    q = p->parent->child[m + 1];
                      
                    if (q) {
                          
                        // Se o irmão direito estiver cheio
                        if (q->n == N - 1) {
                            struct node* r = new struct node;
                            int* z = new int[((2 * N) / 3)];
                            int parent1, parent2;
                            int* marray = new int[2 * N];
                            int i;
                            for (i = 0; i < p->n; i++)
                                marray[i] = p->key[i];
                            int fege = i;
                            marray[i] = e;
                            marray[i + 1] = p->parent->key[m];
                            for (int j = i + 2; j < ((i + 2) + (q->n)); j++)
                                marray[j] = q->key[j - (i + 2)];
                                  
                            
  
                            // Coloca primeiro (2*N-2)/3 elementos nas chaves de p
                            for (int i = 0; i < (2 * N - 2) / 3; i++)
                                p->key[i] = marray[i];
                            parent1 = marray[(2 * N - 2) / 3];
  
                            // Coloca os próximos (2*N-1)/3 elementos nas chaves de q
                            for (int j = ((2 * N - 2) / 3) + 1; j < (4 * N) / 3; j++)
                                q->key[j - ((2 * N - 2) / 3 + 1)] = marray[j];
                            parent2 = marray[(4 * N) / 3];
  
                            // Coloca os últimos (2*N)/3 elementos nas chaves de r
                            for (int f = ((4 * N) / 3 + 1); f < 2 * N; f++)
                                r->key[f - ((4 * N) / 3 + 1)] = marray[f];
  
                            // Como m=0 e m=1 são filhos da mesma chave,
                             // um caso especial é feito para eles
                            if (m == 0 || m == 1) {
                                p->parent->key[0] = parent1;
                                p->parent->key[1] = parent2;
                                p->parent->child[0] = p;
                                p->parent->child[1] = q;
                                p->parent->child[2] = r;
                                return root;
                            }
  
                            else {
                                p->parent->key[m - 1] = parent1;
                                p->parent->key[m] = parent2;
                                p->parent->child[m - 1] = p;
                                p->parent->child[m] = q;
                                p->parent->child[m + 1] = r;
                                return root;
                            }
                        }
                    }
                    else //Se o irmão direito não estiver cheio
                    {
                        int put;
                        if (m == 0 || m == 1)
                            put = p->parent->key[0];
                        else
                            put = p->parent->key[m - 1];
                        for (int j = (q->n) - 1; j >= 1; j--)
                            q->key[j + 1] = q->key[j];
                        q->key[0] = put;
                        p->parent->key[m == 0 ? m : m - 1] = p->key[p->n - 1];
                    }
                }
            }
        }
  
        /*Casos de divisão de raiz, etc. são omitidos
          pois esta implementação é apenas para demonstrar
          a operação de divisão dois-três*/
    }
    else 
    {
        // Cria um novo nó se a raiz for NULL
        struct node* root = new struct node;
        root->key[0] = k;
        root->isleaf = 1;
        root->n = 1;
        root->parent = NULL;
    }
}
  
int main()
{ 
    // Comece com uma raiz vazia
    struct node* root = NULL;
    // Inserir 6
    root = insert(root, 6);
      
    // Inserir 1, 2, 4 pela esquerda de 6
    root->child[0] = insert(root->child[0], 1);
    root->child[0] = insert(root->child[0], 2);
    root->child[0] = insert(root->child[0], 4);
    root->child[0]->parent = root;
      
      
    // Inserir 7, 8, 9 pela direita de 6
    root->child[1] = insert(root->child[1], 7);
    root->child[1] = insert(root->child[1], 8);
    root->child[1] = insert(root->child[1], 9);
    root->child[1]->parent = root;
      
      
    cout << "Arvore ao inicio: " << endl;
    for (int i = 0; i < root->n; i++)
        cout << root->key[i] << " ";
    cout << endl;
    for (int i = 0; i < 2; i++) {
        cout << root->child[i]->key[0] << " ";
        cout << root->child[i]->key[1] << " ";
        cout << root->child[i]->key[2] << " ";
    }
    cout << endl;
      
      
    cout << "Depois de adicionar o 5: " << endl;
  
    // Inserindo elemento '5':
  
    root->child[0] = insert(root->child[0], 5);
  
  
    for (int i = 0; i <= root->n; i++)
        cout << root->key[i] << " ";
    cout << endl;
    for (int i = 0; i < N - 1; i++) {
        cout << root->child[i]->key[0] << " ";
        cout << root->child[i]->key[1] << " ";
    }
      
    return 0;
}