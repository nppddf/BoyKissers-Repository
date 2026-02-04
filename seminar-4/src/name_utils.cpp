

void solve(int n, int m, vector<vector<int>>& matrix) {
    vector<vector<int>> prefix(n + 1, vector<int> (m, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            prefix[i][j] = prefix[i - 1][j] + matrix[i - 1][j];
        }
    }
    int ans = 0;
    for (int top_row = 0; top_row < n; ++top_row) {
        vector<int> sum_coloms(m);
        for (int buttom_row = top_row; buttom_row < n; ++buttom_row) {
             for (int i = 0; i < m; ++i) {
                 sum_coloms[i] = prefix[buttom_row + 1][i] - prefix[top_row][i];
             }
            int lhs = 0, rhs = 0;
            int cur_sum = 0;
            while (rhs < m) {
                cur_sum += sum_coloms[rhs];
                rhs++;
                ans = max(ans, cur_sum);
                while (lhs < rhs && cur_sum < 0) {
                    lhs++;
                    cur_sum -= sum_coloms[lhs];
                    ans = max(ans, cur_sum);
                }
            }
        }
    }
}
