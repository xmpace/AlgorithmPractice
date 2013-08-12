
// 五种迭代器类型
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Catagory, class T, class Distance = ptrdiff_t,
  class Pointer = T*, class Reference = T&>
struct iterator
{
  typedef Catagory iterator_catagory;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;  
};

template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::iterator_catagory iterator_catagory;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;

};

template <class T>
struct iterator_traits <T*>
{
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag iterator_catagory;
  typedef T* pointer;
  typedef T& reference;
};
  
template <class T>
struct iterator_traits <const T*>
{
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag iterator_catagory;
  typedef const T* pointer;
  typedef const T& reference;
};

template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_catagory 
iterator_catagory(const Iterator&)
{
  typedef typename iterator_traits<Iterator>::iterator_catagory catagory;
  return catagory();
}

template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&)
{
  return static_cast<typename iterator_traits<Iterator>::difference_type>(0);
}

template <class Iterator>
inline typename iterator_traits<Iterator>::value_type
value_type(const Iterator&)
{
  return static_cast<typename iterator_traits<Iterator>::value_type>(0);
}

template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag)
{
  typename iterator_traits<InputIterator>::difference_type n = 0;
  while (first != last)
  {
    first++;
    n++;
  }
  return n;
}

template <class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last, 
random_access_iterator_tag)
{
  return last - first;
}

template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last)
{
  return __distance(first, last, iterator_catagory(first));
}

template <class InputIterator, class Distance>
  inline void __advance(InputIterator& i, Distance n, 
			input_iterator_tag)
{
  while (n--)
    i++;
}

template <class BidirectionalIterator, class Distance>
  inline void __advance(BidirectionalIterator& i, Distance n,
			bidirectional_iterator_tag)
{
  if (n > 0)
  {
    while (n--)
      ++i;
  }
  else
  {
    while (n++)
      --i;
  }
}

template <class Iterator, class Distance>
  inline void advance(Iterator& i, Distance n)
{
  __advance(i, n, iterator_catagory(i));
}


