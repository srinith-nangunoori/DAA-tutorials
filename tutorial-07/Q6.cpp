#include <iostream>
#include <algorithm>
using namespace std;

class TSPSolver {
public:
    int n;  
    vector<vector<int>> cost;  

    TSPSolver(int n) : n(n) {
        cost.assign(n, vector<int>(n));
    }

    struct Node {
        vector<vector<int>> reducedMatrix;
        vector<int> path;
        int cost;
        int vertex;
        int level;

        bool operator>(const Node& other) const {
            return cost > other.cost;
        }
    };

    // Reduce matrix and return the reduction cost
    int reduceMatrix(vector<vector<int>>& mat) {
        int reductionCost = 0;

        // Row reduction
        for (int i = 0; i < n; i++) {
            int rowMin = INT_MAX;
            for (int j = 0; j < n; j++)
                if (mat[i][j] >= 0) rowMin = min(rowMin, mat[i][j]);

            if (rowMin == INT_MAX || rowMin == 0) continue;

            reductionCost += rowMin;
            for (int j = 0; j < n; j++)
                if (mat[i][j] >= 0) mat[i][j] -= rowMin;
        }

        // Column reduction
        for (int j = 0; j < n; j++) {
            int colMin = INT_MAX;
            for (int i = 0; i < n; i++)
                if (mat[i][j] >= 0) colMin = min(colMin, mat[i][j]);

            if (colMin == INT_MAX || colMin == 0) continue;

            reductionCost += colMin;
            for (int i = 0; i < n; i++)
                if (mat[i][j] >= 0) mat[i][j] -= colMin;
        }

        return reductionCost;
    }

    // Create a child node
    Node createChild(const Node& parent, int nextCity) {
        Node child;
        child.reducedMatrix = parent.reducedMatrix;
        child.path = parent.path;
        child.path.push_back(nextCity);
        child.level = parent.level + 1;
        child.vertex = nextCity;

        // Invalidate row of current city and column of next city
        for (int j = 0; j < n; j++)
            child.reducedMatrix[parent.vertex][j] = -1;

        for (int i = 0; i < n; i++)
            child.reducedMatrix[i][nextCity] = -1;

        // Prevent returning too early
        child.reducedMatrix[nextCity][0] = -1;

        int addedCost = parent.reducedMatrix[parent.vertex][nextCity];
        int reductionCost = reduceMatrix(child.reducedMatrix);

        child.cost = parent.cost + addedCost + reductionCost;
        return child;
    }

    // Solve TSP
    void solve() {
        priority_queue<Node, vector<Node>, greater<Node>> pq;

        // Initial root node
        Node root;
        root.path = {0};
        root.level = 0;
        root.vertex = 0;
        root.reducedMatrix = cost;
        root.cost = reduceMatrix(root.reducedMatrix);

        pq.push(root);
        int nodesExpanded = 0;

        Node bestNode;

        while (!pq.empty()) {
            Node curr = pq.top();
            pq.pop();
            nodesExpanded++;

            if (curr.level == n - 1) {
                bestNode = curr;
                break;
            }

            for (int next = 0; next < n; next++) {
                if (curr.reducedMatrix[curr.vertex][next] != -1) {
                    Node child = createChild(curr, next);
                    pq.push(child);
                }
            }
        }

        // Build final tour
        vector<int> tour = bestNode.path;
        tour.push_back(0);

        cout << "\nOptimal Tour: ";
        for (int x : tour) cout << char('A' + x) << " ";
        cout << "\nTotal Cost: " << bestNode.cost;
        cout << "\nNodes Expanded: " << nodesExpanded << "\n";
    }
};

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    TSPSolver solver(n);
    cout << "Enter cost matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> solver.cost[i][j];
    solver.solve();
    return 0;
}



// why this thing actually work :
/*
	1.	Matrix reduction gives a true minimum remaining cost.
	2.	Choosing edges increases the bound by the extra cost + new reduction.
	3.	Priority queue ensures we explore the best possibilities first.
	4.	Bounding eliminates nodes whose lower bound already exceeds the current best tour.
*/