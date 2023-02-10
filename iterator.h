#ifndef ITERATOR_H
#define ITERATOR_H
/** The iterator class */
//#include "hash_table_chain.h"
//#include <stdexcept>
//#include <string>
//#include "Hash_Table_Chain.h"


class iterator {
	/*<exercise chapter="9" type="programming-project" number="6">*/
public:
	
	/** De-reference an const_iterator */
	hash_map<Key_Type, Value_Type>::Entry_Type& operator*() const {
		if (*this == the_parent->end()) {
			throw std::invalid_argument("Attemt to de-reference end()");
		}
		return  *the_pos;
	}

	/** De-reference an const_iterator */
	Entry_Type* operator->() const {
		if (*this == the_parent->end()) {
			throw std::invalid_argument("Attemt to de-reference end()");
		}
		return  &(*the_pos);
	}

	/* The rest of the definition of a const_iterator is
	the same as an iterator except for the class name */
	/** Prefix increment operator */
	iterator& operator++() {
		++the_pos;
		advance();
		return  *this;
	}

	/** Postfix increment operator */
	iterator operator++(int) {
		iterator it = *this;
		++the_pos;
		advance();
		return it;
		
		/*iterator temp(*this);
		++(*this);
		return temp;*/
	}

	/** Equality operator */
	bool operator == (const iterator& other)const {
		return (the_parent == other.the_parent && the_index == other.the_index && the_pos == other.the_pos);
	}

	/** Inequality operator */
	bool operator != (const iterator& other)const {
		return (the_index != other.the_index || the_pos != other.the_pos);
	}

private:
	template<typename,typename> friend class KW::hash_map;

	/** Advance the iterator to the next position */
	void advance() {
        if (the_pos != the_parent->the_buckets[the_index].end()) {
            return;
        } else {
            while (the_index < (the_parent->the_buckets.size() - 1)) {
                the_index++;
                the_pos = the_parent->the_buckets[the_index].begin();
                if (the_pos != the_parent->the_buckets[the_index].end())
                    return;
            }
            the_pos = the_parent->the_buckets[the_index].end();
            return;
        }
	}

	// Allow the map to access the private constructor and data fields

	// Insert constructor and data fields here
	/** Construct an const_iterator starting at a given position
	in a given bucket */;
	iterator(hash_map<Key_Type, Value_Type>* parent, size_t index, typename std::list < Entry_Type > ::iterator pos) :
		the_parent(parent),
		the_index(index),
		the_pos(pos) 
	{}

	/** A pointer to the map that this iterator is in */
	hash_map<Key_Type, Value_Type>* the_parent;

	/** The index of the bucket */
	size_t the_index;

	/** The const_iterator within the bucket */
	typename std::list <Entry_Type> ::iterator the_pos;

	//friend class hash_map;
	friend class const_iterator;
}; // End iterator;;
#endif 