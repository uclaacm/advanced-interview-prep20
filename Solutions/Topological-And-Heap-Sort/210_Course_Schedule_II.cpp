class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int input_degree[100000] = {0};
        unordered_map<int, vector<int>> edges;
        queue<int> proc;
        vector<int> order;
        for(auto prereq : prerequisites){
            input_degree[prereq[0]] += 1;
            edges[prereq[1]].push_back(prereq[0]);
        }
        for(int i = 0; i < numCourses; i++){
            if(input_degree[i] == 0) proc.push(i);
        }
        while(proc.size()){
            int temp = proc.front();
            proc.pop();
            for(int i = 0; i < edges[temp].size(); i++){
                input_degree[edges[temp][i]] -= 1;
                if(input_degree[edges[temp][i]] == 0) proc.push(edges[temp][i]);
            }
            order.push_back(temp);
        }
        if(order.size() == numCourses){
            return order;
        }else{
            return {};
        }
    }
};