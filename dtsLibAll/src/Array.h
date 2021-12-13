#pragma once
#include <Arduino.h>
#include <stdInitList.h>



template<typename T>
class TArray {
protected:
	
	uint8_t FSize;
	T* FItems;
	T  FWrongValue;

public:
	TArray(const uint8_t ASize) {
		FItems = new T[FSize = ASize];
		for (uint8_t i = 0; i < FSize; ++i) FItems[i] = T();
	}

    TArray(const std::initializer_list<T> &AList): TArray(AList.size()) {

		uint8_t idx = 0;
        for (const auto& item:AList) FItems[idx++] = item;
    
	}

	T& operator[] (const uint8_t AIdx) {
		if (AIdx < FSize)
			return FItems[AIdx];
		else
			return FWrongValue;
	}

	T operator[](const uint8_t AIdx) const {
		if (AIdx < FSize)
			return FItems[AIdx];
		else
			return T();
	}

	uint8_t getSize() const { return FSize; }

	T& operator =(const TArray<T>& ASource) {
		if (this->FItems != NULL) {
			delete[] FItems;
			FItems = NULL;
		}
		
		FSize = ASource.getSize();
		if (FSize != 0) {

			FItems = new T[FSize];

			uint8_t idx = 0;
			for (const auto& item : ASource) FItems[idx++] = item;
		}

		return *this;
	}

	~TArray() {
		delete[] FItems;
	}
};

