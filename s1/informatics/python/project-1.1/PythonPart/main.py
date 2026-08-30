#
# Created by MattFor on 12/03/2025.
#

import time
import random


def radix_lsd_bucket_sort(arr):
	if not arr:
		return arr

	# Find the maximum number to know the number of digits
	max_val = max(arr)
	exp = 1

	# Continue until all digit positions have been processed
	while max_val // exp > 0:
		# Create 10 empty buckets for digits 0 through 9
		buckets = [[] for _ in range(10)]

		# Distribute elements into buckets based on current digit
		for number in arr:
			digit = (number // exp) % 10
			buckets[digit].append(number)

		# Collect the numbers from buckets back into the array
		arr = []
		for bucket in buckets:
			arr.extend(bucket)

		# Move to next digit position
		exp *= 10

	return arr


def radix_sort_floats(arr, precision=6):
	factor = 10 ** precision

	# Separate into non-negative and negative lists
	positives = [x for x in arr if x >= 0]
	negatives = [x for x in arr if x < 0]

	# Convert floats to integers by scaling.
	pos_int = [int(round(x * factor)) for x in positives]

	# Make negatives positive for sorting
	neg_int = [int(round(-x * factor)) for x in negatives]

	sorted_pos_int = radix_lsd_bucket_sort(pos_int)
	sorted_neg_int = radix_lsd_bucket_sort(neg_int)

	# Back to floats.
	sorted_positives = [x / factor for x in sorted_pos_int]

	# For negatives, after sorting in increasing order of their absolute values
	# Reverse the list and reapply the negative sign
	sorted_negatives = [-x / factor for x in reversed(sorted_neg_int)]

	# Combine both lists, negatives first of course
	return sorted_negatives + sorted_positives


def main():
	print("Generating random number array...")

	n = 1_000_000
	arr = [random.uniform(-n, n) for _ in range(n)]

	start_time = time.perf_counter()
	sorted_arr = radix_sort_floats(arr, precision=10)
	end_time = time.perf_counter()

	execution_time = end_time - start_time

	print("First 20 elements before sorting:", arr[:20])
	print("First 20 elements after sorting: ", sorted_arr[:20])
	print(f"Radix execution time: {execution_time:.6f} seconds")

	start_time = time.perf_counter()
	sorted_arr = sorted(arr)
	end_time = time.perf_counter()

	execution_time = end_time - start_time

	print("First 20 elements before sorting:", arr[:20])
	print("First 20 elements after sorting: ", sorted_arr[:20])
	print(f"Default sort execution time: {execution_time:.6f} seconds")


if __name__ == '__main__':
	main()
