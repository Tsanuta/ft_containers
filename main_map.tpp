/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:08:32 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 13:13:57 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

template< class container >
static void	printmap(container const &first, std::stringstream *stream)
{
	for (typename container::const_iterator it = first.begin(); it != first.end(); ++it)
		*stream << it->first << " => " << it->second << '\n';
}

template <class Key>
struct classcomp {
	bool operator() (const Key& lhs, const Key& rhs) const {
		return lhs < rhs; }
};

template <class Key>
struct classcomprev {
	bool operator() (const Key& lhs, const Key& rhs) const {
		return lhs > rhs; }
};

template <class T>
static bool fncomp (T lhs, T rhs)
{
	return lhs < rhs;
}

template <class T>
static bool fncomprev (T lhs, T rhs)
{
	return lhs > rhs;
}

template< class container, typename Key, typename T >
void	map_const_test(std::stringstream *stream)
{
	container const	first;								// empty map of chars
	*stream << "map first ok\n";
}

template< class container, class container2, class container3, class container4, typename Key, typename T >
static void	map_constructor_test(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	first;

	first[values[0].first] = values[0].second;
	first[values[1].first] = values[1].second;
	first[values[2].first] = values[2].second;
	first[values[3].first] = values[3].second;

	*stream << "first contains:\n";
	printmap(first, stream);

	container	second (first.begin(), first.end());
	*stream << "second contains:\n";
	printmap(second, stream);

	container	third (second);
	*stream << "third contains:\n";
	printmap(third, stream);

	container2	fourth;					// class as Compare
	fourth[values[0].first] = values[0].second;
	fourth[values[1].first] = values[1].second;
	fourth[values[2].first] = values[2].second;
	fourth[values[3].first] = values[3].second;
	*stream << "fourth contains:\n";
	printmap(fourth, stream);

	bool(*fn_pt)(Key, Key) = fncomp<Key>;
	container3	fifth(fn_pt);			// function pointer as Compare
	fifth[values[0].first] = values[0].second;
	fifth[values[1].first] = values[1].second;
	fifth[values[2].first] = values[2].second;
	fifth[values[3].first] = values[3].second;\
	*stream << "fifth contains:\n";
	printmap(fifth, stream);

	container4	six;					// class as Compare
	six[values[0].first] = values[0].second;
	six[values[1].first] = values[1].second;
	six[values[2].first] = values[2].second;
	six[values[3].first] = values[3].second;
	*stream << "six contains:\n";
	printmap(six, stream);

	bool(*fn_ptrev)(Key, Key) = fncomprev<Key>;
	container3	seven(fn_ptrev);			// function pointer as Compare
	seven[values[0].first] = values[0].second;
	seven[values[1].first] = values[1].second;
	seven[values[2].first] = values[2].second;
	seven[values[3].first] = values[3].second;\
	*stream << "seven contains:\n";
	printmap(seven, stream);
}

template< class container, typename Key, typename T >
static void	map_operator_equal(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	first;
	container	second;

	first[values[0].first] = values[0].second;
	first[values[1].first] = values[1].second;
	first[values[2].first] = values[2].second;

	second = first;				// second now contains 3 ints
	first = container();		// and first is now empty

	*stream << "Size of first : " << first.size() << '\n';
	*stream << "Size of second: " << second.size() << '\n';
}

template< class container, typename Key, typename T >
static void	map_begin(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	mymap;

	mymap[values[2].first] = values[2].second;
	mymap[values[0].first] = values[0].second;
	mymap[values[3].first] = values[3].second;
	mymap[values[1].first] = values[1].second;

	// show content:
	*stream << "mymap iter contains:\n";
	for (typename container::iterator it = mymap.begin(); it != mymap.end(); ++it)
		*stream << it->first << " => " << it->second << '\n';

	*stream << "mymap const_iter contains:\n";
	for (typename container::const_iterator itconst = mymap.begin(); itconst != mymap.end(); ++itconst)
		*stream << itconst->first << " => " << itconst->second << '\n';
}

template< class container, typename Key, typename T >
static void	map_rbegin(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	mymap;
	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	mymap[values[2].first] = values[2].second;
	mymap[values[3].first] = values[3].second;
	mymap[values[4].first] = values[4].second;

	*stream << "mymap rev_iter backwards:\n";
	for (typename container::reverse_iterator rit=mymap.rbegin(); rit != mymap.rend(); ++rit)
		*stream << rit->first << " => " << rit->second << '\n';
	*stream << "mymap const_rev_iter backwards:\n";
	for (typename container::const_reverse_iterator ritconst = mymap.rbegin(); ritconst != mymap.rend(); ++ritconst)
		*stream << ritconst->first << " => " << ritconst->second << '\n';
	typename container::reverse_iterator	rit2(mymap.begin());
	*stream << "reverse iterator copy construction from forward iterator\n";
}

template< class container, typename Key, typename T >
static void	map_empty(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	mymap;

	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	mymap[values[2].first] = values[2].second;

	while (!mymap.empty())
	{
		*stream << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
	}
}

template< class container, typename Key, typename T >
static void	map_size(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	mymap;

	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	mymap[values[2].first] = values[2].second;
	*stream << "mymap.size() is " << mymap.size() << '\n';
	mymap[values[3].first] = values[3].second;
	*stream << "mymap.size() is " << mymap.size() << '\n';
	mymap[values[3].first] = values[5].second;
	*stream << "mymap.size() is " << mymap.size() << '\n';
}

template< class container, typename Key, typename T >
static void	map_max_size(std::stringstream *stream)
{
	container	mymap;

	*stream << "mymap max size  : " << mymap.max_size() << '\n';
}

template< class container, typename Key, typename T >
static void	map_operator_brackets(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	mymap;

	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	mymap[values[2].first] = mymap[values[1].first];

	*stream << "mymap['a'] is " << mymap[values[0].first] << '\n';
	*stream << "mymap['b'] is " << mymap[values[1].first] << '\n';
	*stream << "mymap['c'] is " << mymap[values[2].first] << '\n';
	*stream << "mymap['d'] is " << mymap[values[3].first] << '\n';
	*stream << "mymap now contains " << mymap.size() << " elements.\n";
}

template< class container, typename Key, typename T >
void	map_insert(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	mymap;

	// first insert function version (single parameter):
	mymap.insert(values[0]);
	mymap.insert(values[8]);

	std::pair< typename container::iterator, bool >	ret;
	ret = mymap.insert(std::pair<Key,T>(values[8].first, values[6].second));
	if (ret.second == false)
	{
		*stream << "element 'z' already existed";
		*stream << " with a value of " << ret.first->second << '\n';
	}
	// second insert function version (with hint position):
	typename container::iterator	it = mymap.begin();
	mymap.insert(it, values[1]);	// max efficiency inserting
	mymap.insert(it, values[2]);	// no max efficiency inserting
	// third insert function version (range insertion):
	container	anothermap;
	anothermap.insert(mymap.begin(), mymap.find(values[2].first));
	// showing contents:
	*stream << "mymap contains:\n";
	printmap(mymap, stream);
	*stream << "anothermap contains:\n";
	printmap(anothermap, stream);
}

template< class container, typename Key, typename T >
void	map_erase(std::pair<Key, T> *values, std::stringstream *stream)
{
	container						mymap;
	typename container::iterator	it;

	// insert some values:
	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	mymap[values[2].first] = values[2].second;
	mymap[values[3].first] = values[3].second;
	mymap[values[4].first] = values[4].second;
	mymap[values[5].first] = values[5].second;
	it = mymap.find(values[1].first);
	mymap.erase(it);					// erasing by iterator
	mymap.erase(values[2].first);		// erasing by key
	it = mymap.find(values[4].first);
	mymap.erase(it, mymap.end());		// erasing by range
	printmap(mymap, stream);

	container						mymap2;
	typename container::iterator	it2;

	// insert some values:
	mymap2[values[3].first] = values[3].second;
	mymap2[values[1].first] = values[1].second;
	mymap2[values[0].first] = values[0].second;
	mymap2[values[5].first] = values[5].second;
	mymap2[values[2].first] = values[2].second;
	mymap2[values[4].first] = values[4].second;
	it2 = mymap2.find(values[1].first);
	mymap2.erase(it2);					// erasing by iterator
	mymap2.erase(values[2].first);		// erasing by key
	it2 = mymap2.find(values[4].first);
	mymap2.erase(it2, mymap2.end());	// erasing by range
	printmap(mymap2, stream);
}

template< class container, typename Key, typename T >
void	map_swap(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	foo, bar;

	foo[values[7].first] = values[7].second;
	foo[values[8].first] = values[8].second;
	bar[values[0].first] = values[0].second;
	bar[values[1].first] = values[1].second;
	bar[values[2].first] = values[2].second;
	foo.swap(bar);
	*stream << "foo contains:\n";
	printmap(foo, stream);
	*stream << "bar contains:\n";
	printmap(bar, stream);
}

template< class container, typename Key, typename T >
void	map_clear(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	mymap;

	mymap[values[7].first] = values[7].second;
	mymap[values[8].first] = values[8].second;
	mymap[values[9].first] = values[9].second;
	*stream << "mymap contains:\n";
	printmap(mymap, stream);
	mymap.clear();
	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	*stream << "mymap contains:\n";
	printmap(mymap, stream);
}

template< class container, typename Key, typename T >
void	map_key_comp(std::pair<Key, T> *values, std::stringstream *stream)
{
	container						mymap;

	typename container::key_compare	mycomp = mymap.key_comp();
	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	mymap[values[2].first] = values[2].second;
	*stream << "mymap contains:\n";

	Key								highest = mymap.rbegin()->first;	// key value of last element
	typename container::iterator	it = mymap.begin();

	do {
		*stream << it->first << " => " << it->second << '\n';
	} while (mycomp((*it++).first, highest));
	*stream << '\n';
}

template< class container, typename Key, typename T >
void	map_value_comp(std::pair<Key, T> *values, std::stringstream *stream)
{
	container						mymap;

	mymap[values[6].first] = values[6].second;
	mymap[values[7].first] = values[7].second;
	mymap[values[8].first] = values[8].second;
	*stream << "mymap contains:\n";

	std::pair<Key,T>				highest = *mymap.rbegin();	// last element
	typename container::iterator	it = mymap.begin();

	do {
		*stream << it->first << " => " << it->second << '\n';
	} while (mymap.value_comp()(*it++, highest));
}

template< class container, typename Key, typename T >
void	map_find(std::pair<Key, T> *values, std::stringstream *stream)
{
	container						mymap;
	typename container::iterator	it;

	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	mymap[values[2].first] = values[2].second;
	mymap[values[3].first] = values[3].second;
	it = mymap.find(values[1].first);
	if (it != mymap.end())
		mymap.erase (it);
	// print content:
	*stream << "elements in mymap:" << '\n';
	*stream << "a => " << mymap.find(values[0].first)->second << '\n';
	*stream << "c => " << mymap.find(values[2].first)->second << '\n';
	*stream << "d => " << mymap.find(values[3].first)->second << '\n';
}

template< class container, typename Key, typename T >
void	map_count(std::pair<Key, T> *values, std::stringstream *stream)
{
	container	mymap;
	int			c;

	mymap[1] = values[0].second;
	mymap[3] = values[2].second;
	mymap[6] = values[5].second;

	for (c = 1; c < 9; c++)
	{
		*stream << c;
		if (mymap.count(c) > 0)
			*stream << " is an element of mymap.\n";
		else
			*stream << " is not an element of mymap.\n";
	}
}

template< class container, typename Key, typename T >
void	map_lower_upper_bound(std::pair<Key, T> *values, std::stringstream *stream)
{
	container						mymap;
	typename container::iterator	itlow, itup;

	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	mymap[values[2].first] = values[2].second;
	mymap[values[3].first] = values[3].second;
	mymap[values[4].first] = values[4].second;
	itlow = mymap.lower_bound(values[1].first);		// itlow points to b
	itup = mymap.upper_bound (values[3].first);		// itup points to e (not d!)
	mymap.erase(itlow, itup);						// erases (itlow, itup)
	// print content:
	printmap(mymap, stream);
}

template< class container, typename Key, typename T >
void	map_equal_range(std::pair<Key, T> *values, std::stringstream *stream)
{
	container																mymap;

	mymap[values[0].first] = values[0].second;
	mymap[values[1].first] = values[1].second;
	mymap[values[2].first] = values[2].second;

	std::pair<typename container::iterator, typename container::iterator>	ret;

	ret = mymap.equal_range(values[1].first);
	*stream << "lower bound points to: ";
	*stream << ret.first->first << " => " << ret.first->second << '\n';
	*stream << "upper bound points to: ";
	*stream << ret.second->first << " => " << ret.second->second << '\n';
}

template< class container, typename Key, typename T >
void	map_iterator_operations(std::pair<Key, T> *values, std::stringstream *stream)
{
	container						foo;
	foo.insert(values[0]);
	foo.insert(values[1]);
	foo.insert(values[2]);

	typename container::iterator	it0 = foo.begin();
	typename container::iterator	it1 = foo.begin();
	it1++;
	typename container::iterator	it2 = foo.begin();
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
	*stream << "*it0:" << (*it0).first << '\n';
	*stream << "*it1:" << (*it1).first << '\n';
}

template< class container, typename Key, typename T >
void	map_reverse_iterator_operations(std::pair<Key, T> *values, std::stringstream *stream)
{
	container								foo;
	foo.insert(values[0]);
	foo.insert(values[1]);
	foo.insert(values[2]);

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

	*stream << "it1:" << (*it1).first << ", it2:" << (*it2).first << ", it2b:" << (*it2b).first << ", it3:" << (*it3).first << '\n';
	if (it2 == it2b) *stream << "it2 == it2b\n";
	if (it1 != it2b) *stream << "it1 != it2b\n";
	it2--;
	if (it2 == it3) *stream << "it2++ == it3\n";
	it2++;
	if (it2 == it2b) *stream << "it2 == it2b\n";
	*stream << "*it3:" << (*it3).first << '\n';
	*stream << "*it1:" << (*it1).first << '\n';
}

static void	ft_comp_map(std::stringstream *std_stream, std::stringstream *ft_stream, std::ofstream	*ofs1, std::ofstream *ofs2)
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

template < typename Key, typename T >
void		map_test(std::pair< Key, T > *values, std::ofstream *ofs1, std::ofstream *ofs2)
{
	std::stringstream	std_stream;
	std::stringstream	ft_stream;

	std::cout << "const map : ";
	map_const_test< std::map< Key, T >, Key, T >(&std_stream);
	map_const_test< ft::map< Key, T >, Key, T >(&ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "constructor : ";
	map_constructor_test< std::map< Key, T >, std::map< Key, T, classcomp<Key> >, std::map< Key, T, bool(*)(Key, Key) >, std::map< Key, T, classcomprev<Key> >, Key, T >(values, &std_stream);
	map_constructor_test< ft::map< Key, T >, ft::map< Key, T, classcomp<Key> >, ft::map< Key, T, bool(*)(Key, Key) >, ft::map< Key, T, classcomprev<Key> >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "operator= : ";
	map_operator_equal< std::map< Key, T >, Key, T >(values, &std_stream);
	map_operator_equal< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "begin()/end() : ";
	map_begin< std::map< Key, T >, Key, T >(values, &std_stream);
	map_begin< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "rbegin()/rend() : ";
	map_rbegin< std::map< Key, T >, Key, T >(values, &std_stream);
	map_rbegin< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "empty() : ";
	map_empty< std::map< Key, T >, Key, T >(values, &std_stream);
	map_empty< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "size() : ";
	map_size< std::map< Key, T >, Key, T >(values, &std_stream);
	map_size< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "max_size() : ";
	map_max_size< std::map< Key, T >, Key, T >(&std_stream);
	map_max_size< ft::map< Key, T >, Key, T >(&ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "operator[] : ";
	map_operator_brackets< std::map< Key, T >, Key, T >(values, &std_stream);
	map_operator_brackets< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "insert() : ";
	map_insert< std::map< Key, T >, Key, T >(values, &std_stream);
	map_insert< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "erase() : ";
	map_erase< std::map< Key, T >, Key, T >(values, &std_stream);
	map_erase< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "swap() : ";
	map_swap< std::map< Key, T >, Key, T >(values, &std_stream);
	map_swap< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "clear() : ";
	map_clear< std::map< Key, T >, Key, T >(values, &std_stream);
	map_clear< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "key_comp() : ";
	map_key_comp< std::map< Key, T >, Key, T >(values, &std_stream);
	map_key_comp< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "value_comp() : ";
	map_value_comp< std::map< Key, T >, Key, T >(values, &std_stream);
	map_value_comp< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "find() : ";
	map_find< std::map< Key, T >, Key, T >(values, &std_stream);
	map_find< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "count() : ";
	map_count< std::map< int, T >, Key, T >(values, &std_stream);
	map_count< ft::map< int, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "upper_bound() && lower_bound() : ";
	map_lower_upper_bound< std::map< Key, T >, Key, T >(values, &std_stream);
	map_lower_upper_bound< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "equal_range() : ";
	map_equal_range< std::map< Key, T >, Key, T >(values, &std_stream);
	map_equal_range< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "iterator operation : ";
	map_iterator_operations< std::map< Key, T >, Key, T >(values, &std_stream);
	map_iterator_operations< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "reverse iterator operation : ";
	map_reverse_iterator_operations< std::map< Key, T >, Key, T >(values, &std_stream);
	map_reverse_iterator_operations< ft::map< Key, T >, Key, T >(values, &ft_stream);
	ft_comp_map(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << std::endl;
}
