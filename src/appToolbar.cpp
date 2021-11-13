#include "appToolbar.h"
#include "slider.h"
#include "checkbox.h"
#include "selectbox.h"
#include "mesh.h"

AppToolbar::AppToolbar(AppConsts *appConsts)
  : Toolbar(Point<int>(0, 0), Point<int>(0, 0)) {
  this->appConsts = appConsts;
  position = appConsts->toolbarPos;
  size = appConsts->toolbarSize;
  setUpControls();
}

void AppToolbar::setUpControls() {
  Point<float> pos = appConsts->toolbarControlsOffset;
  float smallGap = appConsts->toolbarSmallGap;
  float bigGap = appConsts->toolbarBigGap;

  makeCheckbox(&drawMeshCheckbox, pos, appConsts->defaultRenderMeshMode,
               appConsts->renderMeshModeLabel);
  pos.y += smallGap;
  makeSlider(&meridianCountSlider, pos,
             appConsts->minMeridianCount, appConsts->defaultMeridianCount,
             appConsts->maxMeridianCount, SliderType::IntegerSlider,
             appConsts->meridianCountLabel);
  pos.y += smallGap;
  makeSlider(&parallelsCountSlider, pos,
             appConsts->minParallelCount, appConsts->defaultParallelCount,
             appConsts->maxParallelCount, SliderType::IntegerSlider,
             appConsts->parallelCountLabel);
  pos.y += bigGap;

  makeSlider(&lightColorRSlider, pos, 0, appConsts->defaultLightColor.r,
             255, SliderType::IntegerSlider, appConsts->lightColorRLabel);
  pos.y += smallGap;
  makeSlider(&lightColorGSlider, pos, 0, appConsts->defaultLightColor.g,
             255, SliderType::IntegerSlider, appConsts->lightColorGLabel);
  pos.y += smallGap;
  makeSlider(&lightColorBSlider, pos, 0, appConsts->defaultLightColor.b,
             255, SliderType::IntegerSlider, appConsts->lightColorBLabel);
  pos.y += bigGap;

  makeCheckbox(&spiralLightMoveCheckbox, pos, appConsts->defaultSpiralMoveMode,
               appConsts->spiralSliderLabel);
  pos.y += smallGap;
  makeSlider(&lightZSlider, pos, appConsts->minLightZPos,
             appConsts->defaultLightZPos, appConsts->maxLightZPos,
             SliderType::FloatPointSlider, appConsts->lightZPosLabel);
  pos.y += bigGap;

  makeSlider(&kdSlider, pos, appConsts->minKD, appConsts->defaultKD,
             appConsts->maxKD, SliderType::FloatPointSlider,
             appConsts->kdLabel);
  pos.y += smallGap;
  makeSlider(&ksSlider, pos, appConsts->minKS, appConsts->defaultKS,
             appConsts->maxKS, SliderType::FloatPointSlider,
             appConsts->ksLabel);
  pos.y += smallGap;
  makeSlider(&mSlider, pos, appConsts->minM, appConsts->defaultM,
             appConsts->maxM, SliderType::IntegerSlider, appConsts->mLabel);
  pos.y += smallGap;
  makeSlider(&kSlider, pos, appConsts->minK, appConsts->defaultK,
             appConsts->maxK, SliderType::FloatPointSlider, appConsts->kLabel);
  pos.y += bigGap;
  makeSelectbox(&textureSelectBox, pos, appConsts->textureSelectboxLabel);
  pos.y += smallGap;
  makeSelectbox(&normalMapSelectBox, pos, appConsts->normalMapSelectboxLabel);
  pos.y += bigGap;
  makeCheckbox(&approxColoringModeCheckbox, pos, false,
               appConsts->approxColoringLabel);
}

void AppToolbar::setUpEventHandlers(RenderConfig *renderConfig) {
  meridianCountSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->mesh->setMeridianCount(val);
  });

  parallelsCountSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->mesh->setParallelCount(val);
  });

  lightColorRSlider->setOnValueChangeHandler([renderConfig](float val) {
    auto lightColor = renderConfig->lightColor;
    renderConfig->lightColor = Color(val, lightColor.g, lightColor.b);
  });

  lightColorGSlider->setOnValueChangeHandler([renderConfig](float val) {
    auto lightColor = renderConfig->lightColor;
    renderConfig->lightColor = Color(lightColor.g, val, lightColor.b);
  });

  lightColorBSlider->setOnValueChangeHandler([renderConfig](float val) {
    auto lightColor = renderConfig->lightColor;
    renderConfig->lightColor = Color(lightColor.r, lightColor.g, val);
  });

  kdSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->kd = val;
  });

  ksSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->ks = val;
  });

  mSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->m = val;
  });

  kSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->k = val;
  });

  lightZSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->lightPosition.z = val;
  });

  drawMeshCheckbox->setOnValueChangeHandler([renderConfig](bool val) {
    renderConfig->renderMeshMode = val;
  });

  spiralLightMoveCheckbox->setOnValueChangeHandler([renderConfig](bool val) {
    renderConfig->spiralMoveMode = val;
  });

  approxColoringModeCheckbox->setOnValueChangeHandler([renderConfig](bool val) {
    renderConfig->approximateColoringMode = val;
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
  *var = new Slider(pos, curr, min, max, type, label, appConsts->sliderTheme);
  controls.push_back(*var);
}

void AppToolbar::makeCheckbox(Checkbox **var, Point<float> pos,
                              bool initialState, std::string label) {
  *var = new Checkbox(pos, initialState, label, appConsts->checkboxTheme);
  controls.push_back(*var);
}

void AppToolbar::makeSelectbox(Selectbox **var, Point<float> pos,
                               std::string label) {
  *var = new Selectbox(pos, label, appConsts->selectboxTheme);
  controls.push_back(*var);
}
