/** The const_iterator class */




class const_iterator {
	/*<exercise chapter="9" type="programming-project" number="6">*/
	public:

	/** Convert from an iterator to a const_iterator */
	const_iterator(typename hash_map<Key_Type, Value_Type>::iterator& other)
		: the_parent(other.the_parent),
		the_index(other.the_index),
		the_pos(other.the_pos) {}

	/** De-reference an const_iterator */
	const Entry_Type& operator * ()const {
		if (*this == the_parent->end()) {
			throw std::invalid_argument("Attemt to de-reference end()");
		}
		return  *the_pos;
	}

	/** De-reference an const_iterator */
	const Entry_Type* operator->()const {
		if (*this == the_parent->end()) {
			throw std::invalid_argument("Attemt to de-reference end()");
		}
		return  &(*the_pos);
	}

	/* The rest of the definition of a const_iterator is
	the same as an iterator except for the class name */
	/** Prefix increment operator */
	const_iterator& operator++() {
		++the_pos;
		advance();
		return  *this;
	}

	/** Postfix increment operator */
	const_iterator operator++(int) {
		const_iterator temp(*this);
		++(*this);
		return temp;
	}

	/** Equality operator */
	bool operator == (const const_iterator& other)const {
		return the_index == other.the_index
			&& the_pos == other.the_pos;
	}

	/** Inequality operator */
	bool operator != (const const_iterator& other)const {
		return !operator == (other);
	}

private:

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
	friend class hash_map < Key_Type, Value_Type >;

	// Insert constructor and data fields here
	/** Construct an const_iterator starting at a given position
	in a given bucket */
	const_iterator(const hash_map < Key_Type, Value_Type >* const parent,
		size_t index,
		typename std::list < Entry_Type > ::const_iterator pos) :
		the_parent(parent),
		the_index(index),
		the_pos(pos) {}

	/** A pointer to the map that this iterator is in */
	const hash_map < Key_Type, Value_Type >* const the_parent;

	/** The index of the bucket */
	size_t the_index;

	/** The const_iterator within the bucket */
	typename std::list < Entry_Type > ::const_iterator the_pos;

	/*</exercise>*/
}; // End const_iterator
