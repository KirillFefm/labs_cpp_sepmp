#include <iostream>
#include "subvector.hpp"

struct subvector {
	int* mas;
	unsigned int top;
	unsigned int capacity;
};

bool init(subvector* qv) {
	qv->capacity = 0;
	qv->mas = nullptr;
	qv->top = 0;
	return true;
}

bool resize(subvector* qv, unsigned int new_capacity) {
	if (new_capacity == qv->capacity) {
		return true;
	}
	if (qv->top > new_capacity) {
		qv->top = new_capacity;
	}
	int* new_mas = nullptr;
	if (new_capacity > 0) {
		new_mas = new int[new_capacity];
		if (new_mas == nullptr) return false;
	}

	for (unsigned int i = 0; i < qv->top; i++) {
		if (qv->mas != nullptr) {
			new_mas[i] = qv->mas[i];
		}
	}

	if (qv->mas != nullptr) {
		delete[] qv->mas;
	}

	qv->mas = new_mas;
	qv->capacity = new_capacity;

	return true;
}

void clear(subvector* qv) {
	qv->top = 0;
}

void destructor(subvector* qv) {
	if (qv->mas != nullptr) {
		delete[] qv->mas;
	}
	init(qv);
}

void shrink_to_fit(subvector* qv) {
	resize(qv, qv->top);
}

bool push_back(subvector* qv, int d) {
	if (qv->top == qv->capacity) {

		unsigned int new_capacity;
		if (qv->capacity == 0) {
			new_capacity = 1;
		}
		else {
			new_capacity = qv->capacity + 1;
		}

		if (!resize(qv, new_capacity)) {
			return false;
		}
	}

	qv->mas[qv->top] = d;
	qv->top += 1;
	return true;
}

int pop_back(subvector* qv) {
	if (qv->top == 0) {
		return 0;
	}

	int ans = qv->mas[qv->top - 1];
	qv->top -= 1;

	return ans;
}