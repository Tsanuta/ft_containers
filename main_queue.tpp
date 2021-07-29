/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_queue.tpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:30:48 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:17:04 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

template< class container, typename T >
static void	que_empty_queue(std::stringstream *stream)
{
	container const	constQueue;
	container		first;						// empty queue

	*stream << "queue first ok\n";
	*stream << "first size : " << first.size() << std::endl;
}


template< class container, class container2, typename T >
static void	que_constructor_test(T* values, std::stringstream *stream)
{
	std::deque<T>	mydeque(3, values[5]);		// deque with 3 elements
	std::list<T>	mylist(2, values[6]);		// vector with 2 elements

	container		first;						// empty queue
	container		second(mydeque);			// queue initialized to copy of deque

	container2		third;						// empty queue using vector
	container2		fourth(mylist);

	*stream << "size of first: " << first.size() << '\n';
	*stream << "size of second: " << second.size() << '\n';
	*stream << "size of third: " << third.size() << '\n';
	*stream << "size of fourth: " << fourth.size() << '\n';
}

template< class container, typename T >
static void	que_empty(std::stringstream *stream)
{
	container	myqueue;
	int			sum(0);

	for (int i = 1;i <= 10; i++) myqueue.push(i);

	while (!myqueue.empty())
	{
		sum += myqueue.front();
		myqueue.pop();
	}
	*stream << "total: " << sum << '\n';
}

template< class container, typename T >
static void	que_size(T* values, std::stringstream *stream)
{
	container	myints;

	*stream << "0. size: " << myints.size() << '\n';
	for (int i = 0; i < 5; i++) myints.push(values[i]);
	*stream << "1. size: " << myints.size() << '\n';
	myints.pop();
	*stream << "2. size: " << myints.size() << '\n';
}

template< class container, typename T >
static void	que_front(T* values, std::stringstream *stream)
{
	container	myqueue;

	myqueue.push(values[0]);
	*stream << "myqueue.back() is now " << myqueue.back() << '\n';
	myqueue.push(values[1]);
	*stream << "myqueue.front() is now " << myqueue.front() << '\n';
	myqueue.push(values[2]);
	*stream << "myqueue.front() is now " << myqueue.front() << '\n';
	myqueue.pop();
	*stream << "myqueue.front() is now " << myqueue.front() << '\n';
}

template< class container, typename T >
static void	que_back(T* values, std::stringstream *stream)
{
	container	myqueue;

	myqueue.push(values[0]);
	*stream << "myqueue.back() is now " << myqueue.back() << '\n';
	myqueue.push(values[1]);
	*stream << "myqueue.back() is now " << myqueue.back() << '\n';
	myqueue.push(values[2]);
	*stream << "myqueue.back() is now " << myqueue.back() << '\n';
	myqueue.pop();
	*stream << "myqueue.back() is now " << myqueue.back() << '\n';
}

template< class container, typename T >
static void	que_push_pop(T* values, std::stringstream *stream)
{
	container	myqueue;

	for (int i = 0; i < 5; ++i) myqueue.push(values[i]);
	*stream << "Popping out elements...";
	while (!myqueue.empty())
	{
		*stream << ' ' << myqueue.front();
		myqueue.pop();
	}
	*stream << '\n';
}

template< class container, typename T >
static void	que_relational_operators(T* values, std::stringstream *stream)
{
	container a;
	a.push(values[0]);
	a.push(values[1]);
	a.push(values[2]);
	container b;
	b.push(values[0]);
	b.push(values[1]);
	b.push(values[2]);
	container c;
	c.push(values[2]);
	c.push(values[1]);
	c.push(values[0]);

	if (a==b) *stream << "a and b are equal\n";
	if (b!=c) *stream << "b and c are not equal\n";
	if (b<c) *stream << "b is less than c\n";
	if (c>b) *stream << "c is greater than b\n";
	if (a<=b) *stream << "a is less than or equal to b\n";
	if (a>=b) *stream << "a is greater than or equal to b\n";
}

static void	ft_comp_que(std::stringstream *std_stream, std::stringstream *ft_stream, std::ofstream	*ofs1, std::ofstream *ofs2)
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
void		queue_test(T *values, std::ofstream	*ofs1, std::ofstream *ofs2)
{
	std::stringstream	std_stream;
	std::stringstream	ft_stream;

	std::cout << "const queue : ";
	que_empty_queue< std::queue< T >, T >(&std_stream);
	que_empty_queue< ft::queue< T >, T >(&ft_stream);
	ft_comp_que(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "constructor : ";
	que_constructor_test< std::queue< T >, std::queue<T, std::list<T> >, T >(values, &std_stream);
	que_constructor_test< ft::queue< T >, ft::queue<T, std::list<T> >, T >(values, &ft_stream);
	ft_comp_que(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "empty() : ";
	que_empty< std::queue< int >, int >(&std_stream);
	que_empty< ft::queue< int >, int >(&ft_stream);
	ft_comp_que(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "size() : ";
	que_size< std::queue< T >, T >(values, &std_stream);
	que_size< ft::queue< T >, T >(values, &ft_stream);
	ft_comp_que(&std_stream, &ft_stream, ofs1, ofs2);
	// std::cout << "front() : ";
	// que_front< std::queue< T >, T >(values, &std_stream);
	// que_front< ft::queue< T >, T >(values, &ft_stream);
	// ft_comp_que(&std_stream, &ft_stream, ofs1, ofs2);
	// std::cout << "back() : ";
	// que_back< std::queue< T >, T >(values, &std_stream);
	// que_back< ft::queue< T >, T >(values, &ft_stream);
	// ft_comp_que(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "push() && pop() : ";
	que_push_pop< std::queue< T >, T >(values, &std_stream);
	que_push_pop< ft::queue< T >, T >(values, &ft_stream);
	ft_comp_que(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << "relational operators : ";
	que_relational_operators< std::queue< T >, T >(values, &std_stream);
	que_relational_operators< ft::queue< T >, T >(values, &ft_stream);
	ft_comp_que(&std_stream, &ft_stream, ofs1, ofs2);
	std::cout << std::endl;
}
