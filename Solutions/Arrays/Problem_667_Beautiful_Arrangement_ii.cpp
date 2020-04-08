/*
The main idea behind this solution is to vary the difference by 1 for k/2 pairs and then
append the remaining numbers because we don't care about them having a unique difference. 
So we would group
1, 1+k, 2, 2+k-2, 3, 3+k-4,...,1+k+1,1+k+2,...n.
So the differences between successive pairs will be
k, k-1, k-2, k-3...1, 1, 1,...1.
In order to keep track of the numbers that have been inserted into our result we use an
unordered map.
*/
class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<int> res;
        unordered_map<int, bool> inserted;
        int i = 1;
        int temp = k;
        while(k > 0){
            res.push_back(i);
            res.push_back(i+k);
            inserted[i] = true;
            inserted[i+k] = true;
            k-=2;
            i+=1;
        }
        for(int j = 1; j <= n; j++){
            if(inserted.find(j) == inserted.end())
                res.push_back(j);
        }
        return res;
    }
};