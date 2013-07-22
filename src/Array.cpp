#ifndef __ARRAY_H__
#define __ARRAY_H__

/*
 * Array.cpp -- Simple generic array class for pointers to classes
 *
 * NOTE: Does not typecheck nor do any casting, allowing for some form
 *       of polymorphism.
 */

#include <iostream>
#include <string>

namespace DAN {
  template <class E>
  class Array {
  public:
    Array();
    ~Array();

    void add(E *e);
    E *get(int index);
    E *remove(int index);
    int size();
    void clear();

  private:
    static const int INITAL_CAPACITY = 10;
    static const int EXPANSION_FACTOR = 2;
    
    E **m_array;
    int m_capacity;
    int m_size;
    
    void increaseCapacity();
  };

  template <class E>
  Array<E>::Array(){
    m_array = new E* [INITAL_CAPACITY];
    m_capacity = INITAL_CAPACITY;
    m_size = 0;
  }

  template <class E>
  void Array<E>::add(E *e){
    if(m_size >= m_capacity)
      increaseCapacity();

    m_array[m_size] = e;
    m_size++;
  }

  template <class E>
  void Array<E>::increaseCapacity(){
    int new_capacity = m_capacity << 1;
    E **temp = new E* [new_capacity];
    
    for(int i = 0; i < m_size; ++i){
      temp[i] = m_array[i];
    }

    delete [] m_array;
    m_array = temp;
    m_capacity = new_capacity;
  }

  template<class E>
  E* Array<E>::get(int index){
    if(index >= m_size)
      return NULL;
    return m_array[index];
  }

  template<class E>
  E* Array<E>::remove(int index){
    if(index >= m_size)
      return NULL;
    E *temp = m_array[index];

    m_size--;

    for(int i = index; index < m_size; ++i){
      m_array[i] = m_array[i + 1];
      m_array[i + 1] = NULL;
    }

    return temp;
  }

  template <class E>
  int Array<E>::size(){
    return m_size;
  }

  template <class E>
  void Array<E>::clear(){
    if(m_array != NULL) {
      
      //Delete all entries
      for(int i = 0; i < m_size; ++i){
	delete m_array[i];
	m_array[i] = NULL;
      }

      delete [] m_array;
      m_array = NULL;
    }
    
    m_capacity = 0;
    m_size = 0;
  }
  
  template <class E>
  Array<E>::~Array(){
    clear();
  }
}

#endif
