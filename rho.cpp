/*
 * rho.c
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>

using namespace std;

#define INPUT_SIZE_MIN 5
#define INPUT_SIZE_MAX 10

static unsigned int rand_between(unsigned int lo, unsigned int hi)
{
	return static_cast<unsigned int>(floor(random() * (hi - lo + 1) / RAND_MAX) + lo);
}

static void make_input(unsigned int **arr, size_t *size)
{
	*size= rand_between(INPUT_SIZE_MIN, INPUT_SIZE_MAX);
	*arr = new unsigned int[*size];
	for (unsigned int i = 0; i < *size; i++) {
		(*arr)[i] = rand_between(1, *size - 1);
	}
}

static void show_arr(const unsigned int *arr, size_t size) {
	cout << "arr[" << size << "] = [";
	if (size--) {
		cout << *(arr++);
	}
	while (size--) {
		cout << ", " << *(arr++);
	}
	cout << "]" << endl;
}

static unsigned int f(const unsigned int *arr, size_t n)
{
	return arr[n - 1];
}

static unsigned int rho(const unsigned int *arr, size_t size)
{
	unsigned int a, b;

	a = f(arr, f(arr, size));
	b = f(arr, size);
	while (a != b) {
		a = f(arr, f(arr, a));
		b = f(arr, b);
	}

	a = size;
	while (a != b) {
		a = f(arr, a);
		b = f(arr, b);
	}

	return a;
}

static void check_dup(const unsigned int *arr, size_t size, unsigned int dup)
{
	size_t count = 0;
	for (unsigned int i = 0; i < size; i++) {
		if (arr[i] == dup) {
			count++;
		}
	}
	cout << dup << " occurs " << count << " times." << endl;
	assert(count > 0);
}

int main(int argc, char **argv)
{
	srandom(time(NULL));
	size_t size;
	unsigned int *arr;
	make_input(&arr, &size);
	show_arr(arr, size);
	unsigned int dup = rho(arr, size);
	check_dup(arr, size, dup);

	return EXIT_SUCCESS;
}
