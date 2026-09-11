/* 3483. Unique 3-Digit Even Numbers 
 * You are given an array of digits called digits.
 * Your task is to determine the number of distinct
 * three-digit even numbers that can be formed using these digits.
 * Note: Each copy of a digit can only be used once per number,
 * and there may not be leading zeros.
 *
 * Example 1:
 * 	Input: digits = [1,2,3,4] 
 * 	Output: 12
 * 	Explanation: The 12 distinct 3-digit even numbers that can be formed are
 * 	124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, and 432.
 * 	Note that 222 cannot be formed because there is only 1 copy of the digit 2. 
 *
 * Example 2:
 * 	Input: digits = [0,2,2]
 * 	Output: 2
 * 	Explanation: The only 3-digit even numbers that can be formed are
 * 	202 and 220. Note that the digit 2 can be used twice
 * 	because it appears twice in the array. 
 *
 * Example 3: 
 * 	Input: digits = [6,6,6]
 * 	Output: 1
 * 	Explanation: Only 666 can be formed.
 *
 * Example 4: 
 * 	Input: digits = [1,3,5] 
 * 	Output: 0 
 * 	Explanation: No even 3-digit numbers can be formed.
 *
 * Constraints: 
 * 	3 <= digits.length <= 10 
 * 	0 <= digits[i] <= 9
*/

#include <unordered_map>
#include <vector>
class Solution {
public:
	std::vector<int> factCache = {1};
	void permute(
			std::unordered_map<int,int>& digits,
			int& storage,
			int stage = 1){
		for (auto digit: digits){
			if (digit.second <= 0)
				continue;

			switch (stage){
				case 1:
					if (digit.first%2 != 0)
						continue;
					break;
				case 2:
					if (digit.first == 0)
						continue;
					break;
				case 3:
					storage++;
					continue;
			}
			digits[digit.first]--;
			permute(digits,storage,stage+1);
			digits[digit.first]++;
		}
	}

    int totalNumbers(std::vector<int>& digits) {
		int storage = 0;
		std::unordered_map<int,int> numbering;
		for (auto digit:digits) numbering[digit]++;
		permute(numbering,storage);
		return storage;
    }
};
