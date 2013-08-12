
#if 0
#include<new>
#define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#include <iostream>
#define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1)
#endif

#include <stdlib.h>

class __malloc_alloc_template {
 private:
  static void* oom_malloc(size_t);
  static void* oom_realloc(void*, size_t);
  static void (* __malloc_alloc_oom_handler)();

 public:
  static void* allocate(size_t n)
  {
    void *result = malloc(n);
    if (0 == result)
      result = oom_malloc(n);
    return result;
  }

  static void deallocate(void *p, size_t)
  {
    free(p);
  }

  static void* reallocate(void *p, size_t, size_t new_sz)
  {
    void *result = realloc(p, new_sz);
    if (0 == result)
      result = oom_realloc(p, new_sz);
    return result;
  }

  static void (* set_malloc_handler(void (*f)()))()
  {
    void (* old)() = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = f;
    return old;
  }
};

void (* __malloc_alloc_template::__malloc_alloc_oom_handler)() = 0;

void* __malloc_alloc_template::oom_malloc(size_t n)
{
  void (* my_alloc_handler)();
  void *result;

  for (;;)
  {
    my_alloc_handler = __malloc_alloc_oom_handler;
    if (my_alloc_handler == 0)
      __THROW_BAD_ALLOC;
    my_alloc_handler();
    result = malloc(n);
    if (0 != result)
      return result;
  }
}

void* __malloc_alloc_template::oom_realloc(void *p, size_t n)
{
  void (*my_realloc_handler)();
  void *result;
  
  for (;;)
  {
    my_realloc_handler = __malloc_alloc_oom_handler;
    if (my_realloc_handler == 0)
      __THROW_BAD_ALLOC;
    my_realloc_handler();
    result = realloc(p, n);
    if (result)
      return result;
  }
}

typedef __malloc_alloc_template malloc_alloc;

enum {__ALIGN = 8};
enum {__MAX_BYTES = 128};
enum {__NFREELISTS = __MAX_BYTES/__ALIGN};

class __default_alloc_template {
 private:
  union obj{
    union obj *free_list_link;
    char client_data[1];
  };

 private:
  static size_t ROUND_UP(size_t n)
  {
    return ((n+__ALIGN-1) & ~(__ALIGN-1));
  }

 private:
  static size_t FREELIST_INDEX(size_t n)
  {
    return ((n+__ALIGN-1)/__ALIGN - 1);
  }
  static void* refill(size_t n);
  static char* chunk_alloc(size_t, int&);

 private:
  static obj *free_list[__NFREELISTS];
  static char *start_free;
  static char *end_free;
  static size_t heap_size;

 public:
  static void* allocate(size_t n);
  static void* reallocate(void*, size_t, size_t);
  static void deallocate(void*, size_t);
};

__default_alloc_template::obj *
 __default_alloc_template::free_list[__NFREELISTS] = 
  {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0};

char* __default_alloc_template::start_free = 0;
char* __default_alloc_template::end_free = 0;
size_t __default_alloc_template::heap_size = 0;

void* __default_alloc_template::allocate(size_t n)
{
  obj *result;
  obj **my_free_list;

  if (n > (size_t)__MAX_BYTES)
    return malloc_alloc::allocate(n);
  
  my_free_list = free_list + FREELIST_INDEX(n);
  result = *my_free_list;
  if (0 == result)
  {
    void *r = refill(ROUND_UP(n));
    return r;
  }
  
  *my_free_list = result->free_list_link;
  return (void*)result;
}

void* __default_alloc_template::refill(size_t n)
{
  int nobjs = 20;
  
  char *chunk = chunk_alloc(n, nobjs);
  
  if (1 == nobjs)
    return (void *)chunk;
  
  obj *result;
  obj *current_obj, *next_obj;
  obj **my_free_list;
  size_t i;

  my_free_list = free_list + FREELIST_INDEX(n);

  result = (obj *)chunk;
  *my_free_list = next_obj = (obj *)(chunk + n);
  for (i = 1; ; i++)
  {
    current_obj = next_obj;
    if (nobjs - 1 == i) {
      current_obj->free_list_link = 0;
      break;
    }
    next_obj = (obj *)((char *)current_obj + n);
    current_obj->free_list_link = next_obj;
  }

  return result;
}

char* __default_alloc_template::chunk_alloc(size_t n, int &nobjs)
{
  obj **my_free_list;
  char *result;
  size_t total_bytes = n * nobjs;
  size_t bytes_left = end_free - start_free;
  
  if (total_bytes <= bytes_left)
  {
    result = start_free;
    start_free += total_bytes;
    return result;
  }
  else if (bytes_left >= n)
  {
    result = start_free;
    nobjs = bytes_left / n;
    total_bytes = nobjs * n;
    start_free += total_bytes;
    return result;
  }
  else
  {
    size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
    if (bytes_left > 0)
    {
      my_free_list = free_list + FREELIST_INDEX(bytes_left);
      ((obj *)start_free)->free_list_link = *my_free_list;
      *my_free_list = (obj *)start_free;
    }
    
    start_free = (char *)malloc(bytes_to_get);
    if (0 == start_free)
    {
      int i;
      for (i = n; i <= __MAX_BYTES; i += __ALIGN)
      {
	my_free_list = free_list + FREELIST_INDEX(i);
	obj *p = *my_free_list;
	if (p)
	{
	  *my_free_list = p->free_list_link;
	  start_free = (char *)p;
	  end_free = start_free + i;
	  return (chunk_alloc(n, nobjs));
	}
      }
      
      end_free = 0;
      start_free = (char *)malloc_alloc::allocate(bytes_to_get);
    }
    
    end_free = start_free + bytes_to_get;
    heap_size += bytes_to_get;
    
    return (chunk_alloc(n, nobjs));
  }
}

void __default_alloc_template::deallocate(void *p, size_t n)
{
  obj *q = (obj *)p;

  if (n > (size_t)__MAX_BYTES)
  {
    malloc_alloc::deallocate(p, n);
    return;
  }
  
  obj **my_free_list;
  my_free_list = free_list + FREELIST_INDEX(n);
  q->free_list_link = *my_free_list;
  *my_free_list = q;
}

#ifdef __USE_MALLOC
typedef __malloc_alloc_template malloc_alloc;
typedef malloc_alloc alloc;

#else
typedef __default_alloc_template alloc;
#endif

template <class T, class Alloc>
class simple_alloc
{
  static T * allocate(size_t n)
  {
    return (T*)Alloc::allocate(n * sizeof(T));
  }
  static T *allocate(void)
  {
    return (T*)Alloc::allocate(sizeof(T));
  }
  static void deallocate(T *p, size_t n)
  {
    if (n != 0)
      Alloc::deallocate(p, n * sizeof(T));
  }
  static void deallocate(T *p)
  {
    Alloc::deallocate(p, sizeof(T));
  }
};
