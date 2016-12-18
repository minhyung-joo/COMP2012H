#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class HashTable {
private:
	vector<list<T> > table;
	int base;
	int m;
  int size;
public:
	HashTable(int min, int b) {
		table.resize(min);
		base = b;
		m = min;
		size = 0;
	}

  bool empty() {
    return size == 0;
  }

	int hash(string key) {
		int hashValue = 0;
		int a;
		int product;
		char c;

		for (int i = 0; i < key.length(); i++) {
  			c = key.at(i);
  			product = 1;
  
			if (c > '9') {
				a = c - 'A' + 11;
			}
			else {
				a = c - '0';
			}
  
			for (int j = 0; j < i; j++) {
				product = (product * base) % m;
			}
			hashValue = (hashValue + (a * product) % m) % m;
		}
  
		return hashValue;
	}
 
	void insert(T newItem) {
		int h = hash(newItem.getKey());

		table[h].push_front(newItem);
		table[h].sort();
   
		size++;
	}

  void insert(T newItem, string& key) {
    int h = hash(key);
    
    table[h].push_front(newItem);
		table[h].sort();
   
    size++;
  }
 
  T query(string& key) {
    int h = hash(key);
    
    if (table[h].empty()) {
	T dummy;
      return dummy;
    }
    else {
      typename list<T>::iterator scanner;

    	for (scanner = table[h].begin(); scanner != table[h].end(); scanner++) {
    		if (key == (*scanner).getKey()) {
          T foundItem = *scanner;
    			return foundItem;
    		}
    	}
    }
  }

  list<T> queryAll(string& key) {
    int h = hash(key);
    list<T> matchedItems;
    
    if (!table[h].empty()) {
      typename list<T>::iterator scanner;

    	for (scanner = table[h].begin(); scanner != table[h].end(); ++scanner) {
   		if (*(*scanner) == key) {
			T item = *scanner;
			matchedItems.push_back(item);
    		}
    	}
    }
    
    return matchedItems;
  }

	T remove(string& key) {
		int h = hash(key);

		if (table[h].empty()) {
			T dummy;
			return dummy;
		}
		else {
			typename list<T>::iterator scanner;

			for (scanner = table[h].begin(); scanner != table[h].end(); scanner++) {
				if (key == (*scanner).getKey()) {
					T removedItem = *scanner;
					table[h].erase(scanner);
          size--;
					return removedItem;
				}
      }
		}
	}

  T remove(T item, string& key) {
    int h = hash(key);

		if (table[h].empty()) {
			T dummy;
			return dummy;
		}
		else {
			typename list<T>::iterator scanner;

			for (scanner = table[h].begin(); scanner != table[h].end(); scanner++) {
				if (*item == *(*scanner)) {
					T removedItem = *scanner;
					table[h].erase(scanner);
          size--;
					return removedItem;
				}
      }
		}
  }

	list<T> getList() {
		list<T> allItems;

		for (int i = 0; i < m; i++) {
			allItems.insert(allItems.end(), table[i].begin(), table[i].end());
		}

		allItems.sort();

		return allItems;
	}

	void clear() {
		for (int i = 0; i < m; i++) {
			table[i].clear();
		}
		table.clear();
	}
};

#endif
