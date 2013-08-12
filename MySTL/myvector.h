#include "../Memory/myalloc.h"
#include "../Memory/myconstruct.h"

template <class T, class Alloc = alloc>
class Vector {
 public:
 typedef T value_type;
 typedef value_type* pointer;
 typedef value_type& reference;
 typedef ptrdiff_t difference_type;
 typedef size_t size_type;
 typedef value_type* iterator;

 protected:
 typedef simple_alloc<value_type, Alloc> data_allocate;
 iterator start;
 iterator finish;
 iterator end_of_storage;

 void insert_aux(iterator position, const T& x);
 void deallocate()
 {
   if (start)
     data_allocate::deallocate(start, end_of_storage - start);
 }

 void fill_initialize(size_type n, const T& value) {
   

 public:
 iterator begin() { return start; }
 iterator end() { return finish; }
 
 size_type size() { return (size_type)(finish - start); }
 size_type capacity() { return (size_type)(end_of_storage - start); }
 bool empty() { return start == finish; }
 reference operator[](size_type n) { return *(start + n); }

 Vector() : start(0), finish(0), end_of_storage(0) {}
 Vector(size_type n, const T& value) { fill_initialize(n, value); }
 Vector(int n, const T& value) { fill_initialize(n, value); }
 Vector(long n, const T& value) { fill_initialize(n, value); }
 explicit Vector(size_type n) { fill_initialize(n, value); }
 
 ~Vector() {
   destroy(start, finish);
   deallocate();
 }

 reference front() { return *begin(); }
 reference back() { return *(end() - 1); }
 void push_back(const T& value)
 {
   if (finish != end_of_storage) {
     construct(finish, value);
     finish++;
   }
   else
     insert_aux(finish, value);
 }

 void pop_back() {
   --finish;
   destroy(finish);
 }

 iterator erase(iterator position) {
   if (position + 1 != end()) {
     for (iterator it = position; it != end()-1; it++)
       *it = *(it+1);
   }
   finish--;
   return position;
 }
 
 void resize(size_type new_size, const T& x)
 {
   if (new_size < size()) {
     erase(begin() + new_size, end());
   }
   else
     insert(end(), new_size - size, x);
 }
 
 void resize(size_type new_size)
 {
   resize(new_size, T());
 }

 void clear() { erase(begin(), end()); }

 protected:
 
