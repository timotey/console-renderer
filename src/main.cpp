#include <algorithm>
#include <chrono>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <vector>

#include "bitmap.hpp"

struct point {
  glm::fvec2 pos;
  glm::fvec2 vel;
};

int main() {
  obl::bitmap a(160, 160);
  std::vector<point> ps;
  ps.push_back({{0.5, 0.9}, {-0.010, 0}});
  ps.push_back({{0.5, 0.8}, {-0.005, 0}});
  ps.push_back({{0.5, 0.7}, {0.000, 0}});
  ps.push_back({{0.5, 0.6}, {0.005, 0}});
  ps.push_back({{0.5, 0.5}, {0.010, 0}});
  for (float size = 0;; size += 0.01) {
    for (auto& p : ps) {
      p.pos += p.vel * 0.1f;
      if (p.pos[0] > 1) {
        if (p.vel[0] > 0) p.vel[0] = -p.vel[0];
      } else if (p.pos[0] < -1) {
        if (p.vel[0] < 0) p.vel[0] = -p.vel[0];
      }
      if (p.pos[1] < -1) {
        if (p.vel[1] < 0) p.vel[1] = -p.vel[1];
      } else {
        p.vel[1] -= 0.001;
      }
    }
    for (size_t i = 0; i < ps.size(); ++i) {
      ps[i].pos[0] = std::sin(2 * i + size) * 0.5;
      ps[i].pos[1] = std::cos(2 * i + size) * 0.5;
    }

    for (size_t i = 0; i < a.height; ++i) {
      a.set(glm::uvec2{0, i});
      a.set(glm::uvec2{a.width - 1, i});
      a.set(glm::uvec2{i, 0});
    }
    for (auto const& p1 : ps)
      for (auto const& p2 : ps) a.line(p1.pos, p2.pos);
    for (auto const& p : ps) a.set(p.pos);
    a.set(ps[0].pos, {1, 1});
    a.set(ps[0].pos, {-1, 1});
    a.set(ps[0].pos, {1, -1});
    a.set(ps[0].pos, {-1, -1});
    std::cout << a;
    for (auto& p : ps) std::cout << p.pos[0] << ", " << p.pos[1] << "\n";
    a.clear();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  std::cin.ignore();
}
