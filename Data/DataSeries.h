//
// Created by yiwang on 17-5-10.
//

#ifndef ARIA_DATASERIES_H
#define ARIA_DATASERIES_H

#include <array>

template<class TIndex, class TVal, std::size_t size = 24 * 3600 * 2>
class DataSeries {
 public:
  DataSeries();
  DataSeries(const DataSeries &rhs);
  virtual ~DataSeries();
  DataSeries &operator=(const DataSeries &rhs);

 private:

 private:
  std::array<TIndex, size> _index_array;
  std::array<TVal, size> _val_array;
};

#endif //ARIA_DATASERIES_H
