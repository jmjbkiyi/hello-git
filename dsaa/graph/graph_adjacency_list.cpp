/* 基于邻接表实现的无向图类 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
using namespace std;

struct Vertex{
    int val;
    explicit Vertex(int x) : val(x){}
};

// 辅助函数：将顶点指针的 vector 转换为顶点值的 vector
vector<int> vetsToVals(const vector<Vertex*>& vets){
    vector<int> vals;
    for(Vertex* vet : vets){
        vals.push_back(vet->val);
    }
    return vals;
}

// 辅助函数：打印 vector
void printVector(const vector<int> &vec){
    cout << "[" ;
    for(int v : vec){
        cout << v << " " ;
    }
    cout << "]" << endl;
}

class GraphAdjList {
public:
    // 邻接表，key：顶点，value：该顶点的所有邻接顶点
    unordered_map<Vertex*, vector<Vertex*>> list;
    
    void remove(vector<Vertex*>& vec, Vertex* vet){
        for(int i=0;i<vec.size();i++){
            if(vec[i] == vet){
                vec.erase(vec.begin() + i);
                break;
            }
        }
    }

    GraphAdjList(const vector<vector<Vertex*>> &edges){
        for(const vector<Vertex*> &edge : edges){
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0],edge[1]);
        }
    }
    
    int size() const {
        return list.size();
    }
    
    void addVertex(Vertex* vet){
        if(list.count(vet)) return;
        list[vet] = vector<Vertex*>();
    }
    void removeVertex(Vertex* vet){
        if(!list.count(vet)) {
            throw invalid_argument("不存在顶点");
        }
        list.erase(vet);
        for(auto &v : list){  //此处不写 for(Vertex*&v : list),因为 v 是 std::pair 类型
            remove(v.second,vet);
        }
    }
    
    void addEdge(Vertex* v1, Vertex* v2){
        if(!list.count(v1) || !list.count(v2) || v1 == v2){
            throw invalid_argument("不存在顶点");
        }
        list[v1].push_back(v2);
        list[v2].push_back(v1);
    }
    
    void removeEdge(Vertex* v1, Vertex* v2){
        if(!list.count(v1) || !list.count(v2) || v1 == v2){
            throw invalid_argument("不存在顶点");
        }
        remove(list[v1],v2);
        remove(list[v2],v1);
    }
    
    void print() const {
        cout << "邻接表 =" << endl;
        for(auto &v : list){
            const auto &key = v.first;
            const auto &vec = v.second;
            cout << key->val << " : " ;
            printVector(vetsToVals(vec));
        }
    }
};

/* --- Driver Code --- */
int main() {
    cout << "=== 初始化顶点 ===" << endl;
    // 在堆上创建顶点，模拟真实的内存分配
    Vertex* v1 = new Vertex(1);
    Vertex* v2 = new Vertex(2);
    Vertex* v3 = new Vertex(3);
    Vertex* v4 = new Vertex(4);
    Vertex* v5 = new Vertex(5);

    // 构造初始边集合：(1,2), (1,3), (2,4)
    vector<vector<Vertex*>> edges = {
        {v1, v2},
        {v1, v3},
        {v2, v4}
    };

    cout << "\n=== 测试 1：构建初始无向图 ===" << endl;
    GraphAdjList graph(edges);
    graph.print();

    cout << "\n=== 测试 2：添加孤立顶点 5 ===" << endl;
    graph.addVertex(v5);
    graph.print();

    cout << "\n=== 测试 3：为 5 添加连线 (3, 5) 和 (4, 5) ===" << endl;
    graph.addEdge(v3, v5);
    graph.addEdge(v4, v5);
    graph.print();

    cout << "\n=== 测试 4：删除边 (1, 2) ===" << endl;
    graph.removeEdge(v1, v2);
    graph.print();

    cout << "\n=== 测试 5：删除顶点 4 ===" << endl;
    // 此时删除 4，与之相连的边 (2,4) 和 (4,5) 也会被彻底清理
    graph.removeVertex(v4);
    graph.print();

    // 释放动态分配的内存，养成良好习惯
    delete v1; delete v2; delete v3; delete v4; delete v5;

    return 0;
}

