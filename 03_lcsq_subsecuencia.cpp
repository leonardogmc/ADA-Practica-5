#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Recursividad Ingenua: O(2^(N+M))
int lcsqRecursivo(int i, int j, const string& s1, const string& s2) {
    if (i == 0 || j == 0) return 0;
    if (s1[i - 1] == s2[j - 1]) {
        return 1 + lcsqRecursivo(i - 1, j - 1, s1, s2);
    }
    return max(lcsqRecursivo(i - 1, j, s1, s2), lcsqRecursivo(i, j - 1, s1, s2));
}

// 2. Memoizacion (Top-Down): O(N * M)
int lcsqMemoAux(int i, int j, const string& s1, const string& s2, vector<vector<int>>& memo) {
    if (i == 0 || j == 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    if (s1[i - 1] == s2[j - 1]) {
        return memo[i][j] = 1 + lcsqMemoAux(i - 1, j - 1, s1, s2, memo);
    }
    return memo[i][j] = max(lcsqMemoAux(i - 1, j, s1, s2, memo), lcsqMemoAux(i, j - 1, s1, s2, memo));
}

int lcsqMemoizacion(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
    return lcsqMemoAux(n, m, s1, s2, memo);
}

// 3. Tabulacion (Bottom-Up): O(N * M)
pair<int, string> lcsqTabulacion(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    string res = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            res.push_back(s1[i - 1]);
            i--; j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(res.begin(), res.end());
    return {dp[n][m], res};
}

int main() {
    string s1 = "ABAZDC";
    string s2 = "BACBAD";

    cout << "--- SUBSECUENCIA COMUN MAS LARGA (LCSq) ---\n";
    cout << "Recursivo:   " << lcsqRecursivo(s1.size(), s2.size(), s1, s2) << "\n";
    cout << "Memoizacion: " << lcsqMemoizacion(s1, s2) << "\n";

    auto tab = lcsqTabulacion(s1, s2);
    cout << "Tabulacion:  " << tab.first << "\n";
    cout << "Cadena:      \"" << tab.second << "\"\n";

    return 0;
}