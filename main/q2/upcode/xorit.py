
def countSetBits(n): 
	count = 0
	while (n):
		count += n & 1
		n >>= 1
	return count 


i = input()
print(pow(2,countSetBits(i))) 

