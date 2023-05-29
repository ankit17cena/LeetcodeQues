#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#define ll long long

// declare a map
std::unordered_map<std::string, int>mp;

bool solve1(const std::vector<int>& nums, int i, int n, int sum, int no) {
	// base cases
	if (no == 0) return sum == 0;
	if (i == n) return false;

	// to create a key
	std::string key = std::to_string(i) + "#" + std::to_string(no) + "#" + std::to_string(sum);

	// if we have already calculated
	if (mp.count(key)) return mp[key];

	// if nums[i]<=sum,then we will two options: either include or exclude
	// calculate the result and store in map
	if (nums[i] <= sum) {
		return mp[key] = solve1(nums, i + 1, n, sum - nums[i], no - 1) || solve1(nums, i + 1, n, sum, no);
	}
	else return mp[key] = solve1(nums, i + 1, n, sum, no);
}

bool splitArraySameAverage(const std::vector<int>& nums) {
	int n = (int)nums.size();

	// find the total sum
	int sum = 0;
	for (int i = 0; i < n; i++) sum += nums[i];

	// check for every possible size of subset from 1 to n-1
	for (int i = 1; i < n; i++) {
		if ((sum * i) % n == 0) {

			// To check if there is any subset of i that has sum of sum_needed
			int sum_needed = (sum * i) / n;
			if (solve1(nums, 0, n, sum_needed, i))
				return true;
		}
	}
	return false;
}

int solve2(int n, std::unordered_map<int, int>& map) {
	// base cases
	if (n < 3) return n;

	//if already calculated, return value
	if (map.find(n) != map.end()) return map[n];

	// answer by eating (2*n)/3 oranges
	int sol1 = solve2(n / 3, map) + 1;
	sol1 += n % 3;  // eating one orange if n is not div by 3

	//answer by eating n/2 oranges...
	int sol2 = solve2(n / 2, map) + 1;
	sol2 += (n & 1); // if n is not odd, we have to eat one orange today

	return map[n] = std::min(sol1, sol2);
}

int minDays(int n) {
	std::unordered_map<int, int> map;
	return solve2(n, map);
}

int dp[51][51][51];
int sol(int r1, int c1, int r2, int n, const std::vector<std::vector<int>>& v) {
	//reduce four variables into three variables
	int c2 = r1 + c1 - r2;

	//base cases
	if (r1 >= n || r2 >= n || c1 >= n || c2 >= n || v[r1][c1] == -1 || v[r2][c2] == -1) return INT_MIN;
	if (r1 == n - 1 && c1 == n - 1) return v[r1][c1];

	//if already traversed, return calculated value
	if (dp[r1][c1][r2] != 0) return dp[r1][c1][r2];
	int x = 0;

	//if from both path, we are on same cherry, take only one
	if (r1 == r2 && c1 == c2) x += v[r1][c1];

	//else take both
	else x += v[r1][c1] + v[r2][c2];

	//take maximum of all 4 possible ways
	int a = sol(r1 + 1, c1, r2 + 1, n, v);
	int b = sol(r1, c1 + 1, r2, n, v);
	int c = sol(r1 + 1, c1, r2, n, v);
	int d = sol(r1, c1 + 1, r2 + 1, n, v);
	x += std::max(std::max(a, b), std::max(c, d));
	return dp[r1][c1][r2] = x;
}
int cherryPickup(const std::vector<std::vector<int>>& v) {
	int n = (int)v.size();
	memset(dp, 0, sizeof(dp));
	int ans = sol(0, 0, 0, n, v);
	return std::max(0, ans);
}


ll minimumCost(const std::string& s)
{
	int n = (int)s.size();
	int mid = n / 2;
	ll ans = 0;
	char temp = s[mid];
	//make all chars of string equal to temp
	int i = mid - 1, j = mid + 1;
	int left = 0, right = 0;
	while (i >= 0) {
		char ss = s[i];
		if (left % 2)    //flip ss, if odd operations done
			ss = (ss == '0') ? '1' : '0';
		if (ss != temp) {
			left++;
			ans += (i + 1);
		}
		i--;
	}
	while (j < n) {
		char ss = s[j];
		if (right % 2) //flip ss, if odd operations done
			ss = (ss == '0') ? '1' : '0';
		if (ss != temp) {
			right++;
			ans += (n - j);
		}
		j++;
	}
	return ans;
}

int maxSum(std::vector<int>& nums1, std::vector<int>& nums2) {
	int i = 0, j = 0;
	ll sum1 = 0, sum2 = 0;
	while (i < nums1.size() && j < nums2.size()) {
		if (nums1[i] == nums2[j]) {
			// if two elements are equal, till current position in both the vectors, keep maximum sum obtained 
			sum1 = (sum1 + nums1[i++]);
			sum2 = (sum2 + nums2[j++]);
			ll msum = std::max(sum1, sum2);
			sum1 = msum % 1000000007;
			sum2 = msum % 1000000007;
		}
		else if (nums1[i] < nums2[j]) { // increase small index and add value in correponding sum
			sum1 = (sum1 + nums1[i++]);
		}
		else {
			sum2 = (sum2 + nums2[j++]);
		}
	}
	while (i < nums1.size()) { // add left elements
		sum1 = sum1 + nums1[i++];
	}
	while (j < nums2.size()) {
		sum2 = (sum2 + nums2[j++]);
	}
	return (std::max(sum1, sum2)) % 1000000007;
}

std::vector<int> nextPermutation(const std::vector<int>& vec) {
	int i, n = (int)vec.size();

	std::vector<int>v(n);
	for (int i = 0; i < n; i++) v[i] = vec[i];
	// find breaking point
	for (i = n - 2; i >= 0; i--) if (v[i] < v[i + 1]) break;

	//if there is no breaking  point
	if (i < 0) {
		reverse(v.begin(), v.end()); return v;
	}

	else {
		int small = i + 1, j;

		// find next greater element
		for (j = i + 2; j < n; j++) if (v[j] > v[i] && v[j] <= v[small]) small = j;
		std::swap(v[i], v[small]);

		// sort the rest right half
		sort(v.begin() + i + 1, v.end());
	}
	return v;
}

std::vector<int> canSeePersonsCount(const std::vector<int>& A) {
	int n = (int)A.size();
	std::vector<int>ans(n), stack;
	for (int i = 0; i < n; i++) {
		while (!stack.empty() && A[stack.back()] <= A[i]) {
			ans[stack.back()]++; // i_th person can see those shorter people, so increase by one
			stack.pop_back(); // Remove shorter people, because those people can't be seen anymore.
		}
		if (!stack.empty())  // If stack is not empty then i_th person can see one more person which is taller than himself.
			ans[stack.back()]++;  // increase by one

		stack.push_back(i); // add i_th person to our stack
	}
	return ans;
}

int totalFruit(std::vector<int>& v) {
	std::unordered_map<int, int>m;
	int i = 0, j = 0, ans = 0;
	while (j < v.size()) {
		m[v[j]]++;   //add a new value to the sliding window
		while (m.size() > 2) { //'repair' the window if it violates the constraints
			if (--m[v[i]] == 0) m.erase(v[i]);
			i++;
		}
		ans = std::max(ans, j - i + 1);
		j++; // increase right
	}
	return ans;
}


int main() {
	return 0;
}