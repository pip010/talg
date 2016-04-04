#pragma once

#include <type_traits>
#include <typeinfo>

template<typename T>
void PrintTypeTraits(void)
{
	using namespace std;
	
	cout << endl;
	cout << "Type: " << typeid(T).name() << endl;
	cout << "Size: " << sizeof(T) << endl;
	cout << endl;
	cout << "Type properties:" << endl;
	cout << "is_abstract: " << is_abstract<T>::value << endl;
	cout << "is_const: " << is_const<T>::value << endl;
	cout << "is_empty: " << is_empty<T>::value << endl;
	cout << "is_literal_type: " << is_literal_type<T>::value << endl;
	cout << "is_pod: " << is_pod<T>::value << endl;
	cout << "is_polymorphic: " << is_polymorphic<T>::value << endl;
	cout << "is_signed: " << is_signed<T>::value << endl;
	cout << "is_standard_layout: " << is_standard_layout<T>::value << endl;
	cout << "is_trivial: " << is_trivial<T>::value << endl;
	//cout << "is_trivially_copyable: " << is_trivially_copyable<T>::value << endl;
	cout << "is_unsigned: " << is_unsigned<T>::value << endl;
	cout << "is_volatile: " << is_volatile<T>::value << endl;
	cout << endl;
	cout << "Type features:" << endl;
	cout << "has_virtual_destructor: " << has_virtual_destructor<T>::value << endl;
	//cout << "is_assignable: " << is_assignable<T>::value << endl;
	cout << "is_constructible: " << is_constructible<T>::value << endl;
	cout << "is_copy_assignable: " << is_copy_assignable<T>::value << endl;
	cout << "is_copy_constructible: " << is_copy_constructible<T>::value << endl;
	cout << "is_destructible: " << is_destructible<T>::value << endl;
	cout << "is_default_constructible: " << is_default_constructible<T>::value << endl;
	cout << "is_move_assignable: " << is_move_assignable<T>::value << endl;
	cout << "is_move_constructible: " << is_move_constructible<T>::value << endl;
	
	/*
	cout << "is_trivially_assignable: " << is_trivially_assignable<T>::value << endl;
	cout << "is_trivially_constructible: " << is_trivially_constructible<T>::value << endl;
	cout << "is_trivially_copy_assignable: " << is_trivially_copy_assignable<T>::value << endl;
	cout << "is_trivially_copy_constructible: " << is_trivially_copy_constructible<T>::value << endl;
	cout << "is_trivially_destructible: " << is_trivially_destructible<T>::value << endl;
	cout << "is_trivially_default_constructible: " << is_trivially_default_constructible<T>::value << endl;
	cout << "is_trivially_move_assignable: " << is_trivially_move_assignable<T>::value << endl;
	cout << "is_trivially_move_constructible: " << is_trivially_move_constructible<T>::value << endl;
	*/
	
	/*
	cout << "is_nothrow_assignable: " << is_nothrow_assignable<T>::value << endl;
	cout << "is_nothrow_constructible: " << is_nothrow_constructible<T>::value << endl;
	cout << "is_nothrow_copy_assignable: " << is_nothrow_copy_assignable<T>::value << endl;
	cout << "is_nothrow_copy_constructible: " << is_nothrow_copy_constructible<T>::value << endl;
	cout << "is_nothrow_destructible: " << is_nothrow_destructible<T>::value << endl;
	cout << "is_nothrow_default_constructible: " << is_nothrow_default_constructible<T>::value << endl;
	cout << "is_nothrow_move_assignable: " << is_nothrow_move_assignable<T>::value << endl;
	cout << "is_nothrow_move_assignable: " << is_nothrow_move_assignable<T>::value << endl;
	cout << "is_nothrow_move_constructible: " << is_nothrow_move_constructible<T>::value << endl;
	*/



}
