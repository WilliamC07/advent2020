g++ -std=c++11 main.cpp && ./a.out

notes:
- Day 3: check for overflow when multiplying, it can get big fast
- Day 5: Used unordered\_set instead of boolean array. I should do some benchmarking to see perf difference, but input size (n=805) is too small to really matter?


Git:  
- To perm delete something from all record:  
    ```git filter-branch -f --index-filter "git rm -rf --cached --ignore-unmatch PATH_TO_FILE" -- --all```  
    ```git push --all --force```  


