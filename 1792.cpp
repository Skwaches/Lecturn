/*
   There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand that in the ith class, there are totali total students, but only passi number of students will pass the exam.

   You are also given an integer extraStudents. There are another extraStudents brilliant students that are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the extraStudents students to a class in a way that maximizes the average pass ratio across all the classes.

   The pass ratio of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.

   Return the maximum possible average pass ratio after assigning the extraStudents students. Answers within 10-5 of the actual answer will be accepted.



   Example 1:

   Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
   Output: 0.78333
   Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.

   Example 2:

   Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
   Output: 0.53485



   Constraints:

   1 <= classes.length <= 10^5
   classes[i].length == 2
   1 <= pass_i <= total_i <= 10^5
   1 <= extraStudents <= 10^5
   */


#include <iostream>
#include <algorithm>
#include <vector>


class Solution {
	public:
		std::vector<int> ranker(std::vector<double>& items){
			std::vector<int> rankings(items.size());
			for (size_t i = 0; i < items.size(); i++) 
				rankings[i] = i;
			bool sorted = false;
			while (!sorted){
				sorted = true;
				for (size_t i = 0; i + 1 < rankings.size();i++){
					if (items[rankings[i]] < items[rankings[i + 1]]){
						rankings[i] ^= rankings[i+1];
						rankings[i+1] ^= rankings[i];
						rankings[i] ^= rankings[i+1];
						sorted = false;
					}
				}
			}
			return rankings;
		}
		void inserter(std::vector<double>& items, std::vector<int>& rankings){
			if (rankings.size() > 1)
				if (items[rankings[0]] >= items[rankings[1]]) 
					return;
			int current = rankings[0];
			rankings.erase(rankings.begin());
			int highest = rankings.size() - 1, lowest = 1;
			while (true){
				int id = (highest + lowest)/2;

				if (items[rankings[id]] > items[current])
					lowest = id + 1;

				else if (items[rankings[id - 1]] <= items[current])
					highest = id - 1;

				if (items[rankings[id]] <= items[current] && items[rankings[id - 1]] >= items[current]){
					rankings.insert(rankings.begin() + id, current);
					return;
				}

				if (lowest == (int)rankings.size()){
					rankings.push_back(current);
					return;
				}
			}
		}

		double maxAverageRatio(std::vector<std::vector<int>>& classes, int extraStudents) {
			std::vector<double> weights(classes.size());
			std::vector<double> averages(classes.size());
			std::vector<int> rankings(classes.size());

			std::vector< std::pair<int,int> >cache;
			std::vector<int> cacheMapping;

			double before = 0, after = 0;
			for (size_t i = 0; i < classes.size();i++){
				auto it = std::find(cache.begin(),cache.end(),(std::pair<int,int>){classes[i][0],classes[i][1]});
				if (it != cache.end()){
					size_t index = std::distance(cache.begin(),it);
					averages[i] = averages[cacheMapping[index]];
					if (extraStudents)
						weights[i] = weights[cacheMapping[index]];
				}

				cache.push_back((std::pair<int,int>){classes[i][0],classes[i][1]});
				cacheMapping.push_back(i);

				before = (double)  classes[i][0]/classes[i][1];
				averages[i] = before;

				if(extraStudents){
					after  = (double) (classes[i][0] + 1) / (classes[i][1] + 1);
					weights[i] = after - before;
				}
			}

			rankings = ranker(weights);
			for (int j = 0; j < extraStudents;j++){
				int highest = rankings[0];
				classes[highest][0]++; 
				classes[highest][1]++; 

				auto ite = std::find(cacheMapping.begin(),cacheMapping.end(), j);
				if (ite != cacheMapping.end()){
					cacheMapping.erase(ite);
					cache.erase(cache.begin() + std::distance(cacheMapping.begin(),ite));
				}

				auto it = std::find(cache.begin(),cache.end(),(std::pair<int,int>){classes[highest][0],classes[highest][1]});
				if (it != cache.end()){
					size_t index = std::distance(cache.begin(),it);
					averages[highest] = averages[cacheMapping[index]];
					if (extraStudents){
						weights[highest] = weights[cacheMapping[index]];
						inserter(weights, rankings);
					}
				}
				else {
					double before = (double)classes[highest][0]/classes[highest][1];
					averages[highest] = before;  
					if (j+1 < extraStudents){
						double after  = (double) (classes[highest][0] + 1) / (classes[highest][1] + 1);
						weights[highest] = after - before;
						inserter(weights, rankings);
					}
					cache.push_back((std::pair<int,int>){classes[highest][0],classes[highest][1]});
					cacheMapping.push_back(highest);
				}
			}

			double total = 0;
			for (double avg:averages)
				total += avg;

			return total/classes.size();
		}
};

int main(){
	Solution solution;

	std::vector<std::vector<int>> classes = {{1,2},{3,5},{2,2}};
	std::cout << solution.maxAverageRatio(classes, 2) << std::endl;
	classes = {{2,4},{3,9},{4,5},{2,10}};
	std::cout << solution.maxAverageRatio(classes, 4) << std::endl;

	// std::vector<double> items = {30, 20, 10, 85, 15};
	// std::vector<int> rankings = solution.ranker(items);
	// for (int rank: rankings)
	// 	std::cout << items[rank] << '\t';
	// std::cout << std::endl;
	// items[rankings[0]] = 1;
	// solution.inserter(items,rankings);
	// std::cout << "After:\n";
	// for (int rank: rankings)
	// 	std::cout << items[rank] << '\t';
	// std::cout << std::endl;
}
