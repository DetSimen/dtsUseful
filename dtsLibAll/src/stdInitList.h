#include <Arduino.h>

namespace std {

	template<typename T>
	class initializer_list {
	protected:

		const T  *FItems;
		size_t   FSize;

	public:

		constexpr initializer_list(): FItems(0), FSize(0) { } // пустой конструктор

		constexpr initializer_list(const T* AItems, size_t ASize) : FItems(AItems), FSize(ASize) {} //толстый конструктор

		constexpr size_t size() const { return FSize; } // число элементов

		constexpr const T* begin() const { return FItems; } // первый элемент

		constexpr const T* end() const { return begin() + size(); } // конец+1
	};

}
