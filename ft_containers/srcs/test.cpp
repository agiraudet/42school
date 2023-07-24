/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:23:49 by agiraude          #+#    #+#             */
/*   Updated: 2023/01/31 11:49:52 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include <deque>
#include <map>
#include <vector>
#include <stack>
#include <cstdlib>

#ifdef FT
	#define NS ft
	char g_chk[] = "FT";
#else
	#define NS std
	char g_chk[] = "STD";
#endif

long unsigned int	g_ncount = 10;
bool				g_output = true;

template<typename T>
long unsigned int	relOp(const T& a, const T& b)
{
	if (g_output)
		std::cout << "CMP: ";
	long unsigned int	checksum = 0;
	if (a == b) 
	{
		if (g_output)
			std::cout << "== ";
		checksum |= 1;
	}
	if (a != b) 
	{
		if (g_output)
			std::cout << "!= ";
		checksum |= 2;
	}
	if (a >= b) 
	{
		if (g_output)
			std::cout << ">= ";
		checksum |= 4;
	}
	if (a <= b) 
	{
		if (g_output)
			std::cout << "<= ";
		checksum |= 8;
	}
	if (a > b) 
	{
		if (g_output)
			std::cout << "> ";
		checksum |= 16;
	}
	if (a < b) 
	{
		if (g_output)
			std::cout << "< ";
		checksum |= 32;
	}
	if (g_output)
	{
		std::cout << std::endl;
		std::cout << "-----" << checksum << "-----" << std::endl;
	}
	return checksum;
}

template<typename T, typename Cont>
long unsigned int	printStack(NS::stack<T, Cont> stck)
{
	long unsigned int	checksum = 0;
	if (g_output)
	{
		std::cout << "STACK:" << std::endl;
		std::cout << "empty: " << stck.empty() << std::endl;
		std::cout << "size: " << stck.size() << std::endl;
	}
	checksum += stck.size();
	checksum += stck.empty();
	while (!stck.empty())
	{
		if (g_output)
			std::cout << stck.top() << std::endl;
		checksum += stck.top();
		stck.pop();
	}
	if (g_output)
		std::cout << "------" << checksum << "-----" << std::endl;
	return checksum;
}

long unsigned int	checkStack(void)
{
	std::vector<int> myvector (4,200);    
	NS::stack<int> stckA;               
	NS::stack<int> stckB;        
	NS::stack<int,std::vector<int> > stckC;
	NS::stack<int,std::vector<int> > stckD(myvector);
	long unsigned int	checksum = 0;
	
	for (long unsigned int i = 0; i < g_ncount; i++)
		stckB.push(i);

	checksum += printStack(stckA);
	checksum += printStack(stckB);
	checksum += printStack(stckC);
	checksum += printStack(stckD);
	checksum += relOp(stckA, stckB);
	return checksum; 
}	

template<typename T>
long unsigned int	printVector(NS::vector<T>& vec)
{
	long unsigned int checksum = 0;
	if (g_output)
	{
		std::cout << "VECTOR:" << std::endl;
		std::cout << "empty: " << vec.empty() << std::endl;
		std::cout << "size: " << vec.size() << std::endl;
	}
	checksum += vec.size();
	checksum += vec.empty();
	if (!vec.empty())
	{
		checksum += vec.front();
		checksum += vec.back();
	}
	typename NS::vector<T>::iterator	it = vec.begin(), ite = vec.end();
	typename NS::vector<T>::const_iterator	cit = vec.begin(), cite = vec.end();
	while (cit != cite || it != ite)
	{
		/* *cit = 4; //SHOULD NOT COMPILE */
		checksum += *cit;
		if (g_output)
			std::cout << *cit << std::endl;
		if (*it++ != *cit++)
			checksum = 0;
	}
	typename NS::vector<T>::reverse_iterator	rit = vec.rbegin(), rite = vec.rend();
	typename NS::vector<T>::const_reverse_iterator	rcit = vec.rbegin(), rcite = vec.rend();
	while (rit != rite || rcit != rcite)
	{
		/* *rcit = 4; //SHOULD NOT COMPILE */
		if (*rit++ != *rcit++)
			checksum = 0;
	}
	if (g_output)
		std::cout << "------" << checksum << "-----" << std::endl;
	return checksum;
}

template<typename T>
long unsigned int	accessVec(NS::vector<T>& vec)
{
	long unsigned int checksum = vec.empty();
	if (checksum)
		return checksum;
	for (long unsigned int i = 0; i < vec.size(); i++)
	{
		checksum += vec[i];
		checksum += vec.at(i);
	}
	try
	{
		checksum += vec.at(vec.size());
	}
	catch (std::out_of_range const& e)
	{
		if (g_output)
			std::cout << "Got (expected) : out_of_range" << std::endl;
	}
	return checksum;
}


long unsigned int	checkVector(void)
{
	long unsigned int	checksum = 0;
	NS::vector<int> vecA;
	NS::vector<int> vecB;
	for (long unsigned int i = 0; i < g_ncount; i++)
		vecB.push_back(i);
	NS::vector<int> vecC(vecB.begin(), vecB.end());
	NS::vector<int> vecD(vecC);
	vecD.reserve(1000);
	if (vecD.capacity() < 1000)
		return 0;
	vecD.insert(vecD.begin(), 4, -4);
	vecD.insert(vecD.end(), -8);
	vecD.insert(vecD.end(), -8);
	vecD.pop_back();
	vecD.resize(vecD.size() + 3);
	vecD.swap(vecA);

	checksum += accessVec(vecA);
	checksum += printVector(vecA);
	checksum += printVector(vecB);
	checksum += printVector(vecC);
	checksum += printVector(vecD);
	checksum += relOp(vecA, vecB);
	checksum += relOp(vecB, vecC);
	return checksum;
}

template<typename T1, typename T2>
long unsigned int	printMap(NS::map<T1, T2>& mp)
{
	long unsigned int checksum = 0;
	if (g_output)
	{
		std::cout << "MAP:" << std::endl;
		std::cout << "empty: " << mp.empty() << std::endl;
		std::cout << "size: " << mp.size() << std::endl;
	}
	checksum += mp.size();
	checksum += mp.empty();
	typename NS::map<T1, T2>::iterator	it = mp.begin(), ite = mp.end();
	typename NS::map<T1, T2>::const_iterator	cit = mp.begin(), cite = mp.end();
	while (cit != cite || it != ite)
	{
		/* cit->second = 4; //SHOULD NOT COMPILE */
		checksum += cit->second;
		if (g_output)
			std::cout << cit->second << std::endl;
		if (it->second != cit->second)
			checksum = 0;
		it++;
		cit++;
	}
	typename NS::map<T1, T2>::reverse_iterator	rit = mp.rbegin(), rite = mp.rend();
	typename NS::map<T1, T2>::const_reverse_iterator	rcit = mp.rbegin(), rcite = mp.rend();
	while (rit != rite || rcit != rcite)
	{
		/* rcit->second = 4; //SHOULD NOT COMPILE */
		if (rit->second != rcit->second)
			checksum = 0;
		rit++;
		rcit++;
	}
	if (g_output)
		std::cout << "------" << checksum << "-----" << std::endl;
	return checksum;
}

long unsigned int checkMap(void)
{
	long unsigned int	checksum = 0;
	NS::map<int, int>	mpA;
	std::vector<NS::pair<int, int> >	vec;
	for (long unsigned int i = 0; i < g_ncount; i++)
		vec.push_back(NS::make_pair(i, i));
	NS::map<int, int>	mpB(vec.begin(), vec.end());
	NS::map<int, int>	mpC(mpB);

	for (long unsigned int i = 0; i < g_ncount; i += 2)
	{
		if (mpB[i] == mpC[i])
			checksum += mpB.at(i);
	}
	try
	{
		checksum += mpB.at(-1234);
	}
	catch (std::out_of_range const& e)
	{
		if (g_output)
			std::cout << "Got (expected) : out_of_range" << std::endl;
	}
	mpC.clear();
	if (!mpC.empty() || mpC.size() > 0)
		checksum = 0;
	mpB.erase(1);
	checksum += mpB.count(1);
	checksum += mpB.count(2);
	mpB.swap(mpC);

	checksum += printMap(mpA);
	checksum += printMap(mpB);
	checksum += printMap(mpC);

	mpA = mpC;
	if (mpA.lower_bound(4)->second != mpC.lower_bound(4)->second)
		checksum = 0;
	if (mpA.upper_bound(4)->second != mpC.upper_bound(4)->second)
		checksum = 0;

	checksum += relOp(mpA, mpC);
	checksum += relOp(mpA, mpB);

	mpC.erase(mpC.begin(), mpC.end());
	checksum += printMap(mpC);
	return checksum;
}



int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " ncount output(0/1)" << std::endl;
		return 0;
	}
	g_ncount = atoi(argv[1]);
	if (g_ncount < 1)
	{
		std::cout << "Wrong ncount" << std::endl;
		return 0;
	}
	if (argv[2])
	{
		if (argv[2][0] == '0')
			g_output = false;
		else if (argv[2][0] == '1')
			g_output = true;
		else
		{
			std::cout << "Please use 0 or 1 to specifie output mode" << std::endl;
			return 0;
		}
	}
	if (!g_output)
		std::cout << "Compiled with namespace: " << g_chk << std::endl;

	long unsigned int check = checkStack();
	std::cout << "STACK CHECKSUM: " << check << std::endl;
	check = checkVector();
	std::cout << "VECTOR CHECKSUM: " << check << std::endl;
	check = checkMap();
	std::cout << "MAP CHECKSUM: " << check << std::endl;
	return 0;
}
