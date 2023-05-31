#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#define ll long long

int findMaxConsecutiveOnes(const std::vector<int>& nums) {
    int ans = 0, s = 0;
    for (int i = 0; i < (int) nums.size(); i++) {
        if (nums[i] == 0) {// assign maximum value when first new 0 is encountered
            ans = std::max(ans, s);
            s = 0;
        }
        else s++;  //to keep track of consecutive 1's
    }
    return std::max(ans, s);
}

int maxProductPath(const std::vector<std::vector<int>>& grid) {
    int n = (int)grid.size();
        int m = (int)grid[0].size();
    int mod = 1000000007;

    std::vector<std::vector<ll>>dp1(n, std::vector<ll>(m)), dp2(n, std::vector<ll>(m));
    dp1[0][0] = dp2[0][0] = grid[0][0];

    // initialize left sides
    for (int i = 1; i < n; i++) {
        dp2[i][0] = dp1[i][0] = dp1[i - 1][0] * grid[i][0];
    }

    // initialize top sides
    for (int j = 1; j < m; j++) {
        dp2[0][j] = dp1[0][j] = dp1[0][j - 1] * grid[0][j];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (grid[i][j] < 0) { // new maximum product= minimum product * negative number 
                dp1[i][j] = std::min(dp2[i - 1][j], dp2[i][j - 1]) * grid[i][j];
                dp2[i][j] = std::max(dp1[i - 1][j], dp1[i][j - 1]) * grid[i][j];
            }
            else { // new maximum product= maximum product * positive number 
                dp1[i][j] = std::max(dp1[i - 1][j], dp1[i][j - 1]) * grid[i][j];
                dp2[i][j] = std::min(dp2[i - 1][j], dp2[i][j - 1]) * grid[i][j];
            }
        }
    }

    int ans = dp1[n - 1][m - 1] % mod;
    return ans < 0 ? -1 : ans;
}

bool val(int i, int j, int n, int m) {
    if (i >= 0 && j >= 0 && i < n && j < m) return true;
    return false;
}

// Four Directional Co-ordinates
std::vector<int>dist = { -1,0,1,0,-1 };
bool solve2(const std::vector<std::vector<int>>& v, const std::vector<std::vector<int>>& dis, int t, int n, int m) {
    std::vector<std::vector<int>>vis(n, std::vector<int>(m, 0));
    vis[0][0] = 1;
    std::queue<std::vector<int>>q;
    q.push({ 0,0,t });
    while (!q.empty()) {
        auto x = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int i = x[0] + dist[k], j = x[1] + dist[k + 1];
            if (!val(i, j, n, m) || v[i][j] == 2 || vis[i][j]) continue;
            if (i == n - 1 && j == m - 1 && dis[i][j] >= x[2] + 1) return true;
            if (dis[i][j] <= x[2] + 1) continue;
            vis[i][j] = 1;
            q.push({ i,j,x[2] + 1 });
        }
    }
    return false;
}
int maximumMinutes(const std::vector<std::vector<int>>& v) {
    int n = (int)v.size();
    int m = (int)v[0].size();
    std::vector<std::vector<int>>dis(n, std::vector<int>(m, INT_MAX));

    // Here we use BFS to calculate the minimum time to reach cell
   // (i,j) from all the initially given fire-points.
    std::queue<std::vector<int>>q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j] == 1) {
                q.push({ i,j,0 });
                dis[i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        auto x = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int i = x[0] + dist[k], j = x[1] + dist[k + 1];
            if (!val(i, j, n, m) || v[i][j] == 2 || dis[i][j] <= x[2] + 1) continue;
            dis[i][j] = x[2] + 1;
            q.push({ i,j,x[2] + 1 });
        }
    }
    int l = 0, r = 1000000000, ans = -1;

    // Binary Search on ans
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (solve2(v, dis, mid, n, m)) {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return ans;
}

int equalSubstring(const std::string &s, const std::string &t, int ma) {
    int i = 0, j = 0, ans = 0, sum = 0;

    // apply sliding window
    while (j < (int) s.size()) {

        // add the cost into sum
        sum += abs(s[j] - t[j]);

        // shrink the window from left to decrement the sum, to make it within range
        while (sum > ma) {
            sum -= abs(s[i] - t[i]);
            i++;
        }
        // update ans
        ans = std::max(ans, j - i + 1);
        j++;
    }
    return ans;
}

int swimInWater(const std::vector<std::vector<int>>& grid) {
    int n = (int) grid.size();
    int ans = std::max(grid[0][0], grid[n - 1][n - 1]);

    //declaring priority queue(min heap) 
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>>pq;

    pq.push({ ans,0,0 });
    std::vector<int>d = { -1,0,1,0,-1 };

    //visited vector of size n*n
    std::vector<std::vector<int>>vis(n, std::vector<int>(n, 0));
    vis[0][0] = 1;
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        ans = std::max(ans, cur[0]);
        std::queue<std::pair<int, int>>q;
        q.push({ cur[1],cur[2] });
        while (!q.empty()) {
            auto p = q.front();
            q.pop();

            // if we reach at the bottom right square then return ans
            if (p.first == n - 1 && p.second == n - 1) return ans;

            for (int i = 0; i < 4; i++) {
                int x = p.first + d[i], y = p.second + d[i + 1];
                if (x >= 0 && y >= 0 && x < n && y < n && vis[x][y] == 0) {
                    //next step
                    vis[x][y] = 1;
                    if (grid[x][y] <= ans) q.push({ x,y });
                    else pq.push({ grid[x][y],x,y });
                }
            }
        }
    }
    return -1;
}


int dp[72][5000];
int solve3(const std::vector<std::vector<int>>& v, int t, int s, int r, int n, int m) {
    //base case
    if (r == n) return abs(t - s);

    //if previously calculated, return it
    if (dp[r][s] != -1) return dp[r][s];
    int ma = INT_MAX;
    for (int c = 0; c < m; c++) {
        //checking all possible cases
        ma = std::min(ma, solve3(v, t, s + v[r][c], r + 1, n, m));

        // if difference==0, break
        if (ma == 0) break;
    }
    return dp[r][s] = ma;
}
int minimizeTheDifference(const std::vector<std::vector<int>>& mat, int t) {
    memset(dp, -1, (int)sizeof(dp));
    int n = (int)mat.size();
    int m = (int) mat[0].size();
    return solve3(mat, t, 0, 0, n, m);
}

int minInsertions(const std::string& s) {
    int n = (int)s.size();
    std::string s1 = s;
    reverse(s1.begin(), s1.end());  // S1 = rev(s) for LPS computation
    std::vector<std::vector<int>>dp(n + 1, std::vector<int>(n + 1));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) { // Generating LCS
            if (!i || !j) dp[i][j] = 0;
            else if (s[i - 1] == s1[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
            else dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }// Got LPS

    //minimum operation=n-LPS
    return n - dp[n][n];
}

int numDecodings(const std::string& s) {
    int n = (int)s.size();
    std::vector<int>dp(n + 1);
    for (int i = 0; i <= n; i++) dp[i] = 0;
    dp[0] = 1;
    dp[1] = 1;

    //If current element is 0, we simply return 0 as it is not possible to get a character using 0.
    if (s[0] == '0') return 0;

    for (int i = 2; i <= n; i++) {

        // Pick single
        if (s[i - 1] > '0') dp[i] = dp[i - 1];

        // Pick couple
        if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] < '7')) dp[i] += dp[i - 2];
    }
    return dp[n];

}

int main() {
    return 0;
}