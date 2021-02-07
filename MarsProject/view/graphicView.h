#ifndef MARS_GRAPHICVIEW_H
#define MARS_GRAPHICVIEW_H

#include <SFML/Graphics.hpp>
#include "iGameView.h"

namespace mars
{
    class GraphicView : public IGameView /// singleton class
    {
    private:
        const int32_t width = 15;
        const int32_t height = 15;
        const int32_t widthTile = 50;
        const int32_t heightTile = 50;
        struct Tiles
        {
            sf::Texture textureUnknown;
            sf::Sprite spriteUnknown;

            sf::Texture textureOutOfBounds;
            sf::Sprite spriteOutOfBounds;

            sf::Texture textureEmpty;
            sf::Sprite spriteEmpty;

            sf::Texture textureRock;
            sf::Sprite spriteRock;

            sf::Texture textureBomb;
            sf::Sprite spriteBomb;

            sf::Texture textureApple;
            sf::Sprite spriteApple;

            sf::Texture textureHarvester;
            sf::Sprite spriteHarvester;

            sf::Texture textureSapper;
            sf::Sprite spriteSapper;

            Tiles();
        };
        Tiles tiles;
        static GraphicView *m_graphicView;

        GraphicView() = default;
    public:
        GraphicView(GraphicView &) = delete;
        ~GraphicView() override = default;

        void operator=(const GraphicView &) = delete;
        static GraphicView * getInstance();
        void draw(const LocalMap &, const Point &, const Point &, sf::RenderWindow &) override;
    };
}

#endif //MARS_GRAPHICVIEW_H
