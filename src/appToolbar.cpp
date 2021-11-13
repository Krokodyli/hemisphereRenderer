#include "appToolbar.h"
#include "slider.h"
#include "checkbox.h"
#include "selectbox.h"

AppToolbar::AppToolbar(Point<int> position, Point<int> size)
  : Toolbar(position, size) {
  setUpControls();
}

void AppToolbar::setUpControls() {
  Point<float> pos(20, 20);
  float smallGap = 40;
  float bigGap = 70;

  makeCheckbox(&drawMeshCheckbox, pos, true, "Toggle mesh drawing");
  pos.y += smallGap;
  makeSlider(&meridianCountSlider, pos, 4, 30, 30, SliderType::IntegerSlider,
             "Meridian count");
  pos.y += smallGap;
  makeSlider(&parallelsCountSlider, pos, 1, 1, 8, SliderType::IntegerSlider,
             "Parallel count");
  pos.y += bigGap;

  makeSlider(&lightColorRSlider, pos, 0, 255, 255, SliderType::IntegerSlider,
             "Light color R");
  pos.y += smallGap;
  makeSlider(&lightColorGSlider, pos, 0, 255, 255, SliderType::IntegerSlider,
             "Light color G");
  pos.y += smallGap;
  makeSlider(&lightColorBSlider, pos, 0, 255, 255, SliderType::IntegerSlider,
             "Light color B");
  pos.y += bigGap;

  makeCheckbox(&spiralLightMoveCheckbox, pos, true, "Toggle spiral light move");
  pos.y += smallGap;
  makeSlider(&lightZSlider, pos, 320 * 1.5, 320 * 5, 320 * 10,
             SliderType::FloatPointSlider, "Light Z position");
  pos.y += bigGap;

  makeSlider(&kdSlider, pos, 0, 0.5, 1, SliderType::FloatPointSlider,
             "Kd factor");
  pos.y += smallGap;
  makeSlider(&ksSlider, pos, 0, 0.5, 1, SliderType::FloatPointSlider,
             "Ks factor");
  pos.y += smallGap;
  makeSlider(&mSlider, pos, 0, 50, 100, SliderType::IntegerSlider, "M factor");
  pos.y += smallGap;
  makeSlider(&kSlider, pos, 0, 0.5, 1, SliderType::FloatPointSlider,
             "K factor");
  pos.y += bigGap;
  makeSelectbox(&textureSelectBox, pos, "Texture");
  pos.y += smallGap;
  makeSelectbox(&normalMapSelectBox, pos, "Normal map");
  pos.y += bigGap;
  makeCheckbox(&approxColoringModeCheckbox, pos, false,
               "Approximate coloring mode");
}

void AppToolbar::setUpEventHandlers(RenderConfig *renderConfig) {
  meridianCountSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setMeridianCount(val);
  });

  parallelsCountSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setParallelCount(val);
  });

  lightColorRSlider->setOnValueChangeHandler([renderConfig](float val) {
    auto lightColor = renderConfig->getLightColor();
    renderConfig->setLightColor(Color(val, lightColor.getG(),
                                      lightColor.getB()));
  });

  lightColorGSlider->setOnValueChangeHandler([renderConfig](float val) {
    auto lightColor = renderConfig->getLightColor();
    renderConfig->setLightColor(Color(lightColor.getR(), val,
                                      lightColor.getB()));
  });

  lightColorBSlider->setOnValueChangeHandler([renderConfig](float val) {
    auto lightColor = renderConfig->getLightColor();
    renderConfig->setLightColor(Color(lightColor.getR(), lightColor.getG(),
                                      val));
  });

  kdSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setKD(val);
  });

  ksSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setKS(val);
  });

  mSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setM(val);
  });

  kSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setK(val);
  });

  lightZSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setLightZ(val);
  });

  drawMeshCheckbox->setOnValueChangeHandler([renderConfig](bool val) {
    renderConfig->setRenderMeshModeStatus(val);
  });

  spiralLightMoveCheckbox->setOnValueChangeHandler([renderConfig](bool val) {
    renderConfig->setSpiralMoveModeStatus(val);
  });

  approxColoringModeCheckbox->setOnValueChangeHandler([renderConfig](bool val) {
    renderConfig->setApproximateColoringMode(val);
  });

  auto names = renderConfig->getTexturesNames();
  names.push_back("None");
  textureSelectBox->setElements(names);
  textureSelectBox->setOnChangeHandler([renderConfig](std::string name) {
    renderConfig->setTexture(name);
  });

  names = renderConfig->getNormalMapsNames();
  names.push_back("None");
  normalMapSelectBox->setElements(names);
  normalMapSelectBox->setOnChangeHandler([renderConfig](std::string name) {
    renderConfig->setNormalMap(name);
  });
}

void AppToolbar::makeSlider(Slider **var, Point<float> pos, float min,
                            float curr, float max, SliderType type,
                            std::string label) {
  *var = new Slider(pos, curr, min, max, type, label);
  controls.push_back(*var);
}

void AppToolbar::makeCheckbox(Checkbox **var, Point<float> pos,
                              bool initialState, std::string label) {
  *var = new Checkbox(pos, initialState, label);
  controls.push_back(*var);
}

void AppToolbar::makeSelectbox(Selectbox **var, Point<float> pos,
                               std::string label) {
  *var = new Selectbox(pos, label);
  controls.push_back(*var);
}
