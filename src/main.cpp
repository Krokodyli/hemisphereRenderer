#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "mesh.h"

int main(int argc, char **argv) {
  sf::Vector2f center(500, 500);
  int r = 400;
  Mesh mesh(sf::Vector3f(center.x, center.y, 0), r, 5, 32);
  std::cout << mesh.getTriangles().size() << std::endl;
  std::cout << mesh.getEdges().size() << std::endl;
  sf::RenderWindow window(sf::VideoMode(1000, 1000, 32), "Mesh");
  sf::CircleShape circle(r);
  circle.setPosition(sf::Vector2f(center.x - r, center.y - r));
  circle.setFillColor(sf::Color::Transparent);
  circle.setOutlineColor(sf::Color::White);
  circle.setOutlineThickness(2);
  window.draw(circle);
  for(auto p : mesh.getPoints()) {
    sf::CircleShape circle2(5);
    circle2.setFillColor(sf::Color::Red);
    circle2.setPosition(sf::Vector2f(p->x - 5, p->y - 5));
    window.draw(circle2);
  }
  for(auto edge : mesh.getEdges()) {
    sf::Vertex line[] = {
      sf::Vertex(sf::Vector2f(edge.a->x, edge.a->y)),
      sf::Vertex(sf::Vector2f(edge.b->x, edge.b->y))
    };
    window.draw(line, 2, sf::Lines);
  }
  window.display();
  bool isRunning = true;
  while(isRunning) {
    sf::sleep(sf::seconds(0.1));
    sf::Event ev;
    while(window.pollEvent(ev))
      if(ev.type == sf::Event::Closed)
        isRunning = false;
  }
  return 0;
}
