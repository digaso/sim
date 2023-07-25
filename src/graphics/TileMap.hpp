#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

  bool load(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
  {
    // load the tileset texture

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
      for (unsigned int j = 0; j < height; ++j)
      {
        // get the current tile number
        int tileNumber = tiles[ i + j * width ];
        // get a pointer to the current tile's quad
        sf::Vertex* quad = &m_vertices[ (i + j * width) * 4 ];

        // define its 4 corners
        quad[ 0 ].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
        quad[ 1 ].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
        quad[ 2 ].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
        quad[ 3 ].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

        //define its color
        quad[ 0 ].color = sf::Color::White;
        quad[ 1 ].color = sf::Color::White;
        quad[ 2 ].color = sf::Color::White;
        quad[ 3 ].color = sf::Color::White;
      }

    return true;
  }

private:

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    // apply the transform
    states.transform *= getTransform();

 
    // draw the vertex array
    target.draw(m_vertices, states);
  }

  sf::VertexArray m_vertices;
  sf::Texture m_tileset;
};