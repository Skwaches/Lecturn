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
#include <iostream>
#include <algorithm>
#include <vector>

class Solution {
public:
	std::vector<size_t> quickSort(
			std::vector<int>& numbers,
			std::vector<size_t> rankings = {},
			bool start = true){
		if (start){
			size_t indexer = 0;
			rankings.resize(numbers.size());
			while(indexer<numbers.size()) {
				rankings[indexer] = indexer;
				indexer++;
			}
		}
		else if(rankings.size() <= 1)
			return rankings;
		size_t pivot = rankings.back();
		std::vector<size_t> left,right,center = {pivot};
		for (size_t i = 0; i < rankings.size() - 1; i++){
			size_t j = rankings[i];
			if (numbers[j] > numbers[pivot]) right.push_back(j);
			else if (numbers[j] < numbers[pivot]) left.push_back(j);
			else center.push_back(j);
		}
		std::vector<size_t> leftSorted  = quickSort(numbers,left,false);
		std::vector<size_t> rightSorted = quickSort(numbers,right,false);
		center.insert(center.end(),rightSorted.begin(),rightSorted.end());
		leftSorted.insert(leftSorted.end(),center.begin(),center.end());
		return leftSorted;
	}
	size_t binarySearch(int search, std::vector<int>& numbers, std::vector<size_t>& rankings){
		size_t lowest = 0, highest = rankings.size() - 1;
		if (search < numbers[rankings[0]] || search > numbers[rankings.back()]){
			 return rankings.size();
			
		}
		while (true){
			size_t guess = (highest + lowest)/2;
			size_t i = rankings[guess];
			if (numbers[i] < search) lowest  = guess + 1;
			else if (numbers[i] > search) highest = guess - 1;
			else return i;

			if (highest == lowest) return rankings.size();
			
		}
	}
	void bestPath(
			std::vector< std::pair<std::vector<size_t>, int> >& directions, int depth,
			std::vector<std::vector<size_t>>& paths,
			std::vector<size_t> steps = {}, ulong cost = 0,
			size_t position = 0
			){
		
		cost += directions[position].second;
		for (auto option: directions[position].first){
			auto it = std::find(steps.begin(),steps.end(),option);
			if (it != steps.end())
				continue;
			std::vector<size_t> shadowSteps = steps;
			shadowSteps.push_back(option);

			if (steps.size() >= depth){
				paths.push_back(steps);
				continue;
			}
			bestPath(directions,depth, paths, steps, cost+directions[position].second,option);
		}
	}

	std::vector<int> maximumWeight(std::vector<std::vector<int>>& intervals) {
		// Sort list by upper bounds.
		std::vector<int> upperBounds;
		std::vector<int> path;
		for (auto interval:intervals) upperBounds.push_back(interval[1]);
		std::vector<size_t> rankings = quickSort(upperBounds);
		std::vector< std::pair<std::vector<size_t>, int> > nextStep(intervals.size(), { {}, 0 } );

		for(size_t j = 0; j < rankings.size();j++){
			size_t match = rankings[j];
			std::vector<int> start = intervals[match];
			for(size_t i = j + 1; i < rankings.size();j++){
				size_t current = rankings[i];
				std::vector<int> next = intervals[current];
				if ( next[0] > start[1] ){
					if(next[2] > nextStep[match].second){
						nextStep[match] = { {current}, next[2]};
					}
					else if(next[2]  == nextStep[match].second){
						nextStep[match].first.push_back(current);
					}
				}
			}
		}
		return {};
	}
};

int main(){
	Solution solution;
	std::vector<int> numbers = {5,3,2,1};
	std::vector<size_t> rankings = solution.quickSort(numbers);
	size_t spot = solution.binarySearch(4,numbers,rankings);
	if (spot != rankings.size())
		std::cout << spot << std::endl;
}

