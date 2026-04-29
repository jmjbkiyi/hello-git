#include <unordered_set>
#include <queue>
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

//深度优先遍历辅助函数
void dfs(GraphAdjList &graph, unordered_set<Vertex*> &visited, vector<Vertex*> &res, Vertex *vet){
    // visited.push(vet); ！！！ 错误 ！！！ 哈希集合没有push操作
    visited.insert(vet);  //或visited.emplace(vet);
    res.push_back(vet);

    // 遍历当前节点的所有邻居
    for(auto v : graph.list[vet]){
        if(visited.count(v)){
            continue;
        }
        // 核心：对未访问过的邻居，继续向下递归探索
        dfs(graph,visited,res,v);
    }
}
/* 深度优先遍历 */
// 使用邻接表来表示图，以便获取指定顶点的所有邻接顶点
vector<Vertex*> graphDFS(GraphAdjList &graph, Vertex* startVet){
    unordered_set<Vertex*> visited;
    vector<Vertex*> res;
    dfs(graph,visited,res,startVet);
    return res;
}

/* --- Driver Code --- */
int main() {
    cout << "=== 初始化图的顶点 ===" << endl;
    Vertex* v0 = new Vertex(0);
    Vertex* v1 = new Vertex(1);
    Vertex* v2 = new Vertex(2);
    Vertex* v3 = new Vertex(3);
    Vertex* v4 = new Vertex(4);
    Vertex* v5 = new Vertex(5);
    Vertex* v6 = new Vertex(6);

    // 构建边集合
    vector<vector<Vertex*>> edges = {
        {v0, v1}, {v0, v2}, 
        {v1, v3}, {v1, v4}, 
        {v2, v5}, 
        {v4, v6}
    };

    GraphAdjList graph(edges);
    cout << "无向图构建完成。" << endl;
    graph.print();

    cout << "\n=== 开始深度优先遍历 (DFS) ===" << endl;
    cout << "起点: 顶点 0" << endl;
    
    // 调用我们刚修复的 DFS
    vector<Vertex*> dfsResult = graphDFS(graph, v0);
    
    // 打印遍历结果
    cout << "DFS 遍历序列: ";
    printVector(vetsToVals(dfsResult));

    // 内存清理
    delete v0; delete v1; delete v2; delete v3; 
    delete v4; delete v5; delete v6;

    return 0;
}