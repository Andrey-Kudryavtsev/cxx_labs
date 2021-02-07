#include "graphicView.h"

namespace mars
{
    GraphicView * GraphicView::m_graphicView = nullptr;

    GraphicView::Tiles::Tiles()
    {
        textureUnknown.loadFromFile("../sources/unknown.png");
        textureOutOfBounds.loadFromFile("../sources/outofbounds.png");
        textureEmpty.loadFromFile("../sources/empty.png");
        textureRock.loadFromFile("../sources/rock.png");
        textureBomb.loadFromFile("../sources/bomb.png");
        textureApple.loadFromFile("../sources/apple.png");
        textureHarvester.loadFromFile("../sources/harvester.png");
        textureSapper.loadFromFile("../sources/sapper.png");
        spriteUnknown.setTexture(textureUnknown);
        spriteOutOfBounds.setTexture(textureOutOfBounds);
        spriteEmpty.setTexture(textureEmpty);
        spriteRock.setTexture(textureRock);
        spriteBomb.setTexture(textureBomb);
        spriteApple.setTexture(textureApple);
        spriteHarvester.setTexture(textureHarvester);
        spriteSapper.setTexture(textureSapper);
    }

    GraphicView * GraphicView::getInstance()
    {
        if (m_graphicView == nullptr)
        {
            m_graphicView = new GraphicView();
        }
        return m_graphicView;
    }

    void GraphicView::draw(const LocalMap & map, const Point &harvesterCoords, const Point &sapperCoords, sf::RenderWindow & window)
    {
        window.clear(sf::Color::Black);
        for (int32_t y = 0, i = harvesterCoords.m_y - height/2; y < height; ++y, ++i)
        {
            for (int32_t x = 0, j = harvesterCoords.m_x - width/2; x < width; ++x, ++j)
            {
                if (!map.inBounds(Point(j, i)))
                {
                    tiles.spriteUnknown.setPosition(x*widthTile, y*heightTile);
                    window.draw(tiles.spriteUnknown);
                    continue;
                }
                TileTypes tile = map.getTile(Point(j, i));
                switch (tile)
                {
                    case TileTypes::OUT_OF_BOUNDS:
                        tiles.spriteOutOfBounds.setPosition(x*widthTile, y*heightTile);
                        window.draw(tiles.spriteOutOfBounds);
                        break;
                    case TileTypes::UNKNOWN:
                        tiles.spriteUnknown.setPosition(x*widthTile, y*heightTile);
                        window.draw(tiles.spriteUnknown);
                        break;
                    case TileTypes::EMPTY:
                        tiles.spriteEmpty.setPosition(x*widthTile, y*heightTile);
                        window.draw(tiles.spriteEmpty);
                        break;
                    case TileTypes::ROCK:
                        tiles.spriteRock.setPosition(x*widthTile, y*heightTile);
                        window.draw(tiles.spriteRock);
                        break;
                    case TileTypes::BOMB:
                        tiles.spriteBomb.setPosition(x*widthTile, y*heightTile);
                        window.draw(tiles.spriteBomb);
                        break;
                    case TileTypes::APPLE:
                        tiles.spriteApple.setPosition(x*widthTile, y*heightTile);
                        window.draw(tiles.spriteApple);
                        break;
                    case TileTypes::HARVESTER:
                        tiles.spriteHarvester.setPosition(x*widthTile, y*heightTile);
                        window.draw(tiles.spriteHarvester);
                        break;
                    case TileTypes::SAPPER:
                        tiles.spriteSapper.setPosition(x*widthTile, y*heightTile);
                        window.draw(tiles.spriteSapper);
                        break;
                }
            }
        }
        tiles.spriteHarvester.setPosition(width/2*widthTile, height/2*heightTile);
        window.draw(tiles.spriteHarvester);
        if (sapperCoords.m_x >= 0 && sapperCoords.m_y >= 0)
        {
            tiles.spriteSapper.setPosition((width/2 + sapperCoords.m_x - harvesterCoords.m_x) * widthTile, (height/2 + sapperCoords.m_y - harvesterCoords.m_y) * heightTile);
            window.draw(tiles.spriteSapper);
        }
        window.display();
    }
}
