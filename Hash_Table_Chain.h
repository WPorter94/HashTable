#ifndef HASH_TABLE_CHAIN_H_
#define HASH_TABLE_CHAIN_H_

/** Implementaion of the hash_map class using chaining */

#include <stdexcept>
#include <cstddef>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <ostream>
#include "hash.h"


namespace KW
{
	/** Definition of the hash_map class. This definition is similar
		to the unordered_map that has been proposed for the next
		version of the C++ standard.
		@param Key_Type The type of the keys
		@param Value_Type The type of the values
	*/
	template<typename Key_Type, typename Value_Type> class hash_map {

	public:

		// Typedefs
		typedef std::pair<const Key_Type, Value_Type> Entry_Type;

		// Forward declaration of iterator
		class iterator;
		class const_iterator;

		/** Construct an empty hash_map. */
		/*</exercise>*/
		hash_map() :
			hash_fcn(hash<Key_Type>()), num_keys(0),
			the_buckets(INITIAL_CAPACITY),
			LOAD_THRESHOLD(0.75) {}


		/** Inserts an item into the map.
			post: The key is associated with the value in the map.
			@param entry The key, value pair to be inserted
			@return an iterator to the inserted item and true
					if the entry was inserted, an iterator to the existing
					item and false if the item is already present
		*/
		std::pair<iterator, bool> insert(const Entry_Type& entry) {
			double load_factor = double(num_keys) / the_buckets.size();

			if (load_factor > LOAD_THRESHOLD) {
				rehash(); // Double the size of the table.
			}
			size_t index = hash_fcn(entry.first) % the_buckets.size();
			// Search for the key.
			typename std::list<Entry_Type>::iterator pos = the_buckets[index].begin();

			while (pos != the_buckets[index].end() && pos->first != entry.first)
				++pos;
			if (pos == the_buckets[index].end())
			{ 
				// Not in table
				the_buckets[index].push_back(Entry_Type(entry));
				num_keys++;
				return std::make_pair(iterator(this, index, --(the_buckets[index].end())), true);
			}
			else
			{ // Already there
				return std::make_pair(iterator(this, index, pos), false);
			}
		}

		/** Lookup an item in the map
		@param key The key of the item being sought
		@return An iterator that references a
		pair<const Key_Type, Value_Type> that
		contains the key and the associated value sought,
		or end() if the key is not in the map.
		*/
		iterator find(const Key_Type& key) {
			/*<exercise>*/
			size_t index = hash_fcn(key) % the_buckets.size();
			typename std::list<Entry_Type>::iterator it = the_buckets.at(index).begin(); // making an iterator of type linked list and assign to it the first index of the vector

			while (it != the_buckets.at(index).end() && key != it->first()) //if its not the end && the key isn't equal the first key of the map
			{
				it++; // move to the next index
			}
			if (key == it->first)  // found a match
			{


				return iterator(this, index, it); // return ( this map , with this index of the vector , with this index inside the linked list)
			}
			else
			{
				return this->end(); // return the end iterator
			}
		}


		/** Lookup an item in the map
		@param key The key of the item being sought
		@return An iterator that references a
		pair<const Key_Type, Value_Type> that
		contains the key and the associated value sought,
		or end() if the key is not in the map.
		*/
		const_iterator find(const Key_Type& key) const {
			size_t index = hash_fcn(key) % the_buckets.size();
			typename std::list<Entry_Type>::iterator it = the_buckets.at(index).begin(); // making an iterator of type linked list and assign to it the first index of the vector

			while (it != the_buckets.at(index).end() && key != it->first()) //if its not the end && the key isn't equal the first key of the map
			{
				it++; // move to the next index
			}
			if (key == it->first)  // found a match
			{


				return const_iterator(this, index, it); // return ( this map , with this index of the vector , with this index inside the linked list)
			}
			else
			{
				return this->end(); // return the end iterator
			}
		}



		/** Access a value in the map, using the key as an index
		@param key The key of the item being sought
		@return A reference to the associated value. If the
		key was not in the map, a defalut value is inserted and
		a reference to this value returned.
		*/
		Value_Type& operator[](const Key_Type& key) {

			std::pair<iterator, bool> ret = insert(Entry_Type(key, Value_Type()));
			
			return ret.first->second;

			/*std::pair<iterator, bool> ret = the_buckets.insert(Entry_Type(key, Value_Type()));
			Entry_Type& entry(const_cast<Entry_Type&>(*(ret.first)));
			return entry.second;*/

		}

		/** Remove an item from the map based on a key
		@param key The key of the item to be removed
		@return true if the item removed, false if the item
		was not already in the map
		*/
		bool erase(const Key_Type& key) {

		/*<exercise chapter="9" section="4" type="programming" number="2">*/
		 // Find the position in the table
			size_t index = hash_fcn(key) % the_buckets.size(); // finding the position of the key
			typename std::list<Entry_Type>::iterator it = the_buckets.at(index).begin(); // making an iterator of type linked list and assign to it the first index of the vector

			while (it != the_buckets.at(index).end()) //if its not the end && the key isn't equal the first key of the map
			{


				if (key == it->first)  // found a match
				{
					the_buckets[index].erase(it);
					num_keys--;
					//                delete iterator (this,index,it);
					return true;
				}
			}

			return false;
		}

		/** Return an iterator to the beginning of the map */
		iterator begin() {
			iterator return_value(this, 0, the_buckets[0].begin());
			return_value.advance();
			return return_value;
		}

		/** Return a const_iterator to the beginning of the map */
		const_iterator begin() const {
			const_iterator return_value(this, 0, the_buckets[0].begin());
			return_value.advance();
			return return_value;
		}

		/** Return an iterator to the end of the map */
		iterator end() {
			return iterator(this, the_buckets.size() - 1, the_buckets.at(the_buckets.size() - 1).end());
			
		}

		/** Return a const_iterator to the end of the map */
		const_iterator end() const {
			//return const_iterator(this, the_buckets.size() -1, the_buckets.at(size() -1).end());
            const_iterator it (this, the_buckets.size()-1, the_buckets.at( the_buckets.size()-1 ).end());
            return it;

		}

		/*<exercise chapter="9" section="4" type="programming" number="5">*/
		/** Return the size of the map */
		size_t size() const {

			return num_keys;
		}

		/** Determine if the map is empty */
		bool empty() const {
			return the_buckets.empty();
		}

		/*</exercise chapter="9" section="4" type="programming" number="3">*/
		/** Return a string representation of the hash map
		@return A string that contains each pair enclosed in "[" and "]"
		with the key and value separated by a comma. The whole string
		is enclosed in "{" and "}"
		*/
		std::string to_string() const {
			std::ostringstream result;
			result << "{";
			const_iterator itr = this->begin();


			if ( itr != this->end() ) {

				result << "[" << itr->first << "," << itr->second << "]";
//				itr++;

				while ( ++itr != this->end() ) {


					result << ",[" << itr->first << "," << itr->second << "]";



				}

			}
			result << "}";
			return result.str();

		}

		// See iterator class
		/*</exercise>*/

		#include "iterator.h"
		#include "const_iterator.h"

// See const_iterator class
/*</exercise>*/
	private:

		/** Expand the size of the hash table */
		void rehash() {
			/*<exercise chapter="9" section="4" type="programming" number="2">*/
			// Create a new table that is twice the size
			std::vector<std::list<Entry_Type>> new_buckets(the_buckets.size() * 2);
			// Swap tables
			the_buckets.swap(new_buckets);
			// Reinsert items from old table to new one
			for (int i = 0; i < new_buckets.size(); i++) {
				typename std::list<Entry_Type>::iterator pos = new_buckets[i].begin();
				while (pos != new_buckets[i].end()) {
					size_t index = hash_fcn(pos->first) % the_buckets.size();
					the_buckets[index].push_back(*pos);
					++pos;
				}
			}
			/*</exercise>*/
		}


		// Insert data fields here
	  /** The hash function object */
		hash<Key_Type> hash_fcn;

		/** The number of items currently in the map */
		size_t num_keys;

		/** Vector of lists containing the buckets */
		std::vector<std::list<Entry_Type>> the_buckets;

		/** The initial capacity */
		static const size_t INITIAL_CAPACITY = 20;

		/** The maximum load factor */
		const double LOAD_THRESHOLD;

	}; // End hash_map
}  // End namespace KW

#endif
