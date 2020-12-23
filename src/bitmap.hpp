#ifndef SRC_BITMAP_HPP__
#define SRC_BITMAP_HPP__

#include <algorithm>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace obl {

struct bitmap {
  std::size_t const width = 0;
  std::size_t const height = 0;
  std::vector<bool> data;
  bitmap(size_t x, size_t y) : width(x), height(y), data(x * y) {}

  bitmap(std::initializer_list<std::initializer_list<bool>> data)
      : width(std::max_element(data.begin(), data.end(),
                               [](auto const& a, auto const& b) {
                                 return a.size() > b.size();
                               })
                  ->size()),
        height(data.size()),
        data(height * width) {
    for (size_t i = 0; i < data.size(); ++i) {
      std::copy((data.begin() + i)->begin(), (data.begin() + i)->begin(),
                this->data.begin() + (width * i));
    }
  }

  void set(glm::fvec2, glm::ivec2);
  void set(glm::fvec2);
  void set(glm::uvec2);
  void set(size_t x, size_t y);
  void line(glm::fvec2, glm::fvec2);
  void clear();

  bool operator()(glm::uvec2) const;
  friend std::ostream& operator<<(std::ostream&, obl::bitmap const&);
};

}  // namespace obl
#endif  // SRC_BITMAP_HPP__
