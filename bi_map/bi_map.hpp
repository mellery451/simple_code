#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <map>   /// <<< hmmm....is there a hint here? not sure why we are including this...
#include <string>
#include <utility>
#include <type_traits>

/* A bi-directional map.
   This functions similarly to std::map except that elements
   can be looked up by either T or U.
*/
template <class T, class U>
class bi_map
{
public:
    using pair = std::pair<T, U>;
    using iterator = typename std::list<pair>::iterator;
    using const_iterator = typename std::list<pair>::const_iterator;

    const_iterator end() const { return list_.end(); }
    const_iterator begin() const { return list_.begin(); }

    // returns the number of elements
    std::size_t size() const { return list_.size(); }

     // insert a copy of the given pair
    void insert(pair const& p);

    const_iterator find(T const& t) {
        return std::find_if(list_.begin(), list_.end(),
            [&] (pair const& p) { return p.first == t; } );
    }

    const_iterator find(U const& u) {
        return std::find_if(list_.begin(), list_.end(),
            [&] (pair const& p) { return p.second == u; } );
    }

private:
    static_assert(!std::is_same<T, U>::value,
                  "T and U can not be the same type");

    std::list<pair> list_;
};

// insert the pair
// if either key already exists, undefined behavior
template <class T, class U>
void bi_map<T, U>::insert(pair const& p)
{
    // Implement this function.
    // Assume the neither key is already present.
    if (find(p.first) == end() && find(p.second) == end()) {
        // it is not obvious whether we should insert front, back,
        // or somewhere in the middle
        list_.push_back(p);
    }
    // else, one or both of the pair items
    // is already in the list. Possible actions
    // in the case of one or both pair keys already
    // existing:
    //   (1) throw an exception
    //   (2) silently do nothing
    //   (3) remove any existing entries matching T and or U
    //       and then insert this pair
    // for now, I do option (2), which is the simplest to implement ;)
}

template <class T, class U>
std::ostream& operator<<(std::ostream& os, bi_map<T, U> const& m) {
    // NOTE: this might look like json but is NOT. In order to
    // write valid json, we would need to type test T and U because
    // there are different rules for writing numbers, strings, bools in json
    // for now, just quote all the things!
    os << "[";
    bool first_pass = true;
    for (auto p : m) {
        if (first_pass) {
            first_pass = false;
        }
        else {
            os << " ,";
        }
        os << "\n   ";
        os << "{ 'T': '" << p.first << "', 'U': '" << p.second << "'}";
    }
    if (!first_pass) {
        os << "\n";
    }
    os << "]";
    return os;
}


