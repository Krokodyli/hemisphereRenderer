#include "selectbox.h"

Selectbox::Selectbox(Point<float> pos, std::string label,
                     const SelectboxTheme *theme)
  : theme(theme), pos(pos), label(label),
    previous(pos, theme->buttonSize, "<", theme->buttonTheme),
    next(Point<float>(pos.x + theme->buttonSize.x + theme->buttonGap * 2
                      + theme->textWidth, pos.y),
         theme->buttonSize, ">", theme->buttonTheme),
    currElement(0), eventHandler(nullptr) {

  previous.setOnClickHandler([this]() {
    if (elements.size() > 0) {
      currElement = (currElement + elements.size() - 1) % elements.size();
      tryToInvokeEventHandler();
    }
  });

  next.setOnClickHandler([this]() {
    if(elements.size() > 0) {
      currElement = (currElement + 1) % elements.size();
      tryToInvokeEventHandler();
    }
  });
}

void Selectbox::setOnChangeHandler(std::function<void(std::string val)>
                                   eventHandler) {
  this->eventHandler = eventHandler;
  tryToInvokeEventHandler();
}

void Selectbox::setElements(std::vector<std::string> newElements) {
  elements = newElements;
  for(unsigned int i = 0; i < elements.size(); i++) {
    if(elements[i].size() > theme->maxStringSize)
      elements[i] = elements[i].substr(0, theme->maxStringSize);
  }
  tryToInvokeEventHandler();
}

void Selectbox::draw(DrawManager *drawManager) {
  previous.draw(drawManager);

  if(currElement >= 0 && currElement < (int)elements.size()) {
    Point<float> textPos = pos;
    textPos.x += theme->buttonSize.x + theme->buttonGap;
    drawManager->drawText(textPos, elements[currElement], theme->fontSize,
                          theme->fontColor);
  }

  next.draw(drawManager);
}

void Selectbox::update(Controller *controller) {
  previous.update(controller);
  next.update(controller);
}

void Selectbox::tryToInvokeEventHandler() {
  if(eventHandler && currElement >= 0 && currElement < (int)elements.size())
    eventHandler(elements[currElement]);
}
