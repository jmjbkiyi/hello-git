#include <iostream>
#include <vector>
#include <algorithm>   //std::count() is here.
#include <stdexcept> //out_of_range is here.
using namespace std;

class GraphAdjMat{
private:
    vector<int> vertices;
    vector<vector<int>> mat;
public:
    GraphAdjMat(const vector<int>& ver, const vector<vector<int>>& edges){
        //add vertexs
        for(int val : ver){
            addVertex(val);
        }
        //add edges
        for(const vector<int> &edge : edges){
            addEdge(edge[0],edge[1]);
        }
    }
    
    int size() const {
        return vertices.size();
    }
    
    void addVertex(int val){
        int n = size();
        
        vertices.push_back(val);
        // 在邻接矩阵中添加一行
        mat.emplace_back(vector<int> (n,0));
        // 在邻接矩阵中添加一列
        for(vector<int> &row : mat){
            row.push_back(0);
        }
    }
    
    void removeVertex(int index){
        if(index >= size() || index < 0){
            throw out_of_range("顶点不存在");
        }
        vertices.erase(vertices.begin() + index);
        
        mat.erase(mat.begin() + index);
        
        for(vector<int> &row : mat){
            row.erase(row.begin() + index);
        }
    }
    
    void addEdge(int i, int j){
        if(i<0 || j<0 || i>=size() || j>=size() || i==j){
            throw out_of_range("顶点不存在");
        }
        mat[i][j]=1;
        mat[j][i]=1;
    }
    
    void removeEdge(int i,int j){
        if(i<0 || j<0 || i>=size() || j>=size() || i==j){
            throw out_of_range("顶点不存在");
        }
        mat[i][j]=0;
        mat[j][i]=0;
    }

// 补充：可视化打印方法
    void print() const {
        cout << "顶点列表: [ ";
        for (int v : vertices) cout << v << " ";
        cout << "]\n邻接矩阵:" << endl;
        for (int i = 0; i < size(); i++) {
            cout << "  ";
            for (int j = 0; j < size(); j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        cout << "-----------------------" << endl;
    }
};

/* --- Driver Code --- */
int main() {
    cout << "=== 初始化无向图 ===" << endl;
    // 顶点值：100, 200, 300, 400
    vector<int> vertices = {100, 200, 300, 400};
    // 边：连接 (0,1), (1,2), (2,3), (0,3) 形成一个环
    vector<vector<int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {0, 3}
    };
    
    GraphAdjMat graph(vertices, edges);
    graph.print();

    cout << "=== 测试 1：添加一条跨对角线的边 (0, 2) ===" << endl;
    graph.addEdge(0, 2);
    graph.print();

    cout << "=== 测试 2：添加一个新顶点 500 ===" << endl;
    // 此时它是一个孤立的顶点，矩阵会自动扩容，且该行该列全为 0
    graph.addVertex(500);
    graph.print();

    cout << "=== 测试 3：将新顶点 500 连接到顶点 100(索引0) ===" << endl;
    // 新顶点 500 的索引是 4
    graph.addEdge(0, 4);
    graph.print();

    cout << "=== 测试 4：删除顶点 300 (原索引为 2) ===" << endl;
    // 删除操作会自动抽离第 2 行和第 2 列，矩阵维度收缩
    graph.removeVertex(2);
    graph.print();

    return 0;
}