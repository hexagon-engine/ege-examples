#include <ege/gui/GUIScreen.h>
#include <ege/scene.h>
#include <ege/util.h>
#include <ege/util/GlobalConfig.h>

class MySceneObject : public EGE::SceneObject
{
public:
    EGE_SCENEOBJECT("MySceneObject") // This is required to assign a type to SceneObject to allow saving/loading them from files

    MySceneObject(EGE::Scene& scene)
    : EGE::SceneObject(scene) {}

    virtual void onInit() override
    {
        setPosition({EGE::randomDouble(10, 50), EGE::randomDouble(10, 50), 0});
    }
};

int main()
{
    // Enable debug overlay
    EGE::GlobalConfig::set(EGE::GlobalConfig::Option::SceneObject_Overlay);

    // Create loop, window and GUIScreen
    EGE::GUIGameLoop loop;
    auto window = loop.openWindow(sf::VideoMode(600, 600), "Scene and Objects");
    auto guiScreen = window->setNewGUIScreen<EGE::GUIScreen>();

    // Create a Scene and get Registry
    auto scene = make<EGE::Scene>(loop);
    auto& registry = scene->getRegistry();
    
    // Register a SceneObject
    registry.addType<MySceneObject>();

    // Add some SceneObjects
    for(size_t s = 0; s < 10; s++)
        scene->addNewObject<MySceneObject>();

    // Add a SceneWidget to make Scene visible
    guiScreen->addNewWidget<EGE::SceneWidget>(scene);

    // Run the game!
    return loop.run();
}
