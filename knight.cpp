#include <array>
#include <algorithm>
#include <iostream>

using cell = std::pair<int, int>;

static const int move_x[8] = {+2, +2, +1, -1, -2, -2, +1, -1};
static const int move_y[8] = {+1, -1, +2, +2, +1, -1, -2, -2};
static bool board[8][8];
std::array<cell, 64> path;

bool valid_cell(cell c) {
    if ((c.first < 1 || c.second < 1) || (c.first > 8 || c.second > 8))
        return false;
    return true;
}

int count_available_neighbors(cell c) {
    if (!valid_cell(c) || board[c.first][c.second])
        return 0;
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int x = c.first + move_x[i];
        int y = c.second + move_y[i];
        if (valid_cell({x, y}) && !board[x][y])
            ++count;
    }
    return count;
}

void backtrack(cell c, int d) {
    if (!d) {
        std::cerr << "FOUND!\n";
        for (auto c: path)
            std::cerr << "(" << c.first << ", " << c.second << "), ";
        std::cerr << '\n';
    }
    std::array<std::pair<int, cell>, 8> neighbor;
    for (int i = 0; i < 8; ++i) {
        int x = c.first + move_x[i];
        int y = c.second + move_y[i];
        neighbor[i] = {count_available_neighbors({x, y}), {x, y}};
    }
    std::sort(begin(neighbor), end(neighbor));
    for (auto e: neighbor) {
        if (valid_cell(e.second) && !board[e.second.first][e.second.second]) {
            int x = e.second.first;
            int y = e.second.second;
            board[x][y] = true;
            path[d - 1] = {x, y};
            backtrack({x, y}, d - 1);
            board[x][y] = false;
            path[d - 1] = {0, 0};
        }
    }
}

int main() {
    path[63] = {1, 1};
    board[1][1] = true;
    backtrack({1, 1}, 63);
    return 0;
}
