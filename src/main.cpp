#include "Engine.h"

#include "MeshRenderer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "FreeMove.h"
#include "FreeLook.h"
#include "DebugComponent.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Logger.h"

class CoolGame : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void render(GLManager *glManager);
  virtual void update(int delta);

private:
  Entity *moneyHead;
  Entity *moneySmall;

  Entity *cameraNode;
  Camera *primary_camera;

  SpotLight *sl;
};

void CoolGame::render(GLManager *glManager)
{
  Game::render(glManager);
}

void CoolGame::update(int delta)
{
  static float angle = 0;
  angle += delta * 0.0008;
  // moneySmall->getTransform().setRotation(glm::vec3(0, 1, 0), glm::sin(angle));

  Game::update(delta);
}

void CoolGame::init(GLManager *glManager)
{
  moneyHead = new Entity();
  moneyHead->addComponent(new MeshRenderer(new Mesh(Asset("Pregnant.obj")), new Material(new Texture(Asset("Pregnant_D.tga")), new Texture(Asset("Pregnant_N.tga")), new Texture(Asset("Pregnant_S.tga")))));
  moneyHead->getTransform().setPosition(glm::vec3(0, -2, 0));
  moneyHead->getTransform().setScale(glm::vec3(2.3, 2.3, 2.3));
  moneyHead->getTransform().setScale(glm::vec3(0.7, 0.7, 0.7));



  addToScene(moneyHead);

  cameraNode = new Entity();

  Camera *cam1 = new Camera(45.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.9f, 100.0f);
  cameraNode->addComponent(cam1);
  cameraNode->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Material(new Texture(Asset("t.jpg")))));
  cameraNode->getTransform().setPosition(glm::vec3(0, 0, 8));

  addToScene(cameraNode);

  Entity *camera2Node = new Entity();

  Camera *cam2 = new Camera(45.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.1f, 100.0f);
  camera2Node->addComponent(cam2);
  camera2Node->addComponent(new FreeMove());
#if defined(ANDROID)
  camera2Node->addComponent(new FreeLook(0.0001f));
#else
  camera2Node->addComponent(new FreeLook());
#endif
  camera2Node->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Material(new Texture(Asset("t.jpg")))));
  camera2Node->getTransform().setPosition(glm::vec3(4, 0, 0));
  camera2Node->getTransform().setScale(glm::vec3(0.8, 0.8, 0.8));
  SpotLight *tsl = new SpotLight(glm::vec3(1.0f, 0.0f, 0.0f), 0.4f, 0.9f, new Attenuation(0, 0, 0.01f));
  camera2Node->addComponent(tsl);
  glManager->addLight(tsl);

  moneySmall = new Entity();
  moneySmall->addComponent(new MeshRenderer(new Mesh(Asset("monkey3.obj")), new Material(new Texture(Asset("t.jpg")))));
  moneySmall->getTransform().setPosition(glm::vec3(0, 2, 0));
  moneySmall->getTransform().setScale(glm::vec3(0.3, 0.3, 0.3));
  sl = new SpotLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.99f, new Attenuation(0, 0, 0.01f));
  moneySmall->addComponent(sl);
  glManager->addLight(sl);

  camera2Node->addChild(moneySmall);

  addToScene(camera2Node);

  primary_camera = cam1;

  glManager->setActiveCamera(primary_camera);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gm(&game);

  gm.start();

  return 0;
}
