#pragma once
#include <ostream>
#include <cmath>
#include <complex>

template <class T>
class Vector2 {
private:
	T m_x;
	T m_y;
public:
	Vector2();
	Vector2(T x, T y);
	
	const T GetX() const;
	const T GetY() const;
	void SetX(T x);
	void SetY(T y);

	T GetLength();

	bool operator ==(const Vector2& rhs) const;
	bool operator !=(const Vector2& rhs) const;

	friend std::ostream &operator<<(std::ostream &stream, const Vector2 &vector) {
		stream << "(";
		stream << vector.GetX();
		stream << ", ";
		stream << vector.GetY();
		stream << ")";
		return stream;
	}
};

template <class T>
Vector2<T>::Vector2() {
}

template <class T>
Vector2<T>::Vector2(T x, T y) {
	m_x = x;
	m_y = y;
}

template <class T>
const T Vector2<T>::GetX() const {
	return m_x;
}

template <class T>
const T Vector2<T>::GetY() const {
	return m_y;
}

template <class T>
void Vector2<T>::SetX(T x) {
	m_x = x;
}

template <class T>
void Vector2<T>::SetY(T y) {
	m_y = y;
}

template <class T>
T Vector2<T>::GetLength() {
	return std::sqrt(m_x * m_x + m_y * m_y);
}

template <class T>
bool Vector2<T>::operator==(const Vector2& rhs) const {
	if (rhs.GetX() == m_x && rhs.GetY() == m_y) 
		return true;
	return false;
}

template <class T>
bool Vector2<T>::operator!=(const Vector2& rhs) const {
	if (rhs.GetX() == m_x && rhs.GetY() == m_y)
		return false;
	return true;
}
