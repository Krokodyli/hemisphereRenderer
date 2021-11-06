#include "drawManager.h"
#include "resourceManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

class SFMLDrawManager : public DrawManager {
 private:
  sf::RenderWindow *window;

  ResourceManager resourceManager;

  sf::Color colorToSFMLColor(Color c);
public:
  SFMLDrawManager(sf::RenderWindow *window, std::string execPath);
  virtual ~SFMLDrawManager();

  virtual void drawRectangle(Point<float> position, Point<float> size,
                             Color color);
  virtual void drawLine(Point<float> v1, Point<float> v2, Color color);
  virtual void drawText(Point<float> pos, std::string text,
                        int fontSize, Color color);
};
