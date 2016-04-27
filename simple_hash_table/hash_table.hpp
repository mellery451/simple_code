#include <cstdint>
#include <string>
#include <exception>

// node class template
template <typename K, typename V>
class hash_node {
public:
    hash_node(const K& key, const V& val) : key(key), value(val) {}
    // key-value pair
    K key;
    V value;
    // next item in the same bucket...
    std::unique_ptr<hash_node> next;
};

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

// This is the Paul Hsieh "SuperFastHash"
// http://www.azillionmonkeys.com/qed/hash.html
//
// IMPORTANT NOTE: Since there has been a lot of interest for the code below, I
// have decided to additionally provide it under the LGPL 2.1 license. This
// provision applies to the code below only and not to any other code including
// other source archives or listings from this site unless otherwise specified.
//
// The LGPL 2.1 is not necessarily a more liberal license than my derivative
// license, but this additional licensing makes the code available to more
// developers. Note that this does not give you multi-licensing rights. You can
// only use the code under one of the licenses at a time.
//
uint32_t SuperFastHash (const char * data, int len) {
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= ((signed char)data[sizeof (uint16_t)]) << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += (signed char)*data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}

// Default hash function class
template <typename K> struct KeyHash {
    uint32_t operator()(const K& key) const {
        return SuperFastHash(&key, sizeof(K));
    }
};

template <> struct KeyHash <std::string> {
    uint32_t operator()(const std::string& key) const {
        return SuperFastHash(key.data(), key.size());
    }
};

template <typename K, typename V, typename F = KeyHash<K>>
class hash_table {
public:
    hash_table() : table_size(128) {
        table.reset(new std::unique_ptr<hash_node<K,V>> [table_size]);
    }

    ~hash_table() {
    }

    V get(const K& key) {
        hash_node<K,V>* node = get_node(key);
        if(node) {
            return node->value;
        }
        else {
            throw std::runtime_error("table entry not found");
        }
    }

    bool has_key(const K& key) {
        return (get_node(key) != nullptr);
    }

    void insert(const K& key, const V& value) {
        if(exceeds_load_factor()) {
            rehash();
        }
        insert_raw(key, value, table.get(), table_size);
    }

    void remove(const K& key) {
        /*
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            // key not found
            return;
        }
        else {
            if (prev == NULL) {
                // remove first bucket of the list
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
        */
    }
    typedef struct stats {
        size_t table_size;
        float load_factor;
    } stats;

    stats get_stats(void) {
        return {table_size, get_load_factor()};
    }

private:
    void rehash(void) {
        // make growth factor configurable/adaptive ?
        size_t new_table_size = 4 * table_size;
        std::unique_ptr< std::unique_ptr<hash_node<K,V>> []> new_table(new std::unique_ptr<hash_node<K,V>> [new_table_size]);
        for (size_t index = 0; index < table_size; ++index) {
            hash_node<K, V> *entry = table[index].get();
            while (entry != NULL) {
                insert_raw(entry->key, entry->value, new_table.get(), new_table_size);
                entry = entry->next.get();
            }
        }

        table = std::move(new_table);
        table_size = new_table_size;
    }

    void insert_raw(const K &key, const V &value, std::unique_ptr<hash_node<K,V>> this_table[], size_t this_table_size) {
        uint32_t bucket_val = hash_func(key) % this_table_size;
        hash_node<K, V> *prev = NULL;
        hash_node<K, V> *entry = this_table[bucket_val].get();

        while (entry != NULL && entry->key != key) {
            prev = entry;
            entry = entry->next.get();
        }

        if (entry == NULL) {
            entry = new hash_node<K, V>(key, value);
            if (prev == NULL) {
                // insert as first bucket
                this_table[bucket_val].reset(entry);
            } else {
                prev->next.reset(entry);
            }
        } else {
            // just update the value
            entry->value = value;
        }
    }

    hash_node<K,V>* get_node(const K& key) {
        uint32_t bucket_val = hash_func(key) % table_size;
        hash_node<K, V> *entry = table[bucket_val].get();

        while (entry != NULL) {
            if (entry->key == key) {
                return entry;
            }
            entry = entry->next.get();
        }
        return nullptr;
    }

    float get_load_factor(void) {
        uint32_t occupied_count = 0;
        for (size_t index = 0; index < table_size; ++index) {
            if (table[index].get()) {
                occupied_count += 1;
            }
        }
        return static_cast<float>(occupied_count) / static_cast<float>(table_size);
    }

    bool exceeds_load_factor(void) {
        //
        //TODO : should make this load factor configurable?
        //
        return (get_load_factor() > 0.8);
    }

    std::unique_ptr<std::unique_ptr<hash_node<K,V>> []> table;
    size_t table_size;
    F hash_func;
};
