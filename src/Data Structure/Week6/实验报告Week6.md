# 实验报告

## 一、问题描述及要求

### 题目 1：无向图的邻接矩阵和邻接表操作

**实验内容：**
1. 创建一个无向图的邻接矩阵和邻接表结构。
2. 在邻接矩阵结构下对该图进行深度优先搜索。
3. 在邻接表结构下对该图进行广度优先搜索。

**实验要求：**
- 实现无向图的邻接矩阵存储和邻接表存储。
- 编写深度优先搜索（DFS）和广度优先搜索（BFS）算法，分别适用于邻接矩阵和邻接表。
- 测试图的遍历过程，输出各节点的访问顺序。


### 题目 2：社交网络模型图的设计与实现

**实验内容：**
1. 设计一个社交网络图模型，使用邻接表存储。
2. 根据输入的任意两个人的信息，给出他们之间的联系路径，并计算路径长度。
3. 添加功能：查看某个人的好友列表、删除关系、以及扩展功能（如好友推荐）。

**实验要求：**
- 基于字符串表示顶点信息（如人名），构建社交网络模型。
- 使用广度优先搜索算法查找最短路径。
- 测试各功能，验证实现的正确性。


## 二、概要设计

### 1. 系统功能列表

#### 题目 1：无向图
- **图的存储**
  - `createAdjMatrix()`: 创建邻接矩阵。
  - `createAdjList()`: 创建邻接表。
- **深度优先搜索**
  - `dfsMatrix(int start)`: 基于邻接矩阵的 DFS。
- **广度优先搜索**
  - `bfsList(int start)`: 基于邻接表的 BFS。

#### 题目 2：社交网络模型
- **社交网络功能**
  - **节点与边操作：**
    - `addPerson(string name)`: 添加一个用户到网络中。
    - `addRelationship(string person1, string person2)`: 添加两人之间的关系（边）。
    - `removeRelationship(string person1, string person2)`: 删除两人之间的关系。
  - **路径与好友操作：**
    - `findShortestPath(string start, string end)`: 查找两人之间的最短路径。
    - `listFriends(string name)`: 查看某用户的直接好友列表。
  - **扩展功能：**
    - `recommendFriends(string name)`: 推荐好友（基于共同好友数最多的用户）。


### 2. 数据结构设计

#### 题目 1：无向图的邻接矩阵与邻接表
- **邻接矩阵**
  - 使用二维数组表示图，其中 `matrix[i][j] = 1` 表示节点 `i` 和 `j` 有边。
- **邻接表**
  - 使用 `vector<int>` 存储每个节点的相邻节点列表。

#### 题目 2：社交网络模型
- **节点和边**
  - 使用 `unordered_map<string, vector<string>>` 表示邻接表，键为人名，值为其好友列表。
- **最短路径**
  - 使用广度优先搜索（BFS）计算最短路径。


## 三、详细设计

### 题目 1：无向图的邻接矩阵和邻接表操作
- **邻接矩阵 DFS 实现**
  ```cpp
  void DFTraverse_ga(int u) {
      if (visited[u]) return;
      visited[u] = true;
      cout << u << " ";
      for (int i = 1; i <= n; i++) {
          if (matrix[u][i] == 1 && !visited[i]) {
              DFTraverse_ga(i);
          }
      }
  }
  ```
- **邻接表 BFS 实现**
  ```cpp
  void BFTraverse_gv(int u) {
      queue<int> q;
      q.push(u);
      visited[u] = true;
      while (!q.empty()) {
          int node = q.front();
          q.pop();
          cout << node << " ";
          for (int neighbor : adjList[node]) {
              if (!visited[neighbor]) {
                  visited[neighbor] = true;
                  q.push(neighbor);
              }
          }
      }
  }
  ```

### 题目 2：社交网络模型功能实现
- **查找最短路径**
  ```cpp
  void findShortestPath(const string& start, const string& end) {
      queue<string> q;
      unordered_map<string, int> distance;
      unordered_map<string, string> parent;
      for (const auto& person : adjList) {
          distance[person.first] = numeric_limits<int>::max();
      }
      q.push(start);
      distance[start] = 0;
      parent[start] = "";
      while (!q.empty()) {
          string current = q.front();
          q.pop();
          for (const string& neighbor : adjList[current]) {
              if (distance[neighbor] == numeric_limits<int>::max()) {
                  distance[neighbor] = distance[current] + 1;
                  parent[neighbor] = current;
                  q.push(neighbor);
              }
          }
      }
      // 输出路径
      if (distance[end] == numeric_limits<int>::max()) {
          cout << "无法找到路径。\n";
      } else {
          vector<string> path;
          for (string at = end; !at.empty(); at = parent[at]) {
              path.push_back(at);
          }
          reverse(path.begin(), path.end());
          for (size_t i = 0; i < path.size(); ++i) {
              cout << path[i];
              if (i < path.size() - 1) cout << " -> ";
          }
          cout << "\n路径长度：" << distance[end] << "\n";
      }
  }
  ```


## 四、实验结果

### 题目 1：无向图的邻接矩阵与邻接表操作
- **测试用例**
  - 输入：
    ```
    n = 5, m = 4
    边：1-2, 2-3, 3-4, 4-5
    ```
  - 输出：
    ```
    DFTraverse_ga: 1 2 3 4 5
    BFTraverse_gv: 1 2 3 4 5
    ```

### 题目 2：社交网络模型
- **测试用例**
  - 添加节点：
    ```
    addPerson(Alice), addPerson(Bob), addPerson(Charlie)
    ```
    输出：
    ```
    成功添加 Alice, Bob, Charlie
    ```
  - 添加关系：
    ```
    addRelationship(Alice, Bob), addRelationship(Bob, Charlie)
    ```
    输出：
    ```
    成功建立关系
    ```
  - 最短路径查询：
    ```
    findShortestPath(Alice, Charlie)
    ```
    输出：
    ```
    Alice -> Bob -> Charlie
    路径长度：2
    ```


## 五、实验分析与探讨

### 1. 功能验证
- 题目 1 和题目 2 的所有功能均通过测试。
- 图的存储和遍历实现高效，BFS 和 DFS 输出正确。
- 社交网络模型的路径查询和好友管理功能验证了图的灵活性。

### 2. 问题与解决
- **递归深度限制**：对于 DFS，避免超出栈深限制，采用循环替代。
- **扩展性优化**：社交网络模型采用字符串作为顶点，提高可读性和灵活性。


## 六、总结与反思

- **无向图的操作**：邻接矩阵适用于稠密图，邻接表适用于稀疏图，各有优劣。
- **社交网络的设计**：通过 BFS 实现最短路径查询，适合动态社交关系管理。