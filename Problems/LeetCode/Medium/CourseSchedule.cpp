// https://leetcode.com/problems/course-schedule/

class Solution {
public:
    /*
    Requirements in the graph:
    1. There have be no cycles
    
    3, [[1,0], [2,1], [0,2]] - false
    3, [[1,0], [2,0], [2,1]] - true
    
    How to detect cycles in the graph?
    During each path of DFS, we can insert node to hashset to check whether it is in the path
    */
    bool visit(int& node, vector<vector<int>>& nodes, vector<bool>& visited) {
        if (visited[node]) // already exists in the path
            return false;
        visited[node] = true;
        for (int adjacent : nodes[node])
            if (!visit(adjacent, nodes, visited))
                return false;
        visited[node] = false;
        return true;
    }
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> nodes(numCourses, vector<int>()); // graph
        // construct a graph
        for (vector<int> prereq : prerequisites)
            nodes[prereq[1]].push_back(prereq[0]); // add adjacent node
        vector<bool> visited(numCourses, false);
        for (int i = 0; i < nodes.size(); i++)
            if (!visit(i, nodes, visited))
                return false;
        return true;
    }
};

// Faster approach: color the nodes instead of flags
class Solution {
public:
    /*
    Requirements in the graph:
    1. There have be no cycles
    
    3, [[1,0], [2,1], [0,2]] - false
    3, [[1,0], [2,0], [2,1]] - true
    
    How to detect cycles in the graph?
    During each path of DFS, we can insert node to hashset to check whether it is in the path
    */
    void visit(int& node, vector<vector<int>>& nodes, vector<int>& visited, bool& isAcyclic) {
        if (!isAcyclic) // cycle is present
            return;
        visited[node] = 2; // GRAY
        for (int adjacent : nodes[node]) {
            if (visited[adjacent] == 1) // WHITE
                visit(adjacent, nodes, visited, isAcyclic);
            else if (visited[adjacent] == 2) // GRAY
                isAcyclic = false;
        }
        visited[node] = 3;
    }
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> nodes(numCourses, vector<int>()); // graph
        // construct a graph
        for (vector<int> prereq : prerequisites)
            nodes[prereq[1]].push_back(prereq[0]); // add adjacent node
        vector<int> visited(numCourses, 1);
        bool isAcyclic = true;
        for (int i = 0; i < nodes.size(); i++) {   
            if (!isAcyclic)
                break;
            visit(i, nodes, visited, isAcyclic);
        }
        return isAcyclic;
    }
};