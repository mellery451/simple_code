// g++ -g -Wall -Wextra -Werror -std=c++17 -o nv_ll nv_ll.cpp
#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

template <typename T> struct ListNode {
  T val;
  ListNode<T> *next;
  ListNode(T x) : val(x), next(nullptr) {}
  ListNode(T x, ListNode<T> *next) : val(x), next(next) {}
};

template <typename T> class List {
private:
  ListNode<T> *head;
  size_t size;

public:
  List() : head(nullptr), size(0) {}

  List(const vector<T> &l) : List() {
    ListNode<T> **ppcur = &head;
    for (auto const &entry : l) {
      *ppcur = new ListNode<T>{entry};
      ppcur = &((*ppcur)->next);
    }
    size = l.size();
  }

  ~List() {
    ListNode<T> *pcur{head};
    ListNode<T> *pnext{nullptr};
    while (pcur) {
      pnext = pcur->next;
      delete pcur;
      pcur = pnext;
    }
  }

  bool push_front(const T &val) {
    if (size == std::numeric_limits<size_t>::max())
    {
      std::cerr << "List full, cannot push_front\n";
      return false;
    }
    head = new ListNode<T>{val, head};
    if (!head) {
      std::cerr << "alloc failed, cannot push_front\n";
      return false;
    }
    size++;
    return true;
  }

  ListNode<T> *get_last() {
    ListNode<T> *pend = head;
    while (pend && pend->next) {
      pend = pend->next;
    }
    return pend;
  }

  bool push_back(const T &val) {
    if (size == std::numeric_limits<size_t>::max())
    {
      std::cerr << "List full, cannot push_front\n";
      return false;
    }
    ListNode<T> *newNode = new ListNode<T>{val};
    if (!newNode) {
      std::cerr << "alloc failed, cannot push_back\n";
      return false;
    }

    ListNode<T> *plast = get_last();
    if (plast) {
      plast->next = new ListNode<T>{val};
    } else {
      head = new ListNode<T>{val};
    }
    size++;
    return true;
  }

  bool remove(size_t pos) {
    if (pos >= size) {
      return false;
    }
    size_t loc{0U};
    ListNode<T> *pprev{nullptr};
    ListNode<T> *pcur{head};
    while (pcur) {
      if (loc == pos) {
        if (pprev) {
          pprev->next = pcur->next;
        } else {
          head = pcur->next;
        }
        delete pcur;
        size--;
        break;
      }
      loc++;
      pprev = pcur;
      pcur = pcur->next;
    }
    return true;
  }

  void reverse() {
    ListNode<T> *pprev{nullptr};
    ListNode<T> *pcur{head};
    while (pcur) {
      ListNode<T> *pnext{pcur->next};
      pcur->next = pprev;
      pprev = pcur;
      pcur = pnext;
    }
    head = pprev;
  }

  void print() const {
    if (size == 0) {
      std::cout << "Empty list\n";
      return;
    }
    size_t loc{0U};
    ListNode<T> *pcur{head};
    while (pcur) {
      std::cout << "[" << loc << "]: " << pcur->val << "\n";
    }
  }

  vector<T> to_vector() const {
    vector<T> result;
    ListNode<T> *current = head;
    while (current != nullptr) {
      result.push_back(current->val);
      current = current->next;
    }
    return result;
  }
};

/*
 * Complete the 'run_test' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. STRING operation - the test operation to perform
 *  2. INTEGER_ARRAY context - the input data for testing
 *
 * Operations supported:
 * - "create_from_vector": Create list from context vector
 * - "push_front_sequence": Push context elements to front sequentially
 * - "push_back_sequence": Push context elements to back sequentially
 * - "remove_position": context[0]=list size, context[1]=position to remove
 * - "reverse_list": Create list from context and reverse it
 * - "mixed_operations": Complex test with multiple operations
 */

vector<int> run_test(string operation, vector<int> context) {
  List<int> list;
  vector<int> result;

  if (operation == "create_from_vector") {
    List<int> testList(context);
    return testList.to_vector();
  } else if (operation == "push_front_sequence") {
    for (int val : context) {
      list.push_front(val);
    }
    return list.to_vector();
  } else if (operation == "push_back_sequence") {
    for (int val : context) {
      list.push_back(val);
    }
    return list.to_vector();
  } else if (operation == "remove_position") {
    if (context.size() < 3)
      return result;

    int size = context[0];
    (void)size; // ignore
    int pos = context[1];
    vector<int> data(context.begin() + 2, context.end());

    List<int> testList(data);
    testList.remove(pos);

    return testList.to_vector();
  } else if (operation == "reverse_list") {
    List<int> testList(context);
    testList.reverse();

    return testList.to_vector();
  } else if (operation == "mixed_operations") {
    if (context.empty())
      return result;

    int n = min((int)context[0], (int)context.size() - 1);
    vector<int> initial(context.begin() + 1, context.begin() + 1 + n);

    List<int> testList(initial);
    testList.push_front(99);
    testList.push_back(88);
    if (initial.size() > 0) {
      testList.remove(initial.size() / 2);
    }
    testList.reverse();

    return testList.to_vector();
  } else if (operation == "push_front_and_back") {
    size_t mid = context.size() / 2U;

    for (size_t i = 0U; i < mid; i++) {
      list.push_back(context[i]);
    }
    for (size_t i = mid; i < context.size(); i++) {
      list.push_front(context[i]);
    }

    return list.to_vector();
  } else if (operation == "multiple_removes") {
    if (context.size() < 3)
      return result;

    int size = context[0];
    int numRemoves = context[1];
    vector<int> data(context.begin() + 2, context.begin() + 2 + size);

    List<int> testList(data);

    for (int i = 0;
         i < numRemoves && (2 + size + i) < static_cast<int>(context.size());
         i++) {
      testList.remove(context[2 + size + i]);
    }

    return testList.to_vector();
  }

  return result;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string operation;
  getline(cin, operation);

  string context_count_temp;
  getline(cin, context_count_temp);

  int context_count = stoi(ltrim(rtrim(context_count_temp)));

  vector<int> context(context_count);

  for (int i = 0; i < context_count; i++) {
    string context_item_temp;
    getline(cin, context_item_temp);

    int context_item = stoi(ltrim(rtrim(context_item_temp)));

    context[i] = context_item;
  }

  vector<int> result = run_test(operation, context);

  for (size_t i = 0; i < result.size(); i++) {
    fout << result[i];

    if (i != result.size() - 1) {
      fout << "\n";
    }
  }

  fout << "\n";

  fout.close();

  return 0;
}

string ltrim(const string &str) {
  string s(str);

  s.erase(s.begin(), find_if(s.begin(), s.end(), [](const unsigned char ch) {
            return !std::isspace(ch);
          }));

  return s;
}

string rtrim(const string &str) {
  string s(str);

  s.erase(find_if(s.rbegin(), s.rend(),
                  [](const unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());

  return s;
}
