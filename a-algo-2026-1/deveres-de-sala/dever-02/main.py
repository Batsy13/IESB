def func1(n):
    if n == 0:
        return 1
    
    return func1(n-1) + n + 1

def func2(n):
    if n == 1:
        return 1

    return func2(n-1) + 3*n + 2

def func3(n):
    if n <= 0:
        return 5
    
    print(n)
    
    return func3(n//2) + 3*n
    

question1 = int(input("Enter a number for the first function: "))
print(func1(question1))
question2 = int(input("Enter a number for the second function: "))
print(func2(question2))

question3 = int(input("Enter a number for the third function: "))
if (question3 & (question3-1)):
    print("Insert a valid number")
else:
    print(func3(question3))