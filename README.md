g++ -std=c++11 main.cpp && ./a.out

notes:
- Day 3: check for overflow when multiplying, it can get big fast
- Day 5: Used unordered\_set instead of boolean array. I should do some benchmarking to see perf difference, but input size (n=805) is too small to really matter?
- Day 10: Part 2 is a cool application what what we did in EECS203. I think this is called dynamic programming. Find combinations in O(n) time.
- Day 13: Realized I had to use the Chinese Remainder Theorem for Part 2 (thanks eecs 203). But that is annoying to code up and not really going to help me get better at cpp. **Skipped**.
- Day 14: Overflow error from converting from unsigned long to int in key for unordered_map ```[]``` operator.

Git:  
- To perm delete something from all record:  
    ```git filter-branch -f --index-filter "git rm -rf --cached --ignore-unmatch PATH_TO_FILE" -- --all```  
    ```git push --all --force```  


