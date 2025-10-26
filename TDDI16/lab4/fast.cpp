/*
 * fast < input.txt
 *
 * Compute and plot all line segments involving 4 points in input.txt
 */

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "point.h"
#include "window.h"

using namespace std;

int main(int argc, const char* argv[]) {
    WindowPtr window = create_window(argc, argv);
    if (!window)
        return 1;

    // The array of points
    vector<Point> points;

    // Read tolerance from cin
    double tolerance{};
    cin >> tolerance;

    // Read points from cin
    int N{};
    cin >> N;

    for (int i{0}; i < N; ++i) {
        double x{}, y{};
        cin >> x >> y;
        points.push_back(Point{x, y});
    }

    // draw points to screen all at once
    window->draw_points(points);

    auto begin = chrono::high_resolution_clock::now();

    for(auto& i : points)
    {
        vector<pair<Point, double>> sortedNodes;

        Point point(i.x, i.y);
        for(auto& j : points)
        {
            if (&i == &j)
                continue;
            double tmp = point.slopeTo(j);
            sortedNodes.push_back({j, tmp});
        }
        sort(sortedNodes.begin(), sortedNodes.end(),
        [](pair<Point, double> x, pair<Point, double> y)
        {
            return x.second < y.second;
        });
        for(size_t k {2}; k < sortedNodes.size(); k++){
            if (i.sameSlope(sortedNodes[k-2].first, sortedNodes[k].first, tolerance))
            {
                window->draw_line({i, sortedNodes[k-2].first, sortedNodes[k-1].first, sortedNodes[k].first});
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////
    // Draw any lines that you find in 'points' using the function 'window->draw_line'.
    /////////////////////////////////////////////////////////////////////////////

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // wait for user to terminate program
    window->run();

    return 0;
}
