#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// ========================================================
// 1. PLAIN BACKTRACKING SOLVER
// ========================================================
void solvePlain(int row, int n, vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2, 
                vector<int>& board, long long& solutions, long long& nodes) {
    nodes++; // Đếm mỗi node (lời gọi hàm) được khảo sát

    if (row == n) {
        solutions++;
        // Trực quan hóa nghiệm đầu tiên nếu N = 8
        if (n == 8 && solutions == 1) {
            cout << "\n[Visualizing 8x8 Board - Nghiem dau tien]:\n";
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    cout << (board[r] == c ? "Q " : ". ");
                }
                cout << "\n";
            }
            cout << "\n";
        }
        return;
    }

    for (int col = 0; col < n; col++) {
        int d1 = row - col + n - 1;
        int d2 = row + col;

        if (!cols[col] && !diag1[d1] && !diag2[d2]) {
            board[row] = col;
            cols[col] = diag1[d1] = diag2[d2] = true;

            solvePlain(row + 1, n, cols, diag1, diag2, board, solutions, nodes);

            // Quay lui (Backtrack)
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
    }
}

// ========================================================
// 2. BITMASK BACKTRACKING SOLVER (Knuth's Algorithm)
// ========================================================
void solveBitmask(int row, int ld, int rd, int colmask, int n, long long& solutions, long long& nodes) {
    nodes++; // Đếm mỗi node được khảo sát

    int all_ones = (1 << n) - 1;
    if (colmask == all_ones) {
        solutions++;
        return;
    }

    // Các vị trí hợp lệ còn trống
    int available = ~(colmask | ld | rd) & all_ones;

    while (available) {
        // Lấy bit 1 thấp nhất (isolated low-bit)
        int bit = available & -available;
        available -= bit;

        solveBitmask(row + 1, (ld | bit) << 1, (rd | bit) >> 1, colmask | bit, n, solutions, nodes);
    }
}

// ========================================================
// 3. MAIN BENCHMARK PIPELINE
// ========================================================
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> test_sizes = {8, 10, 12, 14};

    cout << "=========================================================================\n";
    cout << "          N-QUEENS BENCHMARK: PLAIN VS BITMASK (C++ VERSION)             \n";
    cout << "=========================================================================\n\n";

    for (int n : test_sizes) {
        cout << ">>> KHAO SAT VOI N = " << n << " <<<\n";

        // 1. Chạy Plain Backtracking
        long long plain_sols = 0, plain_nodes = 0;
        vector<bool> cols(n, false), diag1(2 * n, false), diag2(2 * n, false);
        vector<int> board(n, 0);

        auto t1 = high_resolution_clock::now();
        solvePlain(0, n, cols, diag1, diag2, board, plain_sols, plain_nodes);
        auto t2 = high_resolution_clock::now();
        double time_plain = duration<double>(t2 - t1).count();

        cout << "  [Plain Backtracking]\n"
             << "    - So nghiem tim duoc : " << plain_sols << "\n"
             << "    - So node khao sat   : " << plain_nodes << "\n"
             << "    - Thoi gian          : " << fixed << setprecision(6) << time_plain << " s\n";

        // 2. Chạy Bitmask Backtracking
        long long bitmask_sols = 0, bitmask_nodes = 0;

        auto t3 = high_resolution_clock::now();
        solveBitmask(0, 0, 0, 0, n, bitmask_sols, bitmask_nodes);
        auto t4 = high_resolution_clock::now();
        double time_bitmask = duration<double>(t4 - t3).count();

        cout << "  [Bitmask Backtracking (Optimized)]\n"
             << "    - So nghiem tim duoc : " << bitmask_sols << "\n"
             << "    - So node khao sat   : " << bitmask_nodes << "\n"
             << "    - Thoi gian          : " << fixed << setprecision(6) << time_bitmask << " s\n";
        // Đánh giá tỷ lệ tăng tốc
        if (time_bitmask > 1e-6) {
            cout << "  => Speedup (Thoi gian) : " << setprecision(2) << (time_plain / time_bitmask) << "x nhanh hon\n";
        } else {
            cout << "  => Speedup (Thoi gian) : Qua nhanh de do chinh xac\n";
        }
        cout << "-------------------------------------------------------------------------\n\n";
    }

    return 0;
}