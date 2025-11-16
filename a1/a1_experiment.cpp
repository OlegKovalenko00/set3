#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

struct box_area {
    long double x_min;
    long double x_max;
    long double y_min;
    long double y_max;
    long double area;
};

bool inside_all(long double x, long double y) {
    long double x1 = 1.0L;
    long double y1 = 1.0L;
    long double r1 = 1.0L;

    long double x2 = 1.5L;
    long double y2 = 2.0L;
    long double r2 = std::sqrt(5.0L) / 2.0L;

    long double x3 = 2.0L;
    long double y3 = 1.5L;
    long double r3 = std::sqrt(5.0L) / 2.0L;

    long double dx1 = x - x1;
    long double dy1 = y - y1;
    if (dx1 * dx1 + dy1 * dy1 > r1 * r1) return false;

    long double dx2 = x - x2;
    long double dy2 = y - y2;
    if (dx2 * dx2 + dy2 * dy2 > r2 * r2) return false;

    long double dx3 = x - x3;
    long double dy3 = y - y3;
    if (dx3 * dx3 + dy3 * dy3 > r3 * r3) return false;

    return true;
}

long double monte_carlo_area(const box_area &rect, int n_points, std::mt19937_64 &rng) {
    std::uniform_real_distribution<long double> dist_x(rect.x_min, rect.x_max);
    std::uniform_real_distribution<long double> dist_y(rect.y_min, rect.y_max);

    int inside_cnt = 0;
    for (int i = 0; i < n_points; ++i) {
        long double x = dist_x(rng);
        long double y = dist_y(rng);
        if (inside_all(x, y)) {
            ++inside_cnt;
        }
    }

    long double ratio = static_cast<long double>(inside_cnt) /
                        static_cast<long double>(n_points);
    return ratio * rect.area;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long double exact_area =
        0.25L * acosl(-1.0L) + 1.25L * asinl(0.8L) - 1.0L;

    box_area wide_rect;
    wide_rect.x_min = 0.0L;
    wide_rect.x_max = 3.0L;
    wide_rect.y_min = 0.0L;
    wide_rect.y_max = 3.0L;
    wide_rect.area = (wide_rect.x_max - wide_rect.x_min) *
                     (wide_rect.y_max - wide_rect.y_min);

    box_area narrow_rect;
    narrow_rect.x_min = 0.882L;
    narrow_rect.x_max = 2.0L;
    narrow_rect.y_min = 0.882L;
    narrow_rect.y_max = 2.0L;
    narrow_rect.area = (narrow_rect.x_max - narrow_rect.x_min) *
                    (narrow_rect.y_max - narrow_rect.y_min);


    std::mt19937_64 rng(20251113ULL);

    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(10);

    for (int n_points = 100; n_points <= 100000; n_points += 500) {
        long double wide_est = monte_carlo_area(wide_rect, n_points, rng);
        long double narrow_est = monte_carlo_area(narrow_rect, n_points, rng);

        long double wide_rel_err =
            fabsl(wide_est - exact_area) / exact_area;
        long double narrow_rel_err =
            fabsl(narrow_est - exact_area) / exact_area;

        std::cout << n_points << ' '
                  << wide_est << ' '
                  << narrow_est << ' '
                  << wide_rel_err << ' '
                  << narrow_rel_err << std::endl;
    }
}
