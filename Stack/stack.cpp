#include <cstddef>

template <class TYPE>
class stack {
public:
  bool stack_empty();
  void push(TYPE x);
  TYPE pop();
  
private:
  TYPE data[1000];
  size_t 
};

bool stack::stack_empty()
{
  return true;
}
