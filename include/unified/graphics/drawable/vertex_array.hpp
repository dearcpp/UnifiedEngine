#ifndef _UNIFIED_GRAPHICS_DRAWABLE_BUFFER_HPP
#define _UNIFIED_GRAPHICS_DRAWABLE_BUFFER_HPP

# include <unified/graphics/buffer.hpp>
# include <unified/graphics/drawable.hpp>
# include <unified/graphics/primitive_type.hpp>

# include <unified/graphics/math/vertex_fwd.hpp>

UNIFIED_BEGIN_NAMESPACE
UNIFIED_GRAPHICS_BEGIN_NAMESPACE

class VertexArray : public Drawable
{
public:

    VertexArray(PrimitiveType type, u32 vertices_dimension, u32 vertices_count, Buffer::Usage usage = Buffer::Usage::Static);

    virtual void draw(const RenderTarget &target) const override;

    template <class _type, u32 _dimension>
    void write(Vertex<_type, _dimension> vertex) {
        _buffer.allocate(sizeof(vertex)), _buffer.write((void*)&vertex, sizeof(vertex));
    }

    template <class _type, u32 _dimension>
    void write(Vertex<_type, _dimension> *data, u32 size) {
        _buffer.allocate(size), _buffer.write((void*)data, size);
    }

    template <class _type, u32 _dimension>
    void read(Vertex<_type, _dimension> *data, u32 size, u32 offset = 0) {
        _buffer.read(data, size, offset);
    }

    u32 size() {
        return _buffer.size();
    }

protected:

    Buffer _buffer;

    PrimitiveType _primitive_type;
    u32 _vertices_dimension, _vertices_count;

};

UNIFIED_GRAPHICS_END_NAMESPACE
UNIFIED_END_NAMESPACE

#endif