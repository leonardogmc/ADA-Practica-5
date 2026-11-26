#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// 1. Recursividad Ingenua: O(C^M)
int cambioRecursivo(int monto, const vector<int>& monedas) {
    if (monto == 0) return 0;
    if (monto < 0) return INF;

    int minMonedas = INF;
    for (int c : monedas) {
        if (monto >= c) {
            int res = cambioRecursivo(monto - c, monedas);
            if (res != INF) minMonedas = min(minMonedas, 1 + res);
        }
    }
    return minMonedas;
}

// 2. Memoizacion (Top-Down): O(M * C)
int cambioMemoAux(int monto, const vector<int>& monedas, vector<int>& memo) {
    if (monto == 0) return 0;
    if (monto < 0) return INF;
    if (memo[monto] != -1) return memo[monto];

    int minMonedas = INF;
    for (int c : monedas) {
        if (monto >= c) {
            int res = cambioMemoAux(monto - c, monedas, memo);
            if (res != INF) minMonedas = min(minMonedas, 1 + res);
        }
    }
    return memo[monto] = minMonedas;
}

int cambioMemoizacion(int monto, const vector<int>& monedas) {
    if (monto <= 0) return 0;
    vector<int> memo(monto + 1, -1);
    int res = cambioMemoAux(monto, monedas, memo);
    return (res >= INF) ? -1 : res;
}

// 3. Tabulacion (Bottom-Up): O(M * C)
pair<int, vector<int>> cambioTabulacion(int monto, const vector<int>& monedas) {
    if (monto <= 0) return {0, {}};

    vector<int> dp(monto + 1, INF);
    vector<int> primeraMoneda(monto + 1, -1);
    dp[0] = 0;

    for (int m = 1; m <= monto; ++m) {
        for (int c : monedas) {
            if (m >= c && dp[m - c] != INF) {
                if (dp[m - c] + 1 < dp[m]) {
                    dp[m] = dp[m - c] + 1;
                    primeraMoneda[m] = c;
                }
            }
        }
    }

    if (dp[monto] >= INF) return {-1, {}};

    vector<int> monedasUsadas;
    int actual = monto;
    while (actual > 0) {
        int c = primeraMoneda[actual];
        monedasUsadas.push_back(c);
        actual -= c;
    }
    return {dp[monto], monedasUsadas};
}

int main() {
    vector<int> monedas = {1, 3, 4};
    int monto = 6;

    cout << "--- CAMBIO DE MONEDAS ---\n";
    cout << "Recursivo:   " << cambioRecursivo(monto, monedas) << "\n";
    cout << "Memoizacion: " << cambioMemoizacion(monto, monedas) << "\n";

    auto tab = cambioTabulacion(monto, monedas);
    cout << "Tabulacion:  " << tab.first << "\n";
    cout << "Monedas usadas: ";
    for (int c : tab.second) cout << c << " ";
    cout << "\n";

    return 0;
}