#include <iostream>
#include <vector>
#include <string>

std::string longestCommonSubstring(const std::string& s1, const std::string& s2) {
    int n = s1.length();
    int m = s2.length();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));
    int maxLength = 0;
    int endIndex = 0;

    std::cout << "Dynamic Programming Table:" << std::endl;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            
            if (i > 0 && j > 0 && s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;
                }
            } else {
                dp[i][j] = 0;
            }
        }

        for (int j = 0; j <= m; ++j) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }

    
    std::string result = s1.substr(endIndex - maxLength + 1, maxLength);
    return result;
}

int main() {
    std::string s1, s2;

    
    std::cout << "Enter the first string: ";
    std::cin >> s1;
    std::cout << "Enter the second string: ";
    std::cin >> s2;

    
    std::string result = longestCommonSubstring(s1, s2);
    std::cout << "\nLongest Common Substring: " << result << std::endl;

    return 0;
}