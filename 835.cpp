/* 835. Image Overlap
 * You are given two images, img1 and img2,
 * represented as binary, square matrices of size n x n.
 * A binary matrix has only 0s and 1s as values.
 * We translate one image however we choose by sliding all the 1 bits left,
 * right, up, and/or down any number of units.
 * We then place it on top of the other image. 
 * We can then calculate the overlap by counting the number of positions
 * that have a 1 in both images.
 * Note also that a translation does not include any kind of rotation.
 * Any 1 bits that are translated outside of the matrix borders are erased.
 *
 * Return the largest possible overlap.
 *
 * Example 1:
 *	   Input: img1 = [[1,1,0],[0,1,0],[0,1,0]], img2 = [[0,0,0],[0,1,1],[0,0,1]]
 *	   Output: 3
 *	   Explanation: We translate img1 to right by 1 unit and down by 1 unit.
 *	   The number of positions that have a 1 in both images is 3 (shown in red).
 * 
 * Example 2:
 *	   Input: img1 = [[1]], img2 = [[1]]
 *	   Output: 1
 * 
 * Example 3:
 *	   Input: img1 = [[0]], img2 = [[0]]
 *	   Output: 0
 *
 * Constraints:
 *    n == img1.length == img1[i].length
 *    n == img2.length == img2[i].length
 *    1 <= n <= 30
 *    img1[i][j] is either 0 or 1.
 *    img2[i][j] is either 0 or 1.
 */

#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>
class Solution {
public:
	uint32_t convert(std::vector<int>& row, size_t& spots){
		uint32_t number = 0;
		for (size_t i = 0; i < row.size();i++)
			if (row[i]){
				number |= (1 << i);
				spots++;
			}
		return number;
	}

	uint32_t shift(uint32_t row, int direction){
		if (direction > 0) 
			row <<= direction;
		else row >>= -direction;
		return row;
	}

	std::vector<uint32_t> shift(
			std::vector<uint32_t> rows,
			std::pair<int,int> direction
			){
		if (direction.first)
			for (auto& row: rows)
				row = shift(row,direction.first);

		if (direction.second){
			std::vector<int> replace(std::abs(direction.second),0);
			if (direction.second > 0){
				rows.erase(rows.begin(),rows.begin() + direction.second);
				rows.insert(rows.end(),replace.begin(),replace.end());
			}
			else {
				if (rows.size() + direction.second > 0)
					rows.resize(rows.size() + direction.second);
				else rows = {};

				rows.insert(rows.begin(), replace.begin(),replace.end());
			}
		}
		return rows;
	}

	size_t overlap(uint32_t combined, size_t range){
		size_t overlapping = 0;
		for (size_t j = 0; j < range; j++){
			if ( combined & (1 << j) )
				overlapping++;
		}
		return overlapping;
	}
	size_t overlap(std::vector<uint32_t> imageA,std::vector<uint32_t> imageB){
		size_t overlapping = 0;
		for (size_t j = 0; j < imageA.size(); j++){
			overlapping += overlap(imageA[j]&imageB[j],imageA.size());
		}
		return overlapping;
	}
	void displayImage(std::vector<uint32_t> image){
		for (auto row: image){
			for (size_t j = 0; j < image.size(); j++){
				bool bit = row & (1 << j);
				std::cout << bit << '\t';
			}
			std::cout << std::endl;
		}
	}

    int largestOverlap(
			std::vector<std::vector<int>>& img1,
			std::vector<std::vector<int>>& img2) {
		std::vector<uint32_t> imageA(img1.size()),imageB(img2.size());
		size_t onA = 0, onB = 0;
		for (size_t i = 0; i < img1.size();i++){
			imageA[i] = convert(img1[i],onA);
			imageB[i] = convert(img2[i],onB);
		}
		int overlapping = 0;
		int maximumLap = onA < onB ? onA: onB;
		for (int x = -imageA.size(); x < (int)imageA.size();x++)
			for (int y = -imageA.size(); y < (int)imageA.size();y++){
				bool finished = false;
				int grade = overlap(shift(imageA,{x,y}),imageB);

compare:
				if (grade > overlapping)
					overlapping = grade;
				if (grade >= maximumLap)
					return grade;
				if (finished) continue;

				grade = overlap(shift(imageB,{x,y}),imageA);
				finished = true;
				goto compare;
			}
			
		return overlapping;
	}
};

int main(){
	Solution solution;
	std::vector<std::vector<int>> 
	img1 = { {1,1,0},
			 {0,1,0},
			 {0,1,0}
	},
	img2 = { {0,0,0},
			 {0,1,1},
			 {0,0,1}
	};
	std::cout << solution.largestOverlap(img1,img2) << std::endl;
	return 0;
}
