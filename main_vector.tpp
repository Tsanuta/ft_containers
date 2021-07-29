/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:08:32 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 13:27:07 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

template< class container >
static void print_vct(container const &vector, std::stringstream *stream)
{
	typename container::const_iterator ite = vector.end();

	for (typename container::const_iterator it = vector.begin(); it != ite; ++it)
		*stream << *it << ' ';
	*stream << std::endl;
}

template< class container, typename T >
static void	vct_empty_vector(T* values, std::stringstream *stream)
{
	container const	constVec(1, values[1]);
	container		first;								// empty vector
	*stream << "vector first ok\n";
	*stream << "first max  : " << first.max_size() << std::endl;
	*stream << "first size  : " << first.size() << std::endl;
}

template< class container, typename T >
static void	vct_lenght_error(T* values, std::stringstream *stream)
{
	container first;

	try {
		container tmp(first.max_size() + 1, values[5]); }
	catch(const std::length_error& e) {
		*stream << "Error: " << e.what() << std::endl; }
}

template< class container, typename T >
static void	vct_constructor_test(T* values, std::stringstream *stream)
{
	container tmp(4, values[5]);
	*stream << "tmp ok\n";
	*stream << "print_vct vector tmp\n";
	print_vct(tmp, stream);

	*stream << "------ VECTOR FROM ITERATORS ------\n";

	typename container::const_iterator it = tmp.begin();
	typename container::const_iterator ite = tmp.end();
	*stream << "it :" << (*it) << std::endl;
	container second(it, ite);						// four ints with value 100
	*stream << "vector second ok\n";
	*stream << "print_vct vector second\n";
	print_vct(second, stream);
	second.push_back(values[6]);
	*stream << "second front  : " << second.front() << std::endl;
	*stream << "second back  : " << second.back() << std::endl;
	second.pop_back();
	*stream << "second front  : " << second.front() << std::endl;
	*stream << "second back  : " << second.back() << std::endl;
	typename container::iterator secondit = second.begin();
	secondit++;
	*stream << "second iterator creation ok\n\n";

	*stream << "------ VECTOR FROM ITERATORS ------\n";

	container third(second.begin(), second.end());	// iterating through second
	*stream << "vector third ok\n";
	*stream << "print_vct vector third\n";
	print_vct(third, stream);

	*stream << "------ VECTOR FROM COPY ------\n";

	container fourth(third);						// a copy of third
	*stream << "vector fourth ok\n";
	*stream << "second capacity  : " << second.capacity() << std::endl;
	*stream << "second size  : " << second.size() << std::endl;
	*stream << "third capacity  : " << third.capacity() << std::endl;
	*stream << "third size  : " << third.size() << std::endl;
	*stream << "fourth capacity  : " << fourth.capacity() << std::endl;
	*stream << "fourth size  : " << fourth.size() << std::endl;
	*stream << "print_vct vector fourth\n";
	print_vct(fourth, stream);
}

template< class container, typename T >
static void	vct_operator_equal(std::stringstream *stream)
{
	container	first(3);		// vector of 3 zero-initialized ints
	container	second(5);		// vector of 5 zero-initialized ints

	second = first;
	first = container();

	*stream << "Size of first  : " << int (first.size()) << std::endl;
	*stream << "Size of second  : " << int (second.size()) << std::endl;
	*stream << std::endl;
}

template< class container, typename T >
static void	vct_begin(T* values, std::stringstream *stream)
{
	container		myvector(values, values + 5);

	*stream << "myvector contains  :";
	for (typename container::iterator it = myvector.begin(); it != myvector.end(); ++it)
		*stream << ' ' << *it;
	*stream << std::endl;

	container const	myvectorconst(values, values + 5);

	*stream << "myvectorconst contains  :";
	for (typename container::const_iterator itconst = myvectorconst.begin(); itconst != myvectorconst.end(); ++itconst)
		*stream << ' ' << *itconst;
	*stream << std::endl;
}

template< class container, typename T >
static void	vct_end(T* values, std::stringstream *stream)
{
	container	myvector(values, values + 5);

	*stream << "myvector contains  :";
	for (typename container::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		*stream << ' ' << *it;
	*stream << std::endl;
}

template< class container, typename T >
static void	vct_rbegin(T* values, std::stringstream *stream)
{
	container		myvector;
	for (int i = 0; i <= 4; ++i) myvector.push_back(values[i]);

	*stream << "myvector backwards  :";
	for (typename container::reverse_iterator rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
		*stream << ' ' << *rit;
	*stream << std::endl;

	container const	myvectorconst(values, values + 5);

	*stream << "myvectorconst backwards  :";
	for (typename container::const_reverse_iterator ritconst = myvectorconst.rbegin(); ritconst != myvectorconst.rend(); ++ritconst)
		*stream << ' ' << *ritconst;
	*stream << std::endl;

	typename container::reverse_iterator	rit2(myvector.begin());
	*stream << "reverse iterator copy construction from forward iterator\n";
}

template< class container, typename T >
static void	vct_rend(T* values, std::stringstream *stream)
{
	container		myvector;

	for (int i = 0; i <= 4; ++i) myvector.push_back(values[i]);

	*stream << "myvector backwards  :";
	for (typename container::reverse_iterator rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
		*stream << ' ' << *rit;
	*stream << std::endl;
}

template< class container, typename T >
static void	vct_empty(std::stringstream *stream)
{
	container myvector;
	int sum (0);

	for (int i = 1; i <= 10; ++i) myvector.push_back(i);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	*stream << "total  : " << sum << std::endl;
}

template< class container, typename T >
static void	vct_size(T* values, std::stringstream *stream)
{
	container myints;
	*stream << "0. size  : " << myints.size() << std::endl;

	for (int i = 0; i < 10; i++) myints.push_back(values[i]);
	*stream << "1. size  : " << myints.size() << std::endl;

	myints.insert (myints.begin(), 10, values[6]);
	*stream << "2. size  : " << myints.size() << std::endl;

	myints.pop_back();
	*stream << "3. size  : " << myints.size() << std::endl;
	*stream << "print_vct vector myints\n";
	print_vct(myints, stream);
}

template< class container, typename T >
static void	vct_max_size(std::stringstream *stream)
{
	container myvector;
	*stream << "myvector max size  : " << myvector.max_size() << std::endl;
}

template< class container, typename T >
static void	vct_resize(T* values, std::stringstream *stream)
{
	container myvector;

	// set some initial content:
	for (int i = 0; i < 8; i++)
		myvector.push_back(values[i]);

	myvector.resize(5);
	myvector.resize(8, values[6]);
	myvector.resize(12);

	*stream << "myvector contains  :";
	print_vct(myvector, stream);
	for (size_t i = 0; i < myvector.size(); i++)
		*stream << ' ' << myvector[i];
	*stream << std::endl;
}

template< class container, typename T >
static void	vct_reserve(T* values, std::stringstream *stream)
{
	typename container::size_type	sz;
	container						foo;

	sz = foo.capacity();
	*stream << "making foo grow  :\n";
	for (int i = 0; i < 10; ++i)
	{
		foo.push_back(values[i]);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			*stream << "capacity changed: " << sz << std::endl;
		}
	}

	container bar;
	sz = bar.capacity();
	bar.reserve(10);	// this is the only difference with foo above
	*stream << "making bar grow  :\n";
	for (int i = 0; i < 10; ++i)
	{
		bar.push_back(values[i]);
		if (sz != bar.capacity())
		{
			sz = bar.capacity();
			*stream << "capacity changed: " << sz << std::endl;
		}
	}
}

template< class container, typename T >
static void	vct_operator_brackets(T* values, std::stringstream *stream)
{
	container						myvector(10);	// 10 zero-initialized elements
	typename container::size_type	sz = myvector.size();

	// assign some values:
	for (unsigned i = 0; i < sz; i++) myvector[i] = values[i];
	// reverse vector using operator[]:
	for (unsigned i = 0; i < sz / 2; i++)
	{
		T		temp;
		temp = myvector[sz - 1 - i];
		myvector[sz - 1 - i] = myvector[i];
		myvector[i] = temp;
	}
	*stream << "myvector contains  :";
	for (unsigned i = 0; i < sz; i++)
		*stream << ' ' << myvector[i];
	*stream << std::endl;
}

template< class container, typename T >
static void	vct_at(T* values, std::stringstream *stream)
{
	container	myvector(10);	// 10 zero-initialized ints

	// assign some values:
	for (unsigned i = 0; i < myvector.size(); i++)
		myvector.at(i) = values[i];
	*stream << "myvector contains  :";
	for (unsigned i = 0; i < myvector.size(); i++)
		*stream << ' ' << myvector.at(i);
	*stream << std::endl;
	try {
		*stream << myvector.at(15); }
	catch(const std::out_of_range& e) {
		*stream << "Error: " << e.what() << std::endl; }
	try {
		*stream << myvector.at(-1); }
	catch(const std::out_of_range& e) {
		*stream << "Error: " << e.what() << std::endl; }
}

template< class container, typename T >
static void	vct_front(std::stringstream *stream)
{
	container	myvector;

	myvector.push_back(77);
	myvector.push_back(22);
	// now front equals 77, and back 22
	myvector.front() -= myvector.back();
	*stream << "myvector.front() is now   " << myvector.front() << std::endl;
}

template< class container, typename T >
static void	vct_back(std::stringstream *stream)
{
	container	myvector;

	myvector.push_back(10);
	while (myvector.back() != 0)
		myvector.push_back(myvector.back() - 1);
	*stream << "myvector contains  :";
	print_vct(myvector, stream);
}

template< class container, typename T >
static void	vct_assign(T* values, std::stringstream *stream)
{
	container						first;
	container						second;
	container						third;

	first.assign (7, values[5]);		// 7 ints with a value of 100

	typename container::iterator	it;

	it = first.begin() + 1;
	second.assign(it, first.end() - 1);	// the 5 central values of first
	third.assign(values, values + 3);	// assigning from array.
	*stream << "Size of first: " << int (first.size()) << std::endl;
	*stream << "Size of second: " << int (second.size()) << std::endl;
	*stream << "Size of third: " << int (third.size()) << std::endl;
}

template< class container, typename T >
static void	vct_push_back(T* values, std::stringstream *stream)
{
	container	myvector;

	myvector.push_back (values[0]);
	myvector.push_back (values[1]);
	myvector.push_back (values[2]);
	myvector.push_back (values[3]);
	myvector.push_back (values[4]);

	*stream << "myvector stores   " << myvector.size() << " numbers.\n";
}

template< class container, typename T >
static void	vct_pop_back(std::stringstream *stream)
{
	container	myvector;
	int			sum(0);

	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);
	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}
	*stream << "The elements of myvector summed   " << sum << std::endl;
}

template< class container, typename T >
static void	vct_insert(T* values, std::stringstream *stream)
{
	container						myvector;
	typename container::iterator	it;
	typename container::iterator	it2;

	// set some initial values:
	for (int i = 0; i <= 4; ++i)
		myvector.push_back(values[i]); 			 	// 1 2 3 4 5
	it = myvector.begin();
	++it;		// it points now to number 2             ^

	it2 = myvector.insert(it, values[5]);			// 1 10 2 3 4 5
	// "it" now points to number 10                      ^
	*stream << "it2(10)   :" << *it2 << std::endl;
	*stream << "it(10)   :" << *it << std::endl;
	print_vct(myvector, stream);
	++it;
	// "it" now points to number 2                          ^
	myvector.insert(it, 2, values[8]);				// 1 10 20 20 2 3 4 5
	*stream << "it(200)   :" << *it << std::endl;
	--it;		// it points now to 10                   ^
	*stream << "it(10)   :" << *it << std::endl;
	print_vct(myvector, stream);

	container	mylist(2, values[7]);
	myvector.insert(it, mylist.begin(), mylist.end());
													// 1 30 30 10 20 20 2 3 4 5
													//         ^
	*stream << "myvector contains  :";
	print_vct(myvector, stream);
}

template< class container, typename T >
static void	vct_erase(T* values, std::stringstream *stream)
{
	container						myvector;
	typename container::iterator	it1, it2;

	// set some values:
	for (int i = 0; i < 9; ++i)
		myvector.push_back(values[i]);
										// 10 20 30 40 50 60 70 80 90
	it1 = it2 = myvector.begin();		// ^^
	for(int i = 0; i < 6; ++i)			// ^                 ^
		++it2;
	++it1;								//    ^              ^
	it1 = myvector.erase(it1);			// 10 30 40 50 60 70 80 90
										//    ^           ^
	it2 = myvector.erase(it2);			// 10 30 40 50 60 80 90
										//    ^           ^
	++it1;								//       ^        ^
	--it2;								//       ^     ^
	myvector.erase (it1,it2);			// 10 30 60 80 90
										//        ^
	*stream << "myvector contains  :";
	print_vct(myvector, stream);
}

template< class container, typename T >
static void	vct_swap(T* values, std::stringstream *stream)
{
	container	first(3, values[5]);	// three ints with a value of 100
	container	second(5, values[7]);	// five ints with a value of 200

	first.swap(second);
	*stream << "first contains  :";
	print_vct(first, stream);
	*stream << "second contains  :";
	print_vct(second, stream);
}

template< class container, typename T >
static void	vct_clear(T* values, std::stringstream *stream)
{
	container						myvector;
	typename container::iterator	it;

	myvector.push_back(values[0]);
	myvector.push_back(values[1]);
	myvector.push_back(values[2]);
	*stream << "myvector contains  :";
	print_vct(myvector, stream);
	myvector.clear();
	myvector.push_back (values[5]);
	myvector.push_back (values[6]);
	*stream << "myvector contains  :";
	print_vct(myvector, stream);
}

template< class container, typename T >
static void	vct_relational_operators(T* values, std::stringstream *stream)
{
	container	a;
	a.push_back(values[0]);
	a.push_back(values[1]);
	a.push_back(values[2]);
	container	b;
	b.push_back(values[0]);
	b.push_back(values[1]);
	b.push_back(values[2]);
	container	c;
	c.push_back(values[2]);
	c.push_back(values[1]);
	c.push_back(values[0]);

	if (a==b) *stream << "a and b are equal\n";
	if (b!=c) *stream << "b and c are not equal\n";
	if (b<c) *stream << "b is less than c\n";
	if (c>b) *stream << "c is greater than b\n";
	if (a<=b) *stream << "a is less than or equal to b\n";
	if (a>=b) *stream << "a is greater than or equal to b\n";
}

template< class container, typename T >
static void	vct_swap_non_member(T* values, std::stringstream *stream)
{
	container	foo(3, values[5]);	// three ints with a value of 100
	container	bar(5, values[7]);	// five ints with a value of 200

	foo.push_back(values[1]);
	bar.push_back(values[3]);
	swap(foo, bar);

	*stream << "foo contains  :";
	print_vct(foo, stream);
	*stream << "capacity:" << foo.capacity() << std::endl;
	*stream << "bar contains  :";
	print_vct(bar, stream);
	*stream << "capacity:" << bar.capacity() << std::endl;
}

template< class container, typename T >
static void	vct_iterator_operations(T* values, std::stringstream *stream)
{
	container						foo;
	foo.push_back(values[0]);
	foo.push_back(values[1]);
	foo.push_back(values[2]);

	typename container::iterator	it0 = foo.begin();
	typename container::iterator	it1 = foo.begin() + 1;
	typename container::iterator	it2 = foo.begin();
	it2 -= 1;
	it2 += 3;
	typename container::iterator	it2b = foo.end() - 1;
	typename container::iterator	it3 = foo.end();

	if (it2 == it2b) *stream << "it2 == it2b\n";
	if (it1 != it2b) *stream << "it1 != it2b\n";
	it2++;
	if (it2 == it3) *stream << "it2++ == it3\n";
	it2--;
	if (it2 == it2b) *stream << "it2 == it2b\n";
	if (it2 < it3) *stream << "it2 < it3\n";
	if (it2 <= it3) *stream << "it2 <= it3\n";
	if (it3 > it2) *stream << "it3 > it2\n";
	if (it3 >= it2) *stream << "it3 >= it2\n";
	*stream << "it3 - it0:" << (it3 - it0) << std::endl;
	*stream << "it0[0]:" << it0[0] << std::endl;
	*stream << "it2[0]:" << it2[0] << std::endl;
	*stream << "it0[1]:" << it0[1] << std::endl;
	*stream << "*it0:" << *it0 << std::endl;
	*stream << "*it1:" << *it1 << std::endl;
}

template< class container, typename T >
static void	vct_rev_iterator_operations(T* values, std::stringstream *stream)
{
	container								foo;
	foo.push_back(values[0]);
	foo.push_back(values[1]);
	foo.push_back(values[2]);

	typename container::reverse_iterator	it0 = foo.rend();
	typename container::reverse_iterator	it1 = foo.rend() - 1;
	typename container::reverse_iterator	it2 = foo.rend();
	it2 += 1;
	it2 -= 3;
	typename container::reverse_iterator	it2b = foo.rbegin() + 1;
	typename container::reverse_iterator	it3 = foo.rbegin();
	*stream << "it1:" << *it1 << ", it2:" << *it2 << ", it2b:" << *it2b << ", it3:" << *it3 << std::endl;

	if (it2 == it2b) *stream << "it2 == it2b\n";
	if (it1 != it2b) *stream << "it1 != it2b\n";
	it2--;
	if (it2 == it3) *stream << "it2++ == it3\n";
	it2++;
	if (it2 == it2b) *stream << "it2 == it2b\n";
	if (it2 < it3) *stream << "it2 < it3\n";
	if (it2 <= it3) *stream << "it2 <= it3\n";
	if (it3 > it2) *stream << "it3 > it2\n";
	if (it3 >= it2) *stream << "it3 >= it2\n";
	*stream << "it3 - it0:" << (it0 - it3) << std::endl;
	*stream << "it3[0]:" << it3[0] << std::endl;
	*stream << "it2[0]:" << it2[0] << std::endl;
	*stream << "it3[1]:" << it3[1] << std::endl;
	*stream << "*it3:" << *it3 << std::endl;
	*stream << "*it1:" << *it1 << std::endl;
}

template< class container, typename T >
static void	vct_additional_tests(T* values, std::stringstream *stream)
{
	container							cont;

	cont.push_back(values[8]);
	cont.push_back(values[5]);
	cont.push_back(values[2]);

	typename container::iterator		begin = cont.begin();

	begin++;
	begin++;
	*stream << "begin:" << *begin << std::endl;
	begin = -2 + begin;
	*stream << "begin:" << *begin << std::endl;
	*stream << "size:" << cont.size() << std::endl;
}

static void	ft_comp_vct(std::stringstream *std_stream, std::stringstream *ft_stream, std::ofstream	*ofs1, std::ofstream *ofs2)
{
	if ((*std_stream).str() == (*ft_stream).str())
	{
		std::cout << "\x1B[32mOK\x1B[0m, ";
		*ofs1 << (*std_stream).str();
		*ofs1 << std::endl;
		*ofs1 << (*ft_stream).str();
		*ofs1 << std::endl;
	}
	else
	{
		std::cout << "\x1B[31mFAIL\x1B[0m, ";
		std::ofstream	ofs;

		*ofs2 << (*std_stream).str();
		*ofs2 << std::endl;
		*ofs2 << (*ft_stream).str();
		*ofs2 << std::endl;
	}
	(*std_stream).str(std::string());
	(*ft_stream).str(std::string());
}

template < typename T >
void		vector_test(T *values, std::ofstream	*ofs1, std::ofstream *ofs2)
{
	std::stringstream	std_stream;
	std::stringstream	ft_stream;

	std::cout << "const vector : ";
	vct_empty_vector< std::vector< T >, T >(values, &std_stream);
	vct_empty_vector< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "lenght error : ";
	vct_lenght_error< std::vector< T >, T >(values, &std_stream);
	vct_lenght_error< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "constructor test : ";
	vct_constructor_test< std::vector< T >, T >(values, &std_stream);
	vct_constructor_test< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "operator= : ";
	vct_operator_equal< std::vector< T >, T >(&std_stream);
	vct_operator_equal< ft::vector< T >, T >(&ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "begin() : ";
	vct_begin< std::vector< T >, T >(values, &std_stream);
	vct_begin< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "end() : ";
	vct_end< std::vector< T >, T >(values, &std_stream);
	vct_end< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "rbegin() : ";
	vct_rbegin< std::vector< T >, T >(values, &std_stream);
	vct_rbegin< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "rend() : ";
	vct_rend< std::vector< T >, T >(values, &std_stream);
	vct_rend< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "size() : ";
	vct_size< std::vector< T >, T  >(values, &std_stream);
	vct_size< ft::vector< T >, T  >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "max_size() : ";
	vct_max_size< std::vector< T >, T >(&std_stream);
	vct_max_size< ft::vector< T >, T >(&ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "resize() : ";
	vct_resize< std::vector< T >, T >(values, &std_stream);
	vct_resize< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "empty() : ";
	vct_empty< std::vector< int >, int >(&std_stream);
	vct_empty< ft::vector< int >, int >(&ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "capacity/reserve() : ";
	vct_reserve< std::vector< T >, T >(values, &std_stream);
	vct_reserve< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "operator[] : ";
	vct_operator_brackets< std::vector< T >, T >(values, &std_stream);
	vct_operator_brackets< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "at() : ";
	vct_at< std::vector< T >, T >(values, &std_stream);
	vct_at< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "front() : ";
	vct_front< std::vector< int >, int >(&std_stream);
	vct_front< ft::vector< int >, int >(&ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "back() : ";
	vct_back< std::vector< int >, int >(&std_stream);
	vct_back< ft::vector< int >, int >(&ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "assign() : ";
	vct_assign< std::vector< T >, T >(values, &std_stream);
	vct_assign< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "push_back() : ";
	vct_push_back< std::vector< T >, T >(values, &std_stream);
	vct_push_back< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "pop_back() : ";
	vct_pop_back< std::vector< int >, int >(&std_stream);
	vct_pop_back< ft::vector< int >, int >(&ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "insert() : ";
	vct_insert< std::vector< T >, T >(values, &std_stream);
	vct_insert< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "erase() : ";
	vct_erase< std::vector< T >, T >(values, &std_stream);
	vct_erase< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "swap() : ";
	vct_swap< std::vector< T >, T >(values, &std_stream);
	vct_swap< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "clear() : ";
	vct_clear< std::vector< T >, T >(values, &std_stream);
	vct_clear< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "relational operators : ";
	vct_relational_operators< std::vector< T >, T >(values, &std_stream);
	vct_relational_operators< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "swap (non-member) : ";
	vct_swap_non_member< std::vector< T >, T >(values, &std_stream);
	vct_swap_non_member< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "iterator operations : ";
	vct_iterator_operations< std::vector< T >, T >(values, &std_stream);
	vct_iterator_operations< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "reverse iterator operations : ";
	vct_rev_iterator_operations< std::vector< T >, T >(values, &std_stream);
	vct_rev_iterator_operations< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "additional tests : ";
	vct_additional_tests< std::vector< T >, T >(values, &std_stream);
	vct_additional_tests< ft::vector< T >, T >(values, &ft_stream);
	ft_comp_vct(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << std::endl;
}
