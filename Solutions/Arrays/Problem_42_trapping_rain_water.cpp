/*
Let H be the highest wall in the sequence.
We can divide the problem into 3 parts.
1. Find the amount of water trapped to the left of the first wall of height H.
   The amount of water trapped by a given wall be the difference between the maximum heighted wall
   to its left (including itself) and the height of the wall.
2. Find the amount of water trapped between the left-most wall of height H and the right-most wall
   of height H. If there is only one wall of height H we skip this part of the problem. The amount of
   water trapped by each wall in this part will be the difference between H and the height of the current wall.
3. Find the amount of water trapped to the right of the right-most wall of height H.  The amount of water
   trapped by a given wall in this part will be the difference between the maximum heighted wall to its left 
   (including itself) and the height of the wall.
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int left_max_wall_index = 0; //index of the left-most wall of height H.
        int right_max_wall_index = 0; //index of the right-most wall of height H.
        for(int i = 0; i < height.size(); i++){
            if(height[i] >= height[right_max_wall_index]){
                right_max_wall_index = i;
            }
        }
        for(int i = 0; i < height.size(); i++){
            if(height[i] == height[right_max_wall_index]){
                left_max_wall_index = i;
                break;
            }
        }
        int rain_water_level = 0;
        int max_wall_so_far = 0;
        
        for(int i = 0; i < left_max_wall_index; i++){
            if(height[i] > max_wall_so_far){
                max_wall_so_far = height[i];
            }
            rain_water_level += max_wall_so_far - height[i];
        }
        
        for(int i = left_max_wall_index; i < right_max_wall_index; i++){
            rain_water_level += height[left_max_wall_index] - height[i];
        }
        
        max_wall_so_far = 0;
        
        for(int i = height.size()-1; i > right_max_wall_index; i--){
            if(height[i] > max_wall_so_far){
                max_wall_so_far = height[i];
            }
            rain_water_level +=  max_wall_so_far - height[i];
        }
        
        return rain_water_level;
    }
};