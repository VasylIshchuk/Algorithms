#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <iomanip>

using namespace std;

struct Point {
    int x, y;

    Point() {}

    Point(int x, int y) : x(x), y(y) {}
};

Point STARTING_POINT;
int COLLINEAR = 0;
int CLOCKWISE = -1;
int COUNTERCLOCKWISE = 1;


void magic_lines();

vector<Point> algorithmGrahamScan(vector<Point> &points);

int findIndexBottommostPoint(vector<Point> &points);

bool isLowerY(const Point &candidate, const Point &current_min);

bool isLeftOfAtSameY(const Point &candidate, const Point &current_min);

bool compare(Point &firstPoint, Point &secondPoint);

int determineTurnDirection(Point &firstPoint, Point &secondPoint, Point &thirdPoint);

int calculateSquaredDistance(Point &firstPoint, Point &secondPoint);

vector<Point> buildConvexHull(vector<Point> &points);

double calculateAreaUsingShoelace(vector<Point> &points);

int main() {
    magic_lines();

    int count_points;
    cin >> count_points;

    vector<Point> points;
    for (int i = 0; i < count_points; ++i) {
        int x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    vector<Point> hull = algorithmGrahamScan(points);

    double result = calculateAreaUsingShoelace(hull);
    cout << fixed << setprecision(3) << result;

    return 0;
}

void magic_lines() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}

vector<Point> algorithmGrahamScan(vector<Point> &points) {
    if (points.size() < 3) return {};

    int min_point_index = findIndexBottommostPoint(points);
    swap(points[0], points[min_point_index]);

    STARTING_POINT = points[0];
    sort(points.begin() + 1, points.end(), compare);

    return buildConvexHull(points);
}

int findIndexBottommostPoint(vector<Point> &points) {
    int min_point_index = 0;
    for (int i = 1; i < points.size(); ++i) {
        Point candidate = points[i];
        Point current_min = points[min_point_index];

        if (isLowerY(candidate, current_min) || isLeftOfAtSameY(candidate, current_min)) min_point_index = i;
    }
    return min_point_index;
}

bool isLowerY(const Point &candidate, const Point &current_min) {
    return (candidate.y < current_min.y);
}

bool isLeftOfAtSameY(const Point &candidate, const Point &current_min) {
    return (candidate.y == current_min.y) && (candidate.x < current_min.x);
}

bool compare(Point &firstPoint, Point &secondPoint) {
    int direction = determineTurnDirection(STARTING_POINT, firstPoint, secondPoint);
    if (direction == COLLINEAR) {
        int distance_to_first_point = calculateSquaredDistance(STARTING_POINT, firstPoint);
        int distance_to_second_point = calculateSquaredDistance(STARTING_POINT, secondPoint);
        return distance_to_first_point < distance_to_second_point;
    }

    return direction == COUNTERCLOCKWISE;
}

int determineTurnDirection(Point &firstPoint, Point &secondPoint, Point &thirdPoint) {
    int crossProduct = (secondPoint.x - firstPoint.x) * (thirdPoint.y - firstPoint.y) -
                       (secondPoint.y - firstPoint.y) * (thirdPoint.x - firstPoint.x);
    if (crossProduct == 0) return COLLINEAR;
    return (crossProduct > 0) ? COUNTERCLOCKWISE : CLOCKWISE;
}

int calculateSquaredDistance(Point &firstPoint, Point &secondPoint) {
    int dx = firstPoint.x - secondPoint.x;
    int dy = firstPoint.y - secondPoint.y;
    return dx * dx + dy * dy;
}

/*
    Why without the square root?
    Because in many algorithms (e.g., sorting points by angle and distance), it's not necessary to know the exact distance —
    it's enough to know which point is closer. And the square root is a costly operation, so it's often skipped.
 */

vector<Point> buildConvexHull(vector<Point> &points) {
    stack<Point> stack;
    stack.push(points[0]);
    stack.push(points[1]);
    stack.push(points[2]);

    for (int i = 3; i < points.size(); ++i) {
        while (stack.size() >= 2) {
            Point top = stack.top();
            stack.pop();

            Point nextToTop = stack.top();
            stack.push(top);

            if (determineTurnDirection(nextToTop, top, points[i]) != COUNTERCLOCKWISE) stack.pop();
            else break;
        }
        stack.push(points[i]);
    }

    vector<Point> hull;
    while (!stack.empty()) {
        hull.push_back(stack.top());
        stack.pop();
    }

    return hull;
}

double calculateAreaUsingShoelace(vector<Point> &points) {
    int count_points = points.size();
    double area = 0.0;

    for (int i = 0; i < count_points; ++i) {
        int j = (i + 1) % count_points;
        area += points[i].x * points[j].y - points[j].x * points[i].y;
    }

    return abs(area / 2.0);
}




