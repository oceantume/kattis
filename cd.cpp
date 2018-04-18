#include <cstdint>
#include <iostream>
#include <vector>

int main()
{
	uint32_t n, m;
	while (std::cin >> n >> m, (m != 0 || n != 0)) {
		std::vector<uint32_t> nNumbers(n), mNumbers(m);

		for (auto& catalogNumber : nNumbers) {
			std::cin >> catalogNumber;
		}

		for (auto& catalogNumber : mNumbers) {
			std::cin >> catalogNumber;
		}

		uint32_t commonNumbersCount = 0, nIndex = 0, mIndex = 0;
		while (nIndex < nNumbers.size() && mIndex < mNumbers.size()) {
			const auto nNum = nNumbers[nIndex], mNum = mNumbers[mIndex];

			if (nNum <= mNum)
				nIndex++;
			if (mNum <= nNum)
				mIndex++;
			if (mNum == nNum)
				commonNumbersCount++;
		}

		std::cout << commonNumbersCount << std::endl;
	}

	return 0;
}
