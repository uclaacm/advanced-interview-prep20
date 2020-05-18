/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Longest Increasing Path in a Matrix
    Leetcode Problem 329
    https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
*/

// Given an integer matrix, find the length of the longest increasing path.

// From each cell, you can either move to four directions: left, right,
// up or down. You may NOT move diagonally or move outside of the
// boundary (i.e. wrap-around is not allowed).

class Solution {
public:
    // This is a graph problem in disguise (tends to happen with
    // problems with multidimensional arrays). In fact, it's a
    // topological sort problem if you think hard enough about it!

    // Suppose the matrix were instead a DAG where each cell is
    // a node and each cell is connected to those adjacent to it
    // only if the cell's value is lower than the adjacent cell's
    // value.

    // Then, the longest increasing path would be the same as
    // the longest increasing path in the graph. We can find
    // the length of the path by doing a combination of the
    // topological sort algorithm and BFS
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        // Trivial edge case
        if(matrix.size() == 0) return 0;
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        // We want to keep track of certain information given a node
        //      * What nodes it points to
        //      * How many incoming edges it has from visited nodes
        //      * Whether we have visited the node yet
        vector<list<int>> graph(rows * cols); // Adjacency list
        vector<int> incoming(rows * cols, 0);
        vector<int> visited(rows * cols, false);
        
        // Build up the information
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                int index = i * cols + j;

                // Check the up adjacent node
                if(i > 0 && matrix[i][j] < matrix[i-1][j]) {
                    graph[index].push_back((i-1) * cols + j);
                    incoming[(i-1) * cols + j]++;
                }

                // Check the down adjacent node
                if(i < rows - 1 && matrix[i][j] < matrix[i+1][j]) {
                    graph[index].push_back((i+1) * cols + j);
                    incoming[(i+1) * cols + j]++;
                }

                // Check the left adjacent node
                if(j > 0 && matrix[i][j] < matrix[i][j-1]) {
                    graph[index].push_back(i * cols + j-1);
                    incoming[i * cols + j-1]++;
                }

                // Check the right adjacent node
                if(j < cols - 1 && matrix[i][j] < matrix[i][j+1]) {
                    graph[index].push_back(i * cols + j+1);
                    incoming[i * cols + j+1]++;
                }

            }
        }
        
        // This queue will store nodes that aren't visited
        // and have zero incoming edges. We pick nodes from
        // here to put into our topological sort
        queue<int> q;
        for(int i = 0; i < rows * cols; i++) {
            if(incoming[i] == 0) q.push(i);
        }
        
        // We process the graph "level-by-level", where each
        // level is the nodes that aren't visited and have
        // zero incoming edges after we remove all the nodes
        // on the upper levels.

        // The longest path in the graph equals the number of
        // levels, because moving down one level means walking
        // along an edge

        int length = 0;
        while(!q.empty()) {
            // Each iteration of the outer loop
            // represents one level
            length++;

            // Remeber to save this number outside of
            // a loop, or q.size() may change with each
            // iteration
            int size = q.size();

            // Process all nodes on the current level
            // (all nodes currently in the queue)
            for(int i = 0; i < size; i++) {
                // Get a node from the queue and
                // mark it as visited
                int cur = q.front(); q.pop();
                visited[cur] = true;

                // Add nodes that the current node points to
                // to the queue only if we haven't visited it
                // and it has no incoming edges
                for(int node: graph[cur]) {
                    incoming[node]--;
                    if(!visited[node] && incoming[node] == 0) {
                        q.push(node);
                    }
                }
            }
        }
        
        return length;
    }
};