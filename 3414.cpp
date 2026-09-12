/* 3414. Maximum Score of Non-overlapping Intervals
 *
 * You are given a 2D integer array intervals,
 * where intervals[i] = [l_i, r_i, weight_i].
 * Interval i starts at position l_i and ends at r_i,
 * and has a weight of weight_i. You can choose up to 4
 * non-overlapping intervals. The score of the chosen intervals
 * is defined as the total sum of their weights.
 * Return the lexicographically smallest array of at most 4
 * indices from intervals with maximum score,
 * representing your choice of non-overlapping intervals.
 * Two intervals are said to be non-overlapping if they do not share any points.
 * In particular, intervals sharing a left or right boundary
 * are considered overlapping.
 *
 * Example 1:
 * 	Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
 *  Output: [2,3]
 *  Explanation: You can choose the intervals with indices 2, and 3
 *  with respective weights of 5, and 3.
 *
 * Example 2:
 * 	Input: intervals = [[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]
 * 	Output: [1,3,5,6]
 * 	Explanation: You can choose the intervals with indices 1, 3, 5, and 6
 * 	with respective weights of 7, 6, 3, and 5.
 *
 * Constraints:
 *	1 <= intevals.length <= 5 * 10^4
 *	intervals[i].length == 3
 *	intervals[i] = [l_i, r_i, weighti]
 *	1 <= l_i <= r_i <= 10^9
 *	1 <= weight_i <= 10^9
 */

#include <algorithm>
#include <iostream>
#include <vector>
class Solution {
public:
	bool isBetween(int a,int l, int h){
		if (l > h){
			h ^= l;
			l ^= h;
			h ^= l;
		}
		return !( (a < l) || (a > h) );
	}
	bool overlap (int l1, int h1, int l2, int h2){
		return  isBetween( l1 , l2, h2) || isBetween(h1 , l2, h2) || 
				isBetween( l2 , l1, h1) || isBetween(h2 , l1, h1);
	}

	 void allPaths(
			std::vector<std::vector<int>>& best, ulong& score,
			std::vector<std::vector<int>>& intervals,
			std::vector<int> allowed, std::vector<int> path = {},
			ulong currScore = 0)
	{
		for (size_t ir = 0; ir < allowed.size(); ir++){
			int i = allowed[ir];
			std::vector<int> myPath = path;
			if (myPath.size() == 0){
				myPath = {i};
			}
			else {
				bool overlapping = false;
				for (int j: myPath){
					int l1 = intervals[j][0];
					int h1 = intervals[j][1];

					int l2 = intervals[i][0];
					int h2 = intervals[i][1];
					if (overlap(l1,h1,l2,h2)){
						overlapping = true;
						break;
					}
				}
				if (overlapping)
					continue;
				myPath.push_back(i);
			}

			ulong updatedScore = currScore + intervals[i][2];
			if (updatedScore > score){
				best = {myPath}; 
				score = updatedScore;
			} 
			else if(score == updatedScore){
				best.push_back(myPath);
			}

			if (myPath.size() >= 4){
				continue;
			}

			std::vector<int> remaining = allowed;
			remaining.erase(remaining.begin() + ir);
			allPaths(best, score, intervals, remaining, myPath, updatedScore);
		}
	}
	std::vector<int> maximumWeight(std::vector<std::vector<int>>& intervals) {
		std::vector<int> permitted(intervals.size());
		size_t indexer = 0;
		while(indexer < intervals.size()){
			permitted[indexer] = indexer; 
			indexer++;
		}
		std::vector<std::vector<int>> paths;
		ulong score = 0;
		allPaths(paths, score, intervals,permitted);
		
		// Find lexicographically smallest.
		for (auto& path: paths){
			std::sort(path.begin(),path.end());
		}

		size_t i = 0;
		std::vector<size_t> marked(paths.size()); 
		indexer = 0;
		while(indexer < paths.size()){
			marked[indexer] = indexer; 
			indexer++;
		}
		while(marked.size() > 1){
			if (i >= paths[marked[0]].size())
				return paths[marked[0]];

			int smallest = paths[marked[0]][i];
			std::vector<size_t> remaining = {marked[0]};
			for (size_t j = 1; j < marked.size();j++){
				size_t k = marked[j];
				if (i < paths[k].size()){
					if (paths[k][i] < smallest){
						remaining = {k};
						smallest = paths[k][i];
					}
					else if (smallest == paths[k][i]) remaining.push_back(k);

					continue;
				}
				return paths[k];
			}
			marked = remaining;
			i++;
		}
		return paths[marked[0]];
	}
};


int main(){
	Solution solution;
	std::vector<std::vector<int>> intervals = {
		{17,17,10},{23,23,23},{3,8,31},{17,21,48},{18,24,44}
	};

	std::vector<int> path = solution.maximumWeight(intervals);
	for (auto item: path){
		std::cout << item << '\t';
	}
	std::cout << std::endl;
}
