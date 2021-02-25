sample_txt ="""3
3 26000000 11000000 6000000
3 1 10 11
2 800000000000000000001 900000000000000000001"""



def main():
	# preparation from input
	sample_txt_list = []


	# sample_txt_list = sample_txt.split('\n')

	# num_test_case = int(sample_txt_list[0])

	sample_txt_list = []
	num_test_case = int(input())
	for i in range(num_test_case):
		sample_txt_list.append(input())

	print(sample_txt_list)

	test_cases = []
	for i in range(len(sample_txt_list)):
		test_cases.append([int(x) for x in sample_txt_list[i].split(' ')[1:]])

	print(test_cases)

	# solve problem
	for i in range(num_test_case):
		pass
		print(f"Case #{i + 1}: {getY(test_cases[i])}")

# Function to return gcd of a and b
def gcd(a, b): 
    if a == 0 :
        return b 
     
    return gcd(b%a, a)


def getY(test_cases):
	test_cases.sort()
	# print(test_cases)

	# handle special case when there's only 1 element
	if len(test_cases) == 1:
		return test_cases[0]

	# gcd for the diff of 2 numbers in sorted array in descending order

	# 1. compute a new list of diff for 2 nubmers in descending order

	diff_list = []
	for i in range(len(test_cases) - 1):
		diff_list.append(test_cases[i + 1] - test_cases[i])

	# 2. iterate the list to do gcd for each number
	gcdNum = diff_list[0]
	for i in range(len(diff_list) - 1):
		gcdNum = gcd(diff_list[i + 1], gcdNum)

	# 3. found the gcd, find y now. pick the smallest number, take the ceiling of quotient for smallest num / gcd
	smallest_num = test_cases[0]
	ceiling = -(-smallest_num // gcdNum)

	# 4. y = ceiling x gcd - smallest num 
	return ceiling * gcdNum - smallest_num




if __name__ == '__main__':
	main()
