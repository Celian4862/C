void selection(int* a, int n) {
	while (--n) {
		int temp = a[n];
		int index = n, j = n;
		while (j--) {
			if (temp < a[j]) {
				index = j;
				temp = a[j];
			}
		}
		a[index] = a[n];
		a[n] = temp;
	}
}

void bubble (int* a, int n) {
	int i = n - 1, sorted, temp;
	do {
		sorted = 0;
		int j = n - 1;
		do {
			if (a[j] < a[j - 1]) {
				temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
				sorted = 1;
			}
		} while (--j);
	} while (--i && sorted);
}
