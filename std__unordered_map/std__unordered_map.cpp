/* Make a data structure that where you can add and get elements based on timestamp.

hash_map use a hash table where the key is hashed to a slot in the table and the value is stored in a list tied to that key.

An unordered_map should give slightly better performance for accessing known elements of the collection, but a map will have
additional useful characteristics (e.g. it is stored in sorted order, which allows traversal from start to finish). 
unordered_map will be faster on insert and delete than a map.

*/
#include "stdafx.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <thread>
#include <windows.h> 
#include <stdio.h> 

using namespace std::chrono;

#define SAMPLING_DELTA (40)

std::uint32_t get_epoch_time()
{
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	return ms.count();
}

void insert_to_map(std::unordered_map<std::uint32_t, std::string> &io_map)
{
	for (int i = 0; i < 10; ++i)
	{
		std::uint32_t epoch_time = get_epoch_time();
		io_map[epoch_time] = "time " + std::to_string(SAMPLING_DELTA) + "*" + std::to_string(i);
		Sleep(SAMPLING_DELTA);
	}
}

int main()
{
	std::unordered_map<std::uint32_t, std::string> mymap;

	insert_to_map(mymap);

	std::cout << "mymap contains:";
	for (auto it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << " " << it->first << ":" << it->second;
	std::cout << std::endl;

	std::cout << "mymap's buckets contain:\n";
	for (unsigned i = 0; i < mymap.bucket_count(); ++i) {
		std::cout << "bucket #" << i << " contains:";
		for (auto local_it = mymap.begin(i); local_it != mymap.end(i); ++local_it)
			std::cout << " " << local_it->first << ":" << local_it->second;
		std::cout << std::endl;
	}

	return 0;
}