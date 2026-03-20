def recursive_palindrome(arr):
    if len(arr) <= 1:
        return True
    
    if arr[0] == arr[-1]:
        return recursive_palindrome(arr[1:-1])
    else:
        return False
    

array1 = [0,1,2,3,2,1,0]
array2 = ["a","b","b","a"]
array3 = ["a","b","c","b","a"]
array4 = ["a","b","c","f","b","a"]
print(recursive_palindrome(array1))
print(recursive_palindrome(array2))
print(recursive_palindrome(array3))
print(recursive_palindrome(array4))