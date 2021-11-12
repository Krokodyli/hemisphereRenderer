#include "drawManager.h"
#include "sfmlResourceManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "sfmlBitmap.h"

class SFMLDrawManager : public DrawManager {
 private:
  sf::RenderWindow *window;

  sf::Texture texture;
  sf::Sprite sprite;

  SFMLResourceManager *resourceManager;

  sf::Color colorToSFMLColor(Color c);
public:
  SFMLDrawManager(sf::RenderWindow *window,
                  SFMLResourceManager *resourceManager);
  virtual ~SFMLDrawManager();

  virtual void drawRectangle(Point<float> pos, Point<float> size,
                             Color color);

  virtual void drawLine(Point<float> v1, Point<float> v2, Color color);

  virtual void drawText(Point<float> pos, std::string text,
                        int fontSize, Color color);

  virtual void drawBitmap(Point<float> pos, Bitmap *bitmap);

  virtual void drawSFMLImage(Point<float> pos, sf::Image *image);
};
