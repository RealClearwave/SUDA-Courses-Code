/*
[问题描述]
设计并实现一个社交网络模型图。
要求：
（1）每个人的信息是一个顶点，两个人相互认识则构成边。
（2）根据输入的任意两个人的信息，给出他们之间的联系路径，最少经过多少人构成联系。
（3）可根据自己的创意添加更多的功能。
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

// 社交网络类
class SocialNetwork {
private:
    unordered_map<string, vector<string>> adjList; // 用邻接表表示社交网络图

public:
    // 添加一个人到网络中
    void addPerson(const string& name) {
        if (adjList.find(name) == adjList.end()) {
            adjList[name] = {};
            cout << "成功将 " << name << " 添加到社交网络中。\n";
        } else {
            cout << name << " 已经存在于社交网络中。\n";
        }
    }

    // 添加两个人之间的关系
    void addRelationship(const string& person1, const string& person2) {
        if (adjList.find(person1) == adjList.end() || adjList.find(person2) == adjList.end()) {
            cout << "无法建立关系，因为 " << person1 << " 或 " << person2 << " 不在网络中。\n";
            return;
        }
        adjList[person1].push_back(person2);
        adjList[person2].push_back(person1);
        cout << "成功建立 " << person1 << " 和 " << person2 << " 的关系。\n";
    }

    // 查找两个人之间的最短路径
    void findShortestPath(const string& start, const string& end) {
        if (adjList.find(start) == adjList.end() || adjList.find(end) == adjList.end()) {
            cout << "无法查找路径，因为 " << start << " 或 " << end << " 不在网络中。\n";
            return;
        }

        queue<string> q;
        unordered_map<string, int> distance;
        unordered_map<string, string> parent;

        // 初始化距离为无限大
        for (const auto& person : adjList) {
            distance[person.first] = numeric_limits<int>::max();
        }

        // BFS 初始化
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

        if (distance[end] == numeric_limits<int>::max()) {
            cout << start << " 和 " << end << " 之间没有路径。\n";
        } else {
            cout << start << " 到 " << end << " 的最短路径为：\n";
            vector<string> path;
            for (string at = end; at != ""; at = parent[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << "\n路径长度为：" << distance[end] << "\n";
        }
    }

    // 查看某个人的直接好友列表
    void listFriends(const string& name) {
        if (adjList.find(name) == adjList.end()) {
            cout << name << " 不在网络中。\n";
            return;
        }
        cout << name << " 的好友列表：\n";
        for (const string& friendName : adjList[name]) {
            cout << "- " << friendName << "\n";
        }
    }

    // 删除两个人之间的关系
    void removeRelationship(const string& person1, const string& person2) {
        if (adjList.find(person1) == adjList.end() || adjList.find(person2) == adjList.end()) {
            cout << "无法删除关系，因为 " << person1 << " 或 " << person2 << " 不在网络中。\n";
            return;
        }

        adjList[person1].erase(remove(adjList[person1].begin(), adjList[person1].end(), person2), adjList[person1].end());
        adjList[person2].erase(remove(adjList[person2].begin(), adjList[person2].end(), person1), adjList[person2].end());
        cout << "成功删除 " << person1 << " 和 " << person2 << " 的关系。\n";
    }
};

int main() {
    SocialNetwork network;
    string command;

    cout << "欢迎使用社交网络系统！请输入指令：\n";

    while (true) {
        cout << "\n可用指令：addPerson, addRelationship, findShortestPath, listFriends, removeRelationship, exit\n";
        cout << "请输入指令：";
        cin >> command;

        if (command == "addPerson") {
            string name;
            cout << "请输入要添加的名字：";
            cin >> name;
            network.addPerson(name);
        } else if (command == "addRelationship") {
            string person1, person2;
            cout << "请输入两个人的名字（用空格分隔）：";
            cin >> person1 >> person2;
            network.addRelationship(person1, person2);
        } else if (command == "findShortestPath") {
            string start, end;
            cout << "请输入起始和目标的名字（用空格分隔）：";
            cin >> start >> end;
            network.findShortestPath(start, end);
        } else if (command == "listFriends") {
            string name;
            cout << "请输入要查看的名字：";
            cin >> name;
            network.listFriends(name);
        } else if (command == "removeRelationship") {
            string person1, person2;
            cout << "请输入两个人的名字（用空格分隔）：";
            cin >> person1 >> person2;
            network.removeRelationship(person1, person2);
        } else if (command == "exit") {
            cout << "退出系统，再见！\n";
            break;
        } else {
            cout << "无效的指令，请重新输入。\n";
        }
    }

    return 0;
}