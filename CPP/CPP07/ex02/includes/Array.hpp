#ifndef ARRAY_H
# define ARRAY_H

# include <iostream>
# include <stdexcept>

template< typename T>
class Array {
	public:
		Array(void);
		Array(unsigned int n);
		Array(Array const &cpy);
		~Array(void);

		Array& operator=(Array const &assign);
		T& operator[](size_t index) const;		

		size_t size(void) const;
		
		class InvalidIndex : public std::exception 
		{
			public:
            virtual const char * what() const throw()
            {
                return ("Invalid index");
            }
		};

	private:
		size_t	_size;
		T* _array;
};

template< typename T>
Array<T>::Array(void) : _size(0), _array(new T[0]) {}

template< typename T>
Array<T>::Array(unsigned int n) : _size(n), _array(new T[n]) {
	for (size_t i = 0; i < _size; i++) {
		_array[i] = T();
	}
}

template< typename T>
Array<T>::Array(Array const &cpy) {
	*this = cpy;
}

template< typename T>
Array<T>::~Array(void){
	delete [] _array;
}

template< typename T>
Array<T>& Array<T>::operator=(Array<T> const &assign) {
	_size = assign._size;
	_array = new T[_size];
	for (size_t i = 0; i < _size; i++) {
		_array[i] = assign._array[i];
	}
	return (*this);
}

template< typename T>
T& Array<T>::operator[](size_t index) const {
	if (index >= _size || index < 0)
		throw InvalidIndex ();
	return (_array[index]);
}

template< typename T>
size_t Array<T>::size(void) const{
	return _size;
}

template< typename T>
std::ostream & operator<<(std::ostream & out, Array<T> const &ref)
{
	for (size_t i = 0; i < ref.size(); i++) {
		out << ref._array[i];
	}
	return out;
}

#endif
