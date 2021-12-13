#include <Arduino.h>

namespace std {

	template<typename T>
	class initializer_list {
	protected:

		const T  *FItems;
		size_t   FSize;

	public:

		constexpr initializer_list(): FItems(0), FSize(0) { } // ������ �����������

		constexpr initializer_list(const T* AItems, size_t ASize) : FItems(AItems), FSize(ASize) {} //������� �����������

		constexpr size_t size() const { return FSize; } // ����� ���������

		constexpr const T* begin() const { return FItems; } // ������ �������

		constexpr const T* end() const { return begin() + size(); } // �����+1
	};

}
