#pragma once
#include <ostream>
#include <cmath>
#include <complex>

template <class T>
class Vector2 {
private:
	T m_x_;
	T m_y_;
public:
	Vector2();
	Vector2(T x, T y);

	T GetX() const;
	T GetY() const;
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
	m_x_ = x;
	m_y_ = y;
}

template <class T>
T Vector2<T>::GetX() const {
	return m_x_;
}

template <class T>
T Vector2<T>::GetY() const {
	return m_y_;
}

template <class T>
void Vector2<T>::SetX(T x) {
	m_x_ = x;
}

template <class T>
void Vector2<T>::SetY(T y) {
	m_y_ = y;
}

template <class T>
T Vector2<T>::GetLength() {
	return std::sqrt(m_x_ * m_x_ + m_y_ * m_y_);
}

template <class T>
bool Vector2<T>::operator==(const Vector2& rhs) const {
	if (rhs.GetX() == m_x_ && rhs.GetY() == m_y_) 
		return true;
	return false;
}

template <class T>
bool Vector2<T>::operator!=(const Vector2& rhs) const {
	if (rhs.GetX() == m_x_ && rhs.GetY() == m_y_)
		return false;
	return true;
}
