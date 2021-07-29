/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_list.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:08:32 by olidon            #+#    #+#             */
/*   Updated: 2021/03/14 18:24:38 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

template< class container >
static void print_lst(container const &list, std::stringstream *stream)
{
	typename container::const_iterator ite = list.end();

	for (typename container::const_iterator it = list.begin(); it != ite; ++it)
		*stream << *it << ' ';
	*stream << std::endl;
}

template< class container, typename T >
void	lst_empty_list(T* values, std::stringstream *stream)
{
	container const constDoubleVec(1, values[1]);
	container first;								// empty list of ints
	*stream << "list first ok\n";
	*stream << "first max  : " << first.max_size() << std::endl;
	*stream << "first size  : " << first.size() << std::endl;
}

template< class container, typename T >
static void	lst_four_value_hundred(T* values, std::stringstream *stream)
{
	container tmp(4, values[5]);
	*stream << "tmp ok\n";
	*stream << "print_lst list tmp\n";
	print_lst(tmp, stream);
	*stream << "------ LIST FROM ITERATORS ------\n";
	typename container::const_iterator it = tmp.begin();
	typename container::const_iterator ite = tmp.end();
	*stream << "it :" << (*it) << std::endl;
	container second(it, ite);						// four ints with value 100
	*stream << "list second ok\n";
	*stream << "print_lst list second\n";
	print_lst(second, stream);
	second.push_front(values[4]);
	second.push_back(values[6]);
	*stream << "second front  : " << second.front() << std::endl;
	*stream << "second back  : " << second.back() << std::endl;
	second.pop_front();
	second.pop_back();
	*stream << "second front  : " << second.front() << std::endl;
	*stream << "second back  : " << second.back() << std::endl;
	typename container::iterator secondit = second.begin();
	secondit++;
	*stream << "second iterator creation ok\n";
	*stream << "------ LIST FROM ITERATORS ------\n";
	container third(second.begin(), second.end());	// iterating through second
	*stream << "list third ok\n";
	*stream << "print_lst list third\n";
	print_lst(third, stream);
	*stream << "------ LIST FROM COPY ------\n";
	container fourth(third);						// a copy of third
	*stream << "list fourth ok\n";
	*stream << "print_lst list fourth\n";
	print_lst(fourth, stream);
}

template< class container, typename T >
static void	lst_operator_equal(std::stringstream *stream)
{
	container	first(3);      // list of 3 zero-initialized ints
	container	second(5);     // list of 5 zero-initialized ints

	second = first;
	first = container();

	*stream << "Size of first  : " << int (first.size()) << std::endl;
	*stream << "Size of second  : " << int (second.size()) << std::endl;
}

template< class container, typename T >
static void	lst_begin(T* values, std::stringstream *stream)
{
	container mylist (values,values+5);

	*stream << "mylist contains  :";
	for (typename container::iterator it=mylist.begin(); it != mylist.end(); ++it)
		*stream << ' ' << *it;
	*stream << std::endl;

	container const mylistconst (values,values+5);

	*stream << "mylistconst contains  :";
	for (typename container::const_iterator itconst=mylistconst.begin(); itconst != mylistconst.end(); ++itconst)
		*stream << ' ' << *itconst;
	*stream << std::endl;
}

template< class container, typename T >
static void	lst_end(T* values, std::stringstream *stream)
{
	container mylist (values,values+5);

	*stream << "mylist contains  :";
	for (typename container::iterator it=mylist.begin() ; it != mylist.end(); ++it)
		*stream << ' ' << *it;
	*stream << std::endl;
}

template< class container, typename T >
static void	lst_rbegin(T* values, std::stringstream *stream)
{
	container mylist;
	for (int i=1; i<=5; ++i) mylist.push_back(values[i]);

	*stream << "mylist backwards  :";
	for (typename container::reverse_iterator rit=mylist.rbegin(); rit!=mylist.rend(); ++rit)
		*stream << ' ' << *rit;
	*stream << std::endl;

	container const mylistconst(values,values+5);

	*stream << "mylistconst backwards  :";
	for (typename container::const_reverse_iterator ritconst=mylistconst.rbegin(); ritconst!=mylistconst.rend(); ++ritconst)
		*stream << ' ' << *ritconst;
	*stream << std::endl;

	typename container::reverse_iterator	rit2(mylist.begin());
	*stream << "reverse iterator copy construction from forward iterator\n";
}

template< class container, typename T >
static void	lst_rend(T* values, std::stringstream *stream)
{
	container mylist;
	for (int i=1; i<=5; ++i) mylist.push_back(values[i]);

	*stream << "mylist backwards  :";
	for (typename container::reverse_iterator rit=mylist.rbegin(); rit!=mylist.rend(); ++rit)
		*stream << ' ' << *rit;
	*stream << std::endl;
}

template< class container, typename T >
static void	lst_empty(std::stringstream *stream)
{
	container mylist;
	int sum (0);

	for (int i=1;i<=10;++i) mylist.push_back(i);

	while (!mylist.empty())
	{
		sum += mylist.front();
		mylist.pop_front();
	}

	*stream << "total  : " << sum << std::endl;
	*stream << std::endl;
}

template< class container, typename T >
static void	lst_size(T* values, std::stringstream *stream)
{
	container	myints;
	*stream << "0. size  : " << myints.size() << std::endl;

	for (int i = 0; i < 10; i++) myints.push_back(values[i]);
	*stream << "1. size  : " << myints.size() << std::endl;

	myints.insert (myints.begin(), 10, values[5]);
	*stream << "2. size  : " << myints.size() << std::endl;

	myints.pop_back();
	*stream << "3. size  : " << myints.size() << std::endl;
	*stream << "print_lst list myints\n";
	print_lst(myints, stream);
}

template< class container, typename T >
static void	lst_max_size(std::stringstream *stream)
{
	container	mylist;
	*stream << "mylist max size  : " << mylist.max_size() << std::endl;
}

template< class container, typename T >
static void	lst_front(std::stringstream *stream)
{
	container	mylist;

	mylist.push_back(77);
	mylist.push_back(22);

	// now front equals 77, and back 22

	mylist.front() -= mylist.back();

	*stream << "mylist.front() is now   " << mylist.front() << std::endl;
	*stream << std::endl;
}

template< class container, typename T >
static void	lst_back(std::stringstream *stream)
{
	container	mylist;

	mylist.push_back(10);
	while (mylist.back() != 0)
		mylist.push_back(mylist.back() - 1);
	*stream << "mylist contains  :";
	print_lst(mylist, stream);
}

template< class container, typename T >
static void	lst_assign(T* values, std::stringstream *stream)
{
	container	first;
	container	second;

	first.assign(7, values[5]);						// 7 ints with value 100
	second.assign(first.begin(), first.end());		// a copy of first
	first.assign(values, values + 3);				// assigning from array
	*stream << "Size of first  : " << int (first.size()) << std::endl;
	*stream << "Size of second  : " << int (second.size()) << std::endl;
}

template< class container, typename T >
static void	lst_push_front(T* values, std::stringstream *stream)
{
	container	mylist(2, values[5]);						// two ints with a value of 100

	mylist.push_front(values[6]);
	mylist.push_front(values[7]);
	*stream << "mylist contains  :";
	print_lst(mylist, stream);
}

template< class container, typename T >
void	lst_pop_front(T* values, std::stringstream *stream)
{
	container	mylist;

	mylist.push_back(values[5]);
	mylist.push_back(values[6]);
	mylist.push_back(values[7]);
	*stream << "Popping out the elements in mylist:  ";
	while (!mylist.empty())
	{
		*stream << ' ' << mylist.front();
		mylist.pop_front();
	}
	*stream << "\nFinal size of mylist is   " << mylist.size() << std::endl;
}

template< class container, typename T >
static void	lst_push_back(T* values, std::stringstream *stream)
{
	container	mylist;

	mylist.push_back(values[0]);
	mylist.push_back(values[1]);
	mylist.push_back(values[2]);
	mylist.push_back(values[3]);
	mylist.push_back(values[4]);
	mylist.push_back(values[5]);
	mylist.push_back(values[6]);
	*stream << "mylist stores " << mylist.size() << " numbers.\n";
}

template< class container, typename T >
static void	lst_pop_back(std::stringstream *stream)
{
	container mylist;
	int sum (0);
	mylist.push_back (100);
	mylist.push_back (200);
	mylist.push_back (300);

	while (!mylist.empty())
	{
		sum += mylist.back();
		mylist.pop_back();
	}
	*stream << std::endl;
	*stream << "The elements of mylist summed   " << sum << std::endl;
}

template< class container, typename T >
static void	lst_insert(T* values, std::stringstream *stream)
{
	container				mylist;
	typename container::iterator	it;

	// set some initial values:
	for (int i=0; i<=4; ++i)
		mylist.push_back(values[i]); 				// 1 2 3 4 5
	it = mylist.begin();
	++it;       // it points now to number 2             ^

	it = mylist.insert (it, values[8]);				// 1 10 2 3 4 5
	// "it" still points to number 2                        ^
	*stream << "it(250)   :" << *it << std::endl;
	++it;
	mylist.insert (it, 2, values[7]);				// 1 10 20 20 2 3 4 5
	--it;       // it points now to the second 20              ^

	container myvector (2,values[6]);
	mylist.insert (it, myvector.begin(), myvector.end());
													// 1 10 20 30 30 20 2 3 4 5
													//               ^
	*stream << "mylist contains  :";
	print_lst(mylist, stream);
}

template< class container, typename T >
static void	lst_erase(T* values, std::stringstream *stream)
{
	container						mylist;
	typename container::iterator	it1, it2;

	// set some values:
	for (int i = 0; i < 9; ++i)
		mylist.push_back(values[i]);
										// 1 2 3 4 5 6 7 8 9
	it1 = it2 = mylist.begin();			// ^
	for(int i = 0; i < 6; ++i)			// ^         ^
		++it2;
	++it1;								//   ^       ^
	it1 = mylist.erase(it1);			// 1 3 4 5 6 7 8 9
										//   ^       ^
	it2 = mylist.erase(it2);			// 1 3 4 5 6 8 9
										//   ^       ^
	++it1;								//     ^     ^
	--it2;								//     ^   ^
	mylist.erase(it1, it2);				// 1 3 6 8 9
										//     ^
	*stream << "mylist contains:";
	print_lst(mylist, stream);
}

template< class container, typename T >
static void	lst_swap(T* values, std::stringstream *stream)
{
	container	first(3, values[5]);	// three ints with a value of 100
	container	second(5, values[6]);	// five ints with a value of 200

	first.swap(second);
	*stream << "first contains  :";
	print_lst(first, stream);
	*stream << "second contains  :";
	print_lst(second, stream);
}

template< class container, typename T >
static void	lst_resize(T* values, std::stringstream *stream)
{
	container mylist;

	for (int i = 1; i < 8; ++i) mylist.push_back(values[i]);
	mylist.resize(5);
	mylist.resize(8, values[0]);
	mylist.resize(12);
	*stream << mylist.size() << std::endl;
	// *stream << "mylist contains  :";
	// print_lst(mylist, stream);
}

template< class container, typename T >
static void	lst_clear(T* values, std::stringstream *stream)
{
	container mylist;
	typename container::iterator it;

	mylist.push_back (values[5]);
	mylist.push_back (values[6]);
	mylist.push_back (values[7]);

	*stream << "mylist contains  :";
	print_lst(mylist, stream);

	mylist.clear();
	mylist.push_back (values[8]);
	mylist.push_back (values[8]);

	*stream << "mylist contains  :";
	print_lst(mylist, stream);
}

template< class container, typename T >
static void	lst_splice(T* values, std::stringstream *stream)
{
	container						mylist1, mylist2;
	typename container::iterator	it;

	// set some initial values:
	for (int i = 0; i <= 3; ++i)
		mylist1.push_back(values[i]);		// mylist1: 1 2 3 4

	for (int i = 4; i <= 6; ++i)
		mylist2.push_back(values[i]);		// mylist2: 5 100 150
	it = mylist1.begin();
	++it;									// points to 2
	mylist1.splice(it, mylist2);			// mylist1: 1 5 100 150 2 3 4
											// mylist2 (empty)
											// "it" still points to 2 (the 5th element)
	mylist2.splice (mylist2.begin(),mylist1, it);
											// mylist1: 1 5 100 200 3 4
											// mylist2: 2
											// "it" is now invalid.
	it = mylist1.begin();
	it++;
	it++;
	it++;									// "it" points now to 150
	mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
											// mylist1: 150 3 4 1 5 100
	*stream << "mylist1 contains  :";
	print_lst(mylist1, stream);
	*stream << "mylist2 contains  :";
	print_lst(mylist2, stream);
	mylist1.splice(mylist1.end(), mylist1, mylist1.begin(), mylist1.end());
	*stream << "mylist1 contains  :";
	print_lst(mylist1, stream);
	mylist2.splice(mylist2.end(), mylist2, mylist2.begin());
	*stream << "mylist2 contains  :";
	print_lst(mylist2, stream);
	mylist2.splice(mylist2.end(), mylist2, mylist2.end());
	*stream << "mylist2 contains  :";
	print_lst(mylist2, stream);
}

template< class container, typename T >
static void	lst_remove(T* values, std::stringstream *stream)
{
	container	mylist(values,values + 4);

	mylist.remove(values[2]);

	*stream << "mylist contains  :";
	print_lst(mylist, stream);
	*stream << std::endl;
}

// a predicate implemented as a function:
static bool	single_digit(const int& value)
{
	return (value < 10);
}

// a predicate implemented as a class:
struct	is_odd
{
	bool	operator()(const int& value)
	{
		return (value % 2) == 1;
	}
};

template< class container, typename T >
static void	lst_remove_if(std::stringstream *stream)
{
	int			myints[] = {15, 36, 7, 17, 20, 39, 4, 1};
	container	mylist(myints, myints + 8);			// 15 36 7 17 20 39 4 1

	mylist.remove_if(single_digit);					// 15 36 17 20 39
	mylist.remove_if(is_odd());						// 36 20
	*stream << "mylist contains:";
	print_lst(mylist, stream);
}

// a binary predicate implemented as a function:
static bool	same_integral_part(double first, double second)
{
	return ( int(first)==int(second) );
}

// a binary predicate implemented as a class:
struct	is_near
{
	bool	operator()(double first, double second)
	{
		return (fabs(first-second) < 5.0);
	}
};

template< class container, typename T >
static void	lst_unique(std::stringstream *stream)
{
	double		mydoubles[] = { 12.15, 2.72,  73.0,  12.77, 3.14,
								12.77, 73.35, 72.25, 15.3,  72.25};
	container	mylist(mydoubles,mydoubles+10);

	mylist.sort();							//  2.72,  3.14, 12.15, 12.77, 12.77,
											// 15.3,  72.25, 72.25, 73.0,  73.35
	mylist.unique();						//  2.72,  3.14, 12.15, 12.77
											// 15.3,  72.25, 73.0,  73.35
	mylist.unique (same_integral_part);		//  2.72,  3.14, 12.15
											// 15.3,  72.25, 73.0
	mylist.unique (is_near());				//  2.72, 12.15, 72.25
	*stream << "mylist contains  :";
	print_lst(mylist, stream);
}

// compare only integral part:
static bool mycomparison (double first, double second)
{
	return ( int(first)<int(second) );
}

template< class container, typename T >
static void	lst_merge(std::stringstream *stream)
{
	std::list<double> first, second;

	first.push_back (3.1);
	first.push_back (2.2);
	first.push_back (2.9);
	second.push_back (3.7);
	second.push_back (7.1);
	second.push_back (1.4);
	first.sort();
	second.sort();
	first.merge(second);
	// (second is now empty)
	second.push_back (2.1);
	first.merge(second,mycomparison);
	*stream << "first contains  :";
	print_lst(first, stream);
}

static bool compare_nocase (const std::string& first, const std::string& second)
{
	unsigned int	i = 0;

	while ( (i<first.length()) && (i<second.length()) )
	{
		if (tolower(first[i])<tolower(second[i]))
			return true;
		else if (tolower(first[i])>tolower(second[i]))
			return false;
		++i;
	}
	return ( first.length() < second.length() );
}

template< class container, typename T >
static void	lst_sort(std::stringstream *stream)
{
	container						mylist;
	typename container::iterator	it;

	mylist.push_back ("one");
	mylist.push_back ("two");
	mylist.push_back ("Three");
	mylist.sort();
	*stream << "mylist contains  :";
	print_lst(mylist, stream);
	mylist.sort(compare_nocase);
	*stream << "mylist contains  :";
	print_lst(mylist, stream);
}

template< class container, typename T >
static void	lst_reverse(T* values, std::stringstream *stream)
{
	container	mylist;

	for (int i = 1; i < 10; ++i)
		mylist.push_back(values[i]);
	mylist.reverse();
	*stream << "mylist contains  :";
	print_lst(mylist, stream);
}

template< class container, typename T >
static void	lst_relational_operators(T* values, std::stringstream *stream)
{
	container a;
	a.push_back(values[0]);
	a.push_back(values[1]);
	a.push_back(values[2]);
	container b;
	b.push_back(values[0]);
	b.push_back(values[1]);
	b.push_back(values[2]);
	container c;
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
static void	lst_swap_non_member(T* values, std::stringstream *stream)
{
	container	foo(3, values[5]);	// three ints with a value of 100
	container	bar(5,values[6]);	// five ints with a value of 200

	std::swap(foo,bar);
	*stream << "foo contains  :";
	print_lst(foo, stream);
	*stream << "bar contains  :";
	print_lst(bar, stream);
}

template< class container, typename T >
static void	lst_iterator_operations(T* values, std::stringstream *stream)
{
	container						foo;
	foo.push_back(values[0]);
	foo.push_back(values[1]);
	foo.push_back(values[2]);

	typename container::iterator	it0 = foo.begin();
	typename container::iterator	it1 = foo.begin();
	it1++;
	typename container::iterator	it2 = foo.begin();
	it2--;
	it2++;
	it2++;
	it2++;
	typename container::iterator	it2b = foo.end();
	it2b--;
	typename container::iterator	it3 = foo.end();

	if (it2 == it2b) *stream << "it2 == it2b\n";
	if (it1 != it2b) *stream << "it1 != it2b\n";
	it2++;
	if (it2 == it3) *stream << "it2++ == it3\n";
	it2--;
	if (it2 == it2b) *stream << "it2 == it2b\n";
	*stream << "*it0:" << *it0 << std::endl;
	*stream << "*it1:" << *it1 << std::endl;
}

template< class container, typename T >
static void	lst_reverse_iterator_operations(T* values, std::stringstream *stream)
{
	container								foo;
	foo.push_back(values[0]);
	foo.push_back(values[1]);
	foo.push_back(values[2]);

	// container::reverse_iterator	it0 = foo.rend();
	typename container::reverse_iterator	it1 = foo.rend();
	it1--;
	typename container::reverse_iterator	it2 = foo.rend();
	it2--;
	it2++;
	it2--;
	it2--;
	typename container::reverse_iterator	it2b = foo.rbegin();
	it2b++;
	typename container::reverse_iterator	it3 = foo.rbegin();

	*stream << "it1:" << *it1 << ", it2:" << *it2 << ", it2b:" << *it2b << ", it3:" << *it3 << std::endl;
	if (it2 == it2b) *stream << "it2 == it2b\n";
	if (it1 != it2b) *stream << "it1 != it2b\n";
	it2--;
	if (it2 == it3) *stream << "it2++ == it3\n";
	it2++;
	if (it2 == it2b) *stream << "it2 == it2b\n";
	*stream << "*it3:" << *it3 << std::endl;
	*stream << "*it1:" << *it1 << std::endl;
}

static void	ft_comp_lst(std::stringstream *std_stream, std::stringstream *ft_stream, std::ofstream	*ofs1, std::ofstream *ofs2)
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
void		list_test(T *values, std::ofstream	*ofs1, std::ofstream *ofs2)
{
	std::stringstream	std_stream;
	std::stringstream	ft_stream;

	std::cout << "Empty : ";
	lst_empty_list< std::list< T > >(values, &std_stream);
	lst_empty_list< ft::list< T > >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "constructors : ";
	lst_four_value_hundred< std::list< T >, T >(values, &std_stream);
	lst_four_value_hundred< ft::list< T > , T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "operator= : ";
	lst_operator_equal< std::list< T >, T >(&std_stream);
	lst_operator_equal< ft::list< T >, T >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "begin() : ";
	lst_begin< std::list< T >, T >(values, &std_stream);
	lst_begin< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "end() : ";
	lst_end< std::list< T >, T >(values, &std_stream);
	lst_end< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "rbegin() : ";
	lst_rbegin< std::list< T >, T >(values, &std_stream);
	lst_rbegin< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "rend() : ";
	lst_rend< std::list< T >, T >(values, &std_stream);
	lst_rend< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "empty() : ";
	lst_empty< std::list< int >, int >(&std_stream);
	lst_empty< ft::list< int >, int >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "size() : ";
	lst_size< std::list< T >, T >(values, &std_stream);
	lst_size< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "max_size() : ";
	lst_max_size< std::list< T >, T >(&std_stream);
	lst_max_size< ft::list< T >, T >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "front() : ";
	lst_front< std::list< int >, int >(&std_stream);
	lst_front< ft::list< int >, int >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "back() : ";
	lst_back< std::list< int >, int >(&std_stream);
	lst_back< ft::list< int >, int >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "assign() : ";
	lst_assign< std::list< T >, T >(values, &std_stream);
	lst_assign< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "push_front() : ";
	lst_push_front< std::list< T >, T >(values, &std_stream);
	lst_push_front< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "pop_front() : ";
	lst_pop_front< std::list< T >, T >(values, &std_stream);
	lst_pop_front< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "push_back() : ";
	lst_push_back< std::list< T >, T >(values, &std_stream);
	lst_push_back< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "pop_back() : ";
	lst_pop_back< std::list< int >, int >(&std_stream);
	lst_pop_back< ft::list< int >, int >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "insert() : ";
	lst_insert< std::list< T >, T >(values, &std_stream);
	lst_insert< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "erase() : ";
	lst_erase< std::list< T >, T >(values, &std_stream);
	lst_erase< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "swap() : ";
	lst_swap< std::list< T >, T >(values, &std_stream);
	lst_swap< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "resize() : ";
	lst_resize< std::list< T >, T >(values, &std_stream);
	lst_resize< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "clear() : ";
	lst_clear< std::list< T >, T >(values, &std_stream);
	lst_clear< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "splice() : ";
	lst_splice< std::list< T >, T >(values, &std_stream);
	lst_splice< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "remove() : ";
	lst_remove< std::list< T >, T >(values, &std_stream);
	lst_remove< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "remove_if() : ";
	lst_remove_if< std::list< int >, int >(&std_stream);
	lst_remove_if< ft::list< int >, int >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "unique() : ";
	lst_unique< std::list< double >, double >(&std_stream);
	lst_unique< ft::list< double >, double >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "merge() : ";
	lst_merge< std::list< double >, double >(&std_stream);
	lst_merge< ft::list< double >, double >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "sort() : ";
	lst_sort< std::list< std::string >, std::string >(&std_stream);
	lst_sort< ft::list< std::string >, std::string >(&ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "reverse() : ";
	lst_reverse< std::list< T >, T >(values, &std_stream);
	lst_reverse< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "relational operator : ";
	lst_relational_operators< std::list< T >, T >(values, &std_stream);
	lst_relational_operators< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "swap (non-member) ; ";
	lst_swap_non_member< std::list< T >, T >(values, &std_stream);
	lst_swap_non_member< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "iterators operations : ";
	lst_iterator_operations< std::list< T >, T >(values, &std_stream);
	lst_iterator_operations< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "reverse iterators operations : ";
	lst_reverse_iterator_operations< std::list< T >, T >(values, &std_stream);
	lst_reverse_iterator_operations< ft::list< T >, T >(values, &ft_stream);
	ft_comp_lst(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << std::endl;
}
