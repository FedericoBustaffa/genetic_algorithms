#ifndef MAZE_HPP
#define MAZE_HPP

#include <cstddef>
#include <ostream>
#include <random>
#include <vector>

class maze
{
  public:
    maze(size_t height, size_t width) : m_height(height), m_width(width), engine(rd())
    {
        for (size_t i = 0; i < height; ++i)
        {
            for (size_t j = 0; j < width; ++j)
                m_maze.push_back(cell(i, j));
        }
    }

    size_t get_height() const { return m_height; }

    size_t get_width() const { return m_width; }

    void generate(size_t x, size_t y) {}

  private:
    size_t m_height, m_width;

    class cell
    {
      public:
        cell(size_t x, size_t y) : x(x), y(y) {}

        void add_neighbour(cell nb) { neighbours.push_back(nb); }

      private:
        size_t x;
        size_t y;
        std::vector<cell> neighbours;
    };

    std::vector<cell> m_maze;
    std::vector<bool> m_grid;

    std::random_device rd;
    std::mt19937 engine;
};

inline std::ostream& operator<<(std::ostream& os, const maze& m)
{
    os << m.get_height() << ", " << m.get_width();
    return os;
}

#endif  // !MAZE_HPP
