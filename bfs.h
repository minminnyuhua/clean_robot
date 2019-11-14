#ifndef BFS_H_INCLUDED
#define BFS_H_INCLUDED
// C++ code
#include <iostream>
#include <vector>
#include <list>
#include <queue>

class Graph{
private:
    int num_vertex;
    std::vector< std::list<int> > AdjList;
    int *color,             // 0:�զ�, 1:�Ǧ�, 2:�¦�
        *distance,          // 0:�_�I, �L���j:�q�_�I�����쪺vertex
        *predecessor;       // -1:�S��predecessor, ��ܬ��_�Ivertex
public:
    Graph():num_vertex(0){};           // default constructor
    Graph(int N):num_vertex(N){        // constructor with input: number of vertex
        // initialize Adjacency List
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    void BFS(int Start);
};

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
}

void Graph::BFS(int Start){

    color = new int[num_vertex];
    predecessor = new int[num_vertex];
    distance = new int[num_vertex];

    for (int i = 0; i < num_vertex; i++) {  // ��l�ơA�p�ϤG(b)
        color[i] = 0;                       // 0:�զ�;
        predecessor[i] = -1;                // -1��ܨS��predecessor
        distance[i] = num_vertex+1;         // num_vertex��vertex,
    }                                       // �̪��Z�� distance = num_vertex -1��edge

    std::queue<int> q;
    int i = Start;

    for (int j = 0; j < num_vertex; j++) {  // j�q0�ƨ�num_vertex-1, �]��j�|���Lgraph���Ҧ�vertex
        if (color[i] == 0) {                // �Ĥ@��i�|�O�_�Ivertex, �p�ϤG(c)
            color[i] = 1;                   // 1:�Ǧ�
            distance[i] = 0;                // �C�@��connected component���_�I���Z���]��0
            predecessor[i] = -1;            // �C�@��connected component���_�I�S��predecessor
            q.push(i);
            while (!q.empty()) {
                int u = q.front();                  // u ���s���j�M�_�I
                for (std::list<int>::iterator itr = AdjList[u].begin();        // for loop �Ӫ�
                     itr != AdjList[u].end(); itr++) {                         // ������q
                    if (color[*itr] == 0) {                // �Y�Q�u���v��vertex�O�զ�
                        color[*itr] = 1;                   // ��Ǧ�, ��ܤw�g�Q�u���v
                        distance[*itr] = distance[u] + 1;  // �Z���Opredecessor���Z���[�@
                        predecessor[*itr] = u;             // ��s�Q�u���v��vertex��predecessor
                        q.push(*itr);                      // ��vertex���iqueue
                    }
                }
                q.pop();        // ��u���Xqueue
                color[u] = 2;   // �åB��u��¦�
            }
        }
        // �Y�@���^��S����Ҧ�vertex���L, ���graph���h��connected component
        // �N��i�t��j, �~���ˬdgraph������Lvertex�O�_���O�զ�, �Y�O, ����while loop
        i = j;
    }
}


#endif // BFS_H_INCLUDED
