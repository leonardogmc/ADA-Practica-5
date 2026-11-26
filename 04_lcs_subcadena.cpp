#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Recursividad Ingenua: O(2^(N+M))
int lcsSufijoRecursivo(int i, int j, const string& s1, const string& s2, int& maxGlobal) {
    if (i == 0 || j == 0) return 0;
    int sufijoActual = 0;
    if (s1[i - 1] == s2[j - 1]) {
        sufijoActual = 1 + lcsSufijoRecursivo(i - 1, j - 1, s1, s2, maxGlobal);
        maxGlobal = max(maxGlobal, sufijoActual);
    }
    lcsSufijoRecursivo(i - 1, j, s1, s2, maxGlobal);
    lcsSufijoRecursivo(i, j - 1, s1, s2, maxGlobal);
    return sufijoActual;
}

int lcsSubcadenaRecursivo(const string& s1, const string& s2) {
    int maxGlobal = 0;
    lcsSufijoRecursivo(s1.size(), s2.size(), s1, s2, maxGlobal);
    return maxGlobal;
}

// 2. Memoizacion (Top-Down): O(N * M)
int lcsSufijoMemo(int i, int j, const string& s1, const string& s2, vector<vector<int>>& memo, int& maxGlobal) {
    if (i == 0 || j == 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    int sufijoActual = 0;
    if (s1[i - 1] == s2[j - 1]) {
        sufijoActual = 1 + lcsSufijoMemo(i - 1, j - 1, s1, s2, memo, maxGlobal);
        maxGlobal = max(maxGlobal, sufijoActual);
    }
    lcsSufijoMemo(i - 1, j, s1, s2, memo, maxGlobal);
    lcsSufijoMemo(i, j - 1, s1, s2, memo, maxGlobal);
    return memo[i][j] = sufijoActual;
}

int lcsSubcadenaMemoizacion(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
    int maxGlobal = 0;
    lcsSufijoMemo(n, m, s1, s2, memo, maxGlobal);
    return maxGlobal;
}

// 3. Tabulacion (Bottom-Up): O(N * M)
pair<int, string> lcsSubcadenaTabulacion(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxLen = 0;
    int endIdxS1 = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endIdxS1 = i;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    string subcadena = (maxLen > 0) ? s1.substr(endIdxS1 - maxLen, maxLen) : "";
    return {maxLen, subcadena};
}

int main() {
    string s1 = "ABAZDC";
    string s2 = "BACBAD";

    cout << "--- SUBCADENA COMUN MAS LARGA (LCS) ---\n";
    cout << "Recursivo:   " << lcsSubcadenaRecursivo(s1, s2) << "\n";
    cout << "Memoizacion: " << lcsSubcadenaMemoizacion(s1, s2) << "\n";

    auto tab = lcsSubcadenaTabulacion(s1, s2);
    cout << "Tabulacion:  " << tab.first << "\n";
    cout << "Cadena:      \"" << tab.second << "\"\n";

    return 0;
}