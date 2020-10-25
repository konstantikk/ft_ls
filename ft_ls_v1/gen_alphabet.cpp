#include <iostream>

using namespace std;

void output_alphabet(char c, int elems_per_row) {
	cout << "{\n";
	int add = 0;
	for (int i = 0; i < 26; ++i) {
		cout << 0 << ", ";
		if ((i % elems_per_row) == 0 && i != 0) {
			cout << "/// ";
			for (int j = i - elems_per_row; j < i + (i == elems_per_row); ++j) {
				cout << '-' << (char)(c + j + add) << ' ';
			}
			if (!add)
				add = i == elems_per_row;
			cout << '\n';
		}
	}
	cout << "}\n";
}

int	main(void)
{
	output_alphabet('a', 5);
	output_alphabet('A', 5);
}
