//
// Created by omer siton on 31/12/2021.
//

#ifndef _VL_VECTOR_H_
#define _VL_VECTOR_H_
#include <algorithm>
#include <stdexcept>
#define DEF_IDX_ERR "Index out of range."
#define DEF_STATIC_CAP 16UL

template<typename T, size_t C=DEF_STATIC_CAP>
class vl_vector{
  T s_vector_ [C];
  T* d_vector_;
  size_t capacity_;
  size_t size_;
 public:
  /**
   * default ctor
   */
  vl_vector (): d_vector_(s_vector_), capacity_(C), size_(0){}
  /**
   * copy ctor
   * @param other - vl_vector to copy
   */
  vl_vector(const vl_vector<T, C>& other):
  d_vector_(s_vector_), capacity_(C), size_(0)
  {
    if (other.size_ > capacity_)
      static_to_heap (other.size_);
    std::copy (other.begin(), other.end(), begin());
    size_ = other.size_;
  }
  /**
   * iterator ctor
   * @tparam InputIterator - iterator class type
   * @param first - iterator begin
   * @param last - iterator end
   */
  template<class InputIterator>
  vl_vector(InputIterator first, InputIterator last):
  d_vector_(s_vector_), capacity_(C), size_(0)
  {
    auto ptrdiff = std::distance (first, last);
    if (ptrdiff > capacity_ )
      static_to_heap (ptrdiff);
    std::copy (first, last, begin());
    size_ = ptrdiff;
  }
  /**
   * constructor that fills count times the v value in this.
   * @param count
   * @param v
   */
  vl_vector (const size_t& count, const T& v):
  d_vector_(s_vector_), capacity_(C), size_(0)
  {
    if (count > capacity_)
        static_to_heap (count);
    std::fill_n (begin(), count, v);
    size_ += count;
  }
  /**
   * Destructor
   */
  ~vl_vector(){
    if (d_vector_ != s_vector_)
      delete [] d_vector_;
  }
  /**
   * Operator= / copy assigment
   * @param rhs - the vector to copy
   * @return reference to deep copy vl_vector of rhs.
   */
  vl_vector& operator=(const vl_vector<T, C>& rhs){
    if (this != &rhs){
      if (capacity_ < rhs.capacity_)
        d_vector_ = new T[rhs.capacity_];
      std::copy (rhs.begin(), rhs.end(), d_vector_);
      capacity_ = rhs.capacity_;
      size_ = rhs.size_;
    }
    return *this;
  }
  /// Iterators
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  iterator begin(){return d_vector_;}
  const_iterator begin()const{return d_vector_;}
  const_iterator cbegin()const{return d_vector_;}
  iterator end(){return d_vector_ + size_;}
  const_iterator end()const{return d_vector_ + size_;}
  const_iterator cend()const{return d_vector_ + size_;}
  reverse_iterator rbegin(){return reverse_iterator (end());}
  const_reverse_iterator rbegin()const{return const_reverse_iterator (cend());}
  const_reverse_iterator crbegin()const{return const_reverse_iterator(cend());}
  reverse_iterator rend(){return reverse_iterator (begin());}
  const_reverse_iterator rend()const{return const_reverse_iterator (cbegin());}
  const_reverse_iterator crend()const{return const_reverse_iterator(cbegin());}
  /// Getters
  size_t capacity () const {return capacity_;}
  size_t size () const {return size_;}
  /**
   *
   * @return - True if the vector is empty, otherwise False.
   */
  bool empty() const {return size_ == 0;}
  /**
   * non const version, throws an exception if index is out of range.
   * @param index
   * @return - a reference to the i'th element on the vector
   */
  T& at(int index){
    if ((size_t)index >= size_)
      throw std::out_of_range(DEF_IDX_ERR);
    return d_vector_[index];
  }
  /**
   * const version, throws an exception if index is out of range.
   * @param index
   * @return - a reference to the i'th element on the vector
   */
  const T& at(int index) const{
    if ((size_t)index >= size_)
      throw std::out_of_range(DEF_IDX_ERR);
    return d_vector_[index];
  }
  /// Operators
  /**
   * non const version
   * @param index
   * @return - a reference to the i'th element on the vector
   */
  T& operator[](int index){
    return d_vector_[index];
  }
  /**
   * const version
   * @param index
   * @return - a reference to the i'th element on the vector
   */
  const T& operator[](int index) const {
    return d_vector_[index];
  }
  /**
   * vectors are equals if they have the same elements and size,
   * with matching order.
   * @param rhs
   * @return - True if the two vectors are equal, False otherwise.
   */
  bool operator== (const vl_vector<T, C>& rhs) const{
    if (size_ != rhs.size_)
      return false;
    for (int i = 0; (size_t)i < size_; ++i)
      {
        if (this->d_vector_[i] != rhs.d_vector_[i])
          return false;
      }
    return true;
  }
  /**
   * vectors are equals if they have the same elements and size,
   * with matching order.
   * @param rhs
   * @return - False if the two vectors are equal, True otherwise.
   */
  bool operator!= (const vl_vector<T, C>& rhs) const{
    return !operator== (rhs);
  }
  /// Methods
  /**
   * push val to the back of the vector, if necessary switch vector to heap.
   * @param val
   */
  void push_back(const T& val){
    if (size_ == capacity_)
      capacity_ == C ? static_to_heap (1) : extend_dynamic_cap (1);
    d_vector_[size_] = val;
    ++size_;
  }
  /**
   * pop val to the back of the vector, if necessary switch vector to stack.
   * @param val
   */
  void pop_back(){
    if (size_ == 0)
      return;
//    d_vector_[size_] = T{};
    --size_;
    if (size_ == C){
      heap_to_static();
    }
  }
  /**
   * push val to the position pos of the vector,
   * if necessary switch vector to heap.
   * @param pos
   * @param val
   * @return an iterator to the added value position.
   */
  iterator insert(iterator pos, const T& val){
    if (size_ == capacity_){
      int index = it_to_idx(pos);
      capacity_ == C ? static_to_heap (1) : extend_dynamic_cap (1);
      pos = &d_vector_[index];
    }
    if (pos != end())
      std::move_backward(pos, end(), end()+1);
    *pos = val;
    ++size_;
    return pos;
  }
  /**
   * push val to the position pos of the vector,
   * if necessary switch vector to heap.
   * @param pos - const iterator
   * @param val
   * @return an iterator to the added value position.
   */
  iterator insert(const_iterator pos, const T& val){
    int index = it_to_idx (pos);
    iterator new_pos = &d_vector_[index];
    return insert(new_pos, val);
  }
  /**
   * push [first, last) to the position pos of the vector,
   * if necessary switch vector to heap.
   * @tparam InputIterator - template iterator
   * @param pos - iterator
   * @param first - first pos, included
   * @param last  - last pos, not included
   * @return - an iterator to the first pos after the insertion
   */
  template<class InputIterator>
  iterator insert(iterator pos, InputIterator first, InputIterator last){
    auto ptrdiff = std::distance (first, last);
    if (size_ + ptrdiff > capacity_){
      int index = it_to_idx(pos);
      capacity_ == C ? static_to_heap (ptrdiff) : extend_dynamic_cap (ptrdiff);
      pos = &d_vector_[index];
    }
    if (pos != end())
      std::move_backward(pos, end(), end()+ptrdiff);
    std::copy (first, last, pos);
    size_ += ptrdiff;
    return pos;
  }
  /**
   * push [first, last) to the position pos of the vector,
   * if necessary switch vector to heap.
   * @tparam InputIterator - template iterator
   * @param pos - const_iterator
   * @param first - first pos, included
   * @param last  - last pos, not included
   * @return - an iterator to the first pos after the insertion
   */
  template<class InputIterator>
  iterator insert(const_iterator pos, InputIterator first, InputIterator last){
    int index = it_to_idx (pos);
    iterator new_pos = &d_vector_[index];
    return insert(new_pos, first, last);
  }
  /**
   * pops val at position pos of the vector,
   * if necessary switch vector to stack.
   * @param pos - iterator
   * @return iterator to pos after erase
   */
  iterator erase(iterator pos){
    auto idx = it_to_idx (pos);
    std::move (pos+1, end(), pos);
    --size_;
    if (size_ == C)
      heap_to_static();
    return &d_vector_[idx];
  }
  /**
   * pops val at position pos of the vector,
   * if necessary switch vector to stack.
   * @param pos - const iterator
   * @return iterator to pos after erase
   */
  iterator erase(const_iterator pos){
    auto idx = it_to_idx (pos);
    std::move (pos+1, end(), pos);
    --size_;
    if (size_ == C)
      heap_to_static();
    return &d_vector_[idx];
  }
  /**
   * pops values [first, last) of the vector,
   * if necessary switch vector to stack.
   * @param first - iterator
   * @param last - iterator
   * @return - iterator to first after erase
   */
  iterator erase(iterator first, iterator last){
    auto idx = it_to_idx (first);
    auto ptrdiff = std::distance (first, last);
    std::move (last, end(), first);
    size_ -= ptrdiff;
    if (size_ == C)
      heap_to_static();
    return &d_vector_[idx];
  }
  /**
   * pops values [first, last) of the vector,
   * if necessary switch vector to stack.
   * @param first - const_iterator
   * @param last - const_iterator
   * @return - iterator to first after erase
   */
  iterator erase(const_iterator first, const_iterator last){
    auto idx = it_to_idx (first);
    auto ptrdiff = std::distance (first, last);
    std::move (last, end(), first);
    size_ -= ptrdiff;
    if (size_ == C)
      heap_to_static();
    return &d_vector_[idx];
  }
  /**
   * check if val is in vector
   * @param val - const T&
   * @return - True if found, False otherwise.
   */
  bool contains(const T& val) const{
    auto find = std::find (cbegin(), cend(), val);
    return find != cend();
  }
  /**
   * clears the vector and init the size and capacity.
   */
  void clear(){
    if (s_vector_ != d_vector_){
      delete [] d_vector_;
      d_vector_ = s_vector_;
      capacity_ = C;
    }
    size_ = 0;
  }
  /**
   *
   * @return - pointer to where the vector data is being held.
   */
  T* data(){
    return d_vector_;
  }
  /**
   *
   * @return - const_pointer to where the vector data is being held.
   */
  const T* data() const{
    return d_vector_;
  }
 private:
  /**
   * switch vector memory from the stack to the heap
   * @param k - number of elements we add to the vector
   */
  void static_to_heap(const size_t & k){
    capacity_ = capacity_c(size_, k);
    d_vector_ = new T[capacity_];
    std::copy (s_vector_, s_vector_ + size_, d_vector_);
  }
  void extend_dynamic_cap(const size_t& k){
    auto p = new T[size_];
    std::copy (d_vector_, d_vector_+size_, p);
    capacity_ = capacity_c(size_, k);
    d_vector_ = new T[capacity_];
    std::copy (p, p + size_, d_vector_);
  }
  /**
   * switch vector memory from the heap to the stack
   */
  void heap_to_static(){
    capacity_ = C;
    std::copy(begin(), end(), s_vector_);
    delete [] d_vector_;
    d_vector_ = s_vector_;
  }
  /**
   * convert an iterator to an index of the vector.
   * @tparam VecIterator - iterator / const_iterator
   * @param it
   * @return - index
   */
  template<class VecIterator>
  int it_to_idx(VecIterator it) const{
    int index = 0;
    while (&d_vector_[index] != it){
      ++index;
    }
    return index;
  }
  /**
   * calculate the new capacity we need to allocate on the heap
   * @param size - current vector size
   * @param k - number of elements we want to add
   * @return - new capacity.
   */
  static size_t capacity_c(const size_t& size, const size_t& k) {
    return ((3 * (size+k)) / (2));
  }
};
#endif //_VL_VECTOR_H_
