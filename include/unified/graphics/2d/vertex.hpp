#ifndef _UNIFIED_GRAPHICS_2D_VERTEX_HPP
#define _UNIFIED_GRAPHICS_2D_VERTEX_HPP

# include <unified/graphics/vertex_fwd.hpp>
# include <unified/core/math/point2.hpp>
# include <unified/graphics/color.hpp>

UNIFIED_BEGIN_NAMESPACE
UNIFIED_GRAPHICS_BEGIN_NAMESPACE

template <class _type>
struct Vertex<_type, 2> : public Point<_type, 2>
{

    UNIFIED_CONSTEXPR Vertex() : Point<_type, 2>(), color() { }

    UNIFIED_CONSTEXPR Vertex(const Point<_type, 2> &point) : color() {
        this->x = point.x, this->y = point.y;
    }

    UNIFIED_CONSTEXPR Vertex(const Point<_type, 2> &point, const Color &color) : color(color) {
        this->x = point.x, this->y = point.y;
    }

    UNIFIED_CONSTEXPR bool operator==(const Vertex &r) const {
        return this->x == r.x && this->y == r.y && this->color == r.color;
    }

    UNIFIED_CONSTEXPR bool operator!=(const Vertex &r) const {
        return !this->operator==(r);
    }

    Color color;
};

typedef Vertex<unsigned, 2> Vertex2u;
typedef Vertex<int,      2> Vertex2i;
typedef Vertex<float,    2> Vertex2f;
typedef Vertex<double,   2> Vertex2d;

UNIFIED_GRAPHICS_END_NAMESPACE
UNIFIED_END_NAMESPACE

#endif