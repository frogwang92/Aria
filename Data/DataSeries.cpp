//
// Created by yiwang on 17-5-10.
//

#include "DataSeries.h"

template<class TIndex, class TVal, std::size_t size>
DataSeries<TIndex, TVal, size>::DataSeries() {

}

template<class TIndex, class TVal, std::size_t size>
DataSeries<TIndex, TVal, size>::DataSeries(const DataSeries &rhs) {

}

template<class TIndex, class TVal, std::size_t size>
DataSeries<TIndex, TVal, size>::~DataSeries() {

}

template<class TIndex, class TVal, std::size_t size>
DataSeries<TIndex, TVal, size> &DataSeries<TIndex, TVal, size>::operator=(const DataSeries &rhs) {
  if (&rhs != this) {

  }
  return *this;
}
