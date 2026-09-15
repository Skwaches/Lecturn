# 2472. Maximum Number of Non-overlapping Palindrome Substrings
# You are given a string s and a positive integer k.
#
# Select a set of non-overlapping substrings from the string s that satisfy the following conditions:
#
#     The length of each substring is at least k.
#     Each substring is a palindrome.
#
# Return the maximum number of substrings in an optimal selection.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example 1:
#     Input: s = "abaccdbbd", k = 3
#     Output: 2
#     Explanation: We can select the substrings underlined in s = 'aba' cc 'dbbd'.
#                  Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
# It can be shown that we cannot find a selection with more than two valid substrings.

# Example 2:
#     Input: s = "adbcda", k = 2
#     Output: 0
#     Explanation: There is no palindrome substring of length at least 2 in the string.

# Constraints:
#     1 <= k <= s.length <= 200
#     s consists of lowercase English letters.
class Solution:
    mostLong = 0
    def isPalindrome(self,text):
        return text[::-1] == text

    def overlap(self, x:tuple[int,int],y:tuple[int,int]):
        if x[1] < y[0] or x[0] > y[1]:
            return False
        return True

    def pick(self, overlapMap:list[list[int]], available:list[int], length = 0):
        for index in available:
            remaining = available.copy()
            remaining.remove(index)
            for other in overlapMap[index]:
                try:
                    remaining.remove(other)
                except ValueError:
                    continue
            if len(remaining) <= 0:
                self.mostLong = max(self.mostLong,length+1)
                return
            self.pick(overlapMap, remaining ,length + 1)

    def non_overlapping(self, ranges:list[tuple[int,int]])->int:
        longest = 0
        overlapsWith:list[list[int]] = [[] for _ in ranges]
        for i in range(len(ranges) - 1):
            for j in range(i + 1, len(ranges)):
                if self.overlap(ranges[i],ranges[j]):
                    overlapsWith[i].append(j)
                    overlapsWith[j].append(i)
        available = [i for i in range(len(ranges))]
        self.pick(overlapsWith, available)
        biggest = self.mostLong
        self.mostLong = 0
        return biggest

    def maxPalindromes(self, s: str, k: int) -> int:
        # Shortest palindrome from each possible starting point.
        ranges:list[tuple[int,int]] = []
        for start in range(0,len(s) - k + 1):
            for end in range(start + k, len(s) + 1):
                substring = s[start:end]
                if self.isPalindrome(substring):
                    ranges.append((start,end-1))
                    break
        return self.non_overlapping(ranges) 

if __name__ == "__main__":
    test = Solution()
    print(test.maxPalindromes("sjbxiufnaanqkwsqswkqrcznzcddhtuhtthuttjfuufjtcfywgecegwyhhnnhtozczirynhhnyrire",3))
