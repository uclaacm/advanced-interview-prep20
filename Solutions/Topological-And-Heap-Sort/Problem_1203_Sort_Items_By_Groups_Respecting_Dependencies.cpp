/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Sort Items by Groups Respecting Dependencies
    Leetcode Problem 1203
    https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/
*/

class Solution {
public:
    // First, we make sure that each group can be topologically ordered against each other.
    // Then, we make sure that within each group, the items can be topologically ordered.
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {

        // To make like easier for us, put each item
        // that doesn't have a group into its own group
        for(int i = 0; i < n; i++) {
            if(group[i] == -1) {
                group[i] = m;
                m++;
            }
        }
        
        // Construct a vector of groups
        // Given the group number: Return
        // the items inside that group
        vector<vector<int>> groups(m);
        for(int i = 0; i < n; i++) {
            groups[group[i]].push_back(i);
        }
        
        // Keep track of information regarding
        // dependencies between each group
        vector<list<int>> groupGraph(m);
        vector<int> groupIncoming(m, 0);
        vector<bool> groupVisited(m, false);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < beforeItems[i].size(); j++) {
                if(group[beforeItems[i][j]] != group[i]) {
                    groupGraph[group[beforeItems[i][j]]].push_back(group[i]);
                    groupIncoming[group[i]]++;
                }
            }
        }
        
        // Run topological sort on our constructed graph
        queue<int> q;
        for(int i = 0; i < m; i++)
            if(groupIncoming[i] == 0) q.push(i);
        vector<int> groupTopoSort;
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            groupTopoSort.push_back(cur);
            groupVisited[cur] = true;
            for(int node: groupGraph[cur]) {
                groupIncoming[node]--;
                if(!groupVisited[node] && groupIncoming[node] == 0) {
                    q.push(node);
                }
            }
        }
        
        // If the topological sort ends early, a sort isn't possible,
        // so return the empty vector
        if(groupTopoSort.size() != m) return {};

        ///////////////////////////////////////////////////////////////////////
        
        vector<int> itemsSort;
        
        // Topologically items within each group, maintaining the
        // order of the topological sort between each group
        for(int x = 0; x < m; x++) {
            vector<int> curGroup = groups[groupTopoSort[x]];
            int size = curGroup.size();

            // Keep track of information regarding
            // dependencies within the items of the group
            unordered_map<int, list<int>> graph;
            unordered_map<int, int> incoming;
            unordered_map<int, bool> visited;
            for(int i : curGroup) {
                incoming[i] = 0;
                visited[i] = 0;
            }
            for(int i : curGroup) {
                for(int j : beforeItems[i]) {
                    if(incoming.find(j) != incoming.end()) {
                        graph[j].push_back(i);
                        incoming[i]++;
                    }
                }
            }

            // Run topological sort on our constructed graph
            queue<int> q;
            for(int i : curGroup)
                if(incoming[i] == 0) q.push(i);
            vector<int> topoSort;
            while(!q.empty()) {
                int cur = q.front(); q.pop();
                topoSort.push_back(cur);
                visited[cur] = true;
                for(int node: graph[cur]) {
                    incoming[node]--;
                    if(!visited[node] && incoming[node] == 0) {
                        q.push(node);
                    }
                }
            }
     
            // If the topological sort ends early, a sort isn't possible,
            // so return the empty vector. Else, concatenate this late to
            // our final result
            if(topoSort.size() != size) return {};
            else itemsSort.insert(itemsSort.end(), topoSort.begin(), topoSort.end());
        }
        
        return itemsSort;
    }
};