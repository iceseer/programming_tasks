#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <assert.h>

using namespace std;
int num_areas(int rows, int columns, vector<int> data) {
    vector<int> entered(data.size(), 0);

    struct point {
        int x, y;
        explicit point(int __x, int __y) : x(__x), y(__y) { }
    };
    deque<point> indexes;

    int count = 0;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            if (entered[y*columns + x] == 0) {
                entered[y*columns + x] = 1;
                if (data[y*columns + x] == 1) {
                    ++count;

                    {
                        const int next_x = x + 1;
                        const int next_y = y + 1;
                        if (next_x < columns) {
                            assert(next_x < columns && y < rows);
                            indexes.emplace_back(next_x, y);
                        }
                        if (next_y < rows) {
                            assert(x < columns && next_y < rows);
                            indexes.emplace_back(x, next_y);
                        }
                    }

                    while (!indexes.empty()) {
                        auto const P = indexes.front(); indexes.pop_front();
                        if (entered[P.x + P.y * columns] == 0) {
                            entered[P.x + P.y * columns] = 1;

                            if (data[P.x + P.y * columns] == 1) {
                                const int next_x = P.x + 1;
                                const int prev_x = P.x - 1;
                                const int next_y = P.y + 1;
                                const int prev_y = P.y - 1;

                                if (next_x < columns) {
                                    assert(next_x < columns && P.y < rows);
                                    indexes.emplace_back(next_x, P.y);
                                }
                                if (next_y < rows) {
                                    assert(P.x < columns && next_y < rows);
                                    indexes.emplace_back(P.x, next_y);
                                }
                                if (prev_x >= 0) {
                                    assert(prev_x < columns && P.y < rows);
                                    indexes.emplace_back(prev_x, P.y);
                                }
                                if (prev_y >= 0) {
                                    assert(P.x < columns && prev_y < rows);
                                    indexes.emplace_back(P.x, prev_y);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}

int main()
{
    vector<int> areas =
    {
        1, 0, 0, 1, 1, 1, 1,
        1, 0, 1, 0, 0, 1, 0,
        1, 0, 0, 1, 0, 1, 1,
        1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1,
    };

    cout << "ANS: " << num_areas(6, 7, areas);
    return 0;
}
