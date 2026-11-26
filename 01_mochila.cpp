#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Recursividad Ingenua: O(2^N)
int mochilaRecursiva(int i, int W, const vector<int>& pesos, const vector<int>& valores) {
    if (i < 0 || W <= 0) return 0;
    if (pesos[i] > W) {
        return mochilaRecursiva(i - 1, W, pesos, valores);
    }
    int noIncluir = mochilaRecursiva(i - 1, W, pesos, valores);
    int incluir = valores[i] + mochilaRecursiva(i - 1, W - pesos[i], pesos, valores);
    return max(noIncluir, incluir);
}

// 2. Memoizacion (Top-Down): O(N * W)
int mochilaMemoAux(int i, int W, const vector<int>& pesos, const vector<int>& valores, vector<vector<int>>& memo) {
    if (i < 0 || W <= 0) return 0;
    if (memo[i][W] != -1) return memo[i][W];

    if (pesos[i] > W) {
        return memo[i][W] = mochilaMemoAux(i - 1, W, pesos, valores, memo);
    }
    int noIncluir = mochilaMemoAux(i - 1, W, pesos, valores, memo);
    int incluir = valores[i] + mochilaMemoAux(i - 1, W - pesos[i], pesos, valores, memo);
    return memo[i][W] = max(noIncluir, incluir);
}

int mochilaMemoizacion(int W, const vector<int>& pesos, const vector<int>& valores) {
    int n = pesos.size();
    if (n == 0 || W <= 0) return 0;
    vector<vector<int>> memo(n, vector<int>(W + 1, -1));
    return mochilaMemoAux(n - 1, W, pesos, valores, memo);
}

// 3. Tabulacion (Bottom-Up): O(N * W)
pair<int, vector<int>> mochilaTabulacion(int W, const vector<int>& pesos, const vector<int>& valores) {
    int n = pesos.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (pesos[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], valores[i - 1] + dp[i - 1][w - pesos[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    vector<int> seleccionados;
    int w_restante = W;
    for (int i = n; i > 0 && dp[i][w_restante] > 0; --i) {
        if (dp[i][w_restante] != dp[i - 1][w_restante]) {
            seleccionados.push_back(i - 1);
            w_restante -= pesos[i - 1];
        }
    }
    reverse(seleccionados.begin(), seleccionados.end());
    return {dp[n][W], seleccionados};
}

int main() {
    vector<int> pesos = {2, 3, 4, 5, 9};
    vector<int> valores = {3, 4, 5, 8, 10};
    int W = 10;
    int n = pesos.size();

    cout << "--- MOCHILA 0/1 ---\n";
    cout << "Recursivo:   " << mochilaRecursiva(n - 1, W, pesos, valores) << "\n";
    cout << "Memoizacion: " << mochilaMemoizacion(W, pesos, valores) << "\n";

    auto tab = mochilaTabulacion(W, pesos, valores);
    cout << "Tabulacion:  " << tab.first << "\n";
    cout << "Indices tomados: ";
    for (int idx : tab.second) cout << idx << " ";
    cout << "\n";

    return 0;
}