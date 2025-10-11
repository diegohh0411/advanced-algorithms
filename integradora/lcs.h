#ifndef LCS_MANAGER
#define LCS_MANAGER

#include <iostream>
#include "common.h"

str LongestCommontSubstring(const str& s1, const str& s2) {
    int n = s1.length();
    int m = s2.length();

    vec<intVec> dp(n + 1, intVec(m + 1, 0));

    int maxLen = 0;
    int endPos = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endPos = i;
                }
            }
        }
    }

    return s1.substr(endPos - maxLen, maxLen);
}

void LcsManager(traVec trs) {
    std::cout << "Los Substring mas largos son:" << std::endl;

    std::cout << "T1-T2 ==> " << LongestCommontSubstring(trs[0].content, trs[1].content) << std::endl;
    std::cout << "T1-T3 ==> " << LongestCommontSubstring(trs[0].content, trs[2].content) << std::endl;
    std::cout << "T2-T3 ==> " << LongestCommontSubstring(trs[1].content, trs[2].content) << std::endl;
}

#endif