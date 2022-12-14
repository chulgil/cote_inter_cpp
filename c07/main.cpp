#include <bits/stdc++.h>
using namespace std;

class Solution {
  protected:
    vector<vector<int>> memo;

  public:
    int minDistance(string word1, string word2) {
        memo.resize(word1.size() + 1, vector<int>(word2.size() + 1, -1));
        return distTopDownDp(word1, word2);
    }

  private:
    int distBottomUp(string &word1, string &word2, int m, int n) {
        if (m == 0 || n == 0) {
            return m == 0 ? n : m;
        }

        int cost;
        if (word1[m - 1] == word2[n - 1]) {
            cost = 0;
        } else {
            cost = 1;
        }

        return min({
            distBottomUp(word1, word2, m, n - 1) + 1,       // Insert
            distBottomUp(word1, word2, m - 1, n) + 1,       // Delete
            distBottomUp(word1, word2, m - 1, n - 1) + cost // Transpose
        });
    }

    int distBottomUpDp(string &word1, string &word2, int m, int n) {
        if (m == 0 || n == 0) {
            return m == 0 ? n : m;
        }

        if (memo[m][n] != -1) {
            return memo[m][n];
        }

        if (word1[m] == word2[n]) {
            memo[m][n] = distBottomUpDp(word1, word2, m - 1, n - 1);
        } else {
            memo[m][n] =
                1 + min({
                        distBottomUp(word1, word2, m, n - 1),    // Insert
                        distBottomUp(word1, word2, m - 1, n),    // Delete
                        distBottomUp(word1, word2, m - 1, n - 1) // Transpose
                    });
        }
        return memo[m][n];
    }

    int distTopDownDp(string word1, string word2) {
        int len1 = word1.size();
        int len2 = word2.size();
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, -1));

        for (int i = 1; i <= len1; i++) {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= len2; i++) {
            dp[0][i] = 0;
        }

        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({
                                       dp[i][j - 1],    // Insert
                                       dp[i - 1][j],    // Delete
                                       dp[i - 1][j - 1] // Transpose
                                   });
                }
            }
        }

        return dp[len1][len2];
    }
};

int main(void) {
    // https://velog.io/@hidaehyunlee/CPP-01-????????????-???????????????-????????????-new-delete
    // ????????????
    Solution sol;
    string word1;
    string word2;
    cin >> word1 >> word2;
    int solved = sol.minDistance(word1, word2);
    cout << solved << '\n';
    return 0;
}