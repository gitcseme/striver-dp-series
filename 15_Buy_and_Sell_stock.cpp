class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minBuy = prices[0];
        int maxProfit = 0;
        for (int i = 0, n = prices.size(); i < n; ++i) {
            if (minBuy > prices[i]) {
                minBuy = prices[i];
            }

            maxProfit = max(maxProfit, prices[i] - minBuy);
        }

        return maxProfit;
    }
};
