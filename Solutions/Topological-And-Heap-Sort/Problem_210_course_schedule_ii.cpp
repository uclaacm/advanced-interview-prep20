/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Course Schedule II
    Leetcode Problem 210
    https://leetcode.com/problems/course-schedule-ii/
*/

// There are a total of n courses you have to take, labeled from 0 to n-1.

// Some courses may have prerequisites, for example to take course 0 you
// have to first take course 1, which is expressed as a pair: [0,1]

// Given the total number of courses and a list of prerequisite pairs,
// return the ordering of courses you should take to finish all courses.

// There may be multiple correct orders, you just need to return one of them.
// If it is impossible to finish all courses, return an empty array.

class Solution {
public:
    // This problem is essentially topological sort,
    // but we must return one such sort if possible.
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // We want to keep track of certain information given a node
        //      * What nodes it points to
        //      * How many incoming edges it has from visited nodes
        //      * Whether we have visited the node yet

        // This section of code builds up this information
        vector<list<int>> graph(numCourses); // Adjacency list
        vector<int> incoming(numCourses, 0);
        vector<bool> visited(numCourses, false);
        for(vector<int> e: prerequisites) {
            graph[e[1]].push_back(e[0]);
            incoming[e[0]]++;
        }
        
        // This queue will store nodes that aren't visited
        // and have zero incoming edges. We pick nodes from
        // here to put into our topological sort
        queue<int> q;
        for(int i = 0; i < numCourses; i++) {
            if(incoming[i] == 0) q.push(i);
        }
        
        vector<int> topoSort;
        while(!q.empty()) {
            // Get a node from the queue and add it to
            // the topological sort. Also mark it as 
            // visited
            int cur = q.front(); q.pop();
            topoSort.push_back(cur);
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

        // A valid topological sort should contain all
        // `numCourses` nodes. If it doesn't, we return
        // an empty vector      
        if(topoSort.size() != numCourses) return {};
        else return topoSort;
    }
};

// Time Complexity: O(V + E) where V is the number of nodes
// and E is the number of edges. We loop through all nodes
// a few times, which is O(V). The while loop with the
// queue potentially processes all edges, which is O(E)

// Space Complexity: O(V + E) where V is the number of nodes
// and E is the number of edges. This is because the adjacency
// list takes up O(V + E) space, and it is the biggest data
// structure we have in our algorithm