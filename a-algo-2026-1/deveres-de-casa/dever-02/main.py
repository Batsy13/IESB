import time
import sys

# Increase the recursion depth limit for large values of n
sys.setrecursionlimit(2000)

def factorial(n):
    # Base case: factorial of 0 is 1
    if n == 0:
        return 1
    # Recursive step: n * factorial of (n-1)
    else:
        return n * factorial(n-1)

# Input values to be tested
sizes = [10, 100, 500, 1000]

print(f"{'n':<10} | {'Execution Time (s)':<20}")
print("-" * 35)

for size in sizes:
    # Record the starting time
    start_time = time.time()
    
    # Execute the recursive function
    factorial(size)
    
    # Record the ending time
    end_time = time.time()

    # Calculate the total duration
    final_time = end_time - start_time
    
    print(f"{size:<10} | {final_time:<20.8f}")



# n          | Factorial (s)       
# ------------------------------
# 10         | 0.00000             
# 100        | 0.00001             
# 500        | 0.00019             
# 1000       | 0.00036  


# Time Complexity O(n)
# 
#     To calcute the factorial of n, the function calls itself n times recursively. 
#     As each call realizes a multiplication operation in constant time, the time increases linearly 
#     with the input n.

# Space Complexity O(n)
#
#     Due to the recursion, the computer must  maintain a call stack in memory. For a n input, will 
#     exist n open stacks simultaneously before it reaches the base case.