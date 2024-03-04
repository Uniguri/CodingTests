class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hm;
        vector<int> ret(2);
        
        for(int i = 0; i < nums.size(); i++)
        {
            if(hm.find(target-nums[i]) == hm.end())
            {
                hm[nums[i]] = i;
            }
            else
            {
                ret[1] = i;
                ret[0] = hm[target-nums[i]];
                
                return ret;
            }
        }
        
        return ret;
    }
};