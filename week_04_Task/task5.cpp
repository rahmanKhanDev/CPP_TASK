#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;
// -------------------------- Singleton Pattern --------------------------

class HMISystem
{
public:
    static HMISystem &getInstance()
    {
        static HMISystem instance;
        return instance;
    }

    void changeMode(const string &mode)
    {
        currentMode = mode;
        notifyObservers();
    }

    const string &getCurrentMode() const
    {
        return currentMode;
    }

    void addObserver(function<void(const string &)> observer)
    {
        observers.push_back(observer);
    }

private:
    HMISystem() : currentMode("Day") {}
    string currentMode;
    vector<function<void(const string &)>> observers;

    void notifyObservers()
    {
        for (auto &observer : observers)
        {
            observer(currentMode);
        }
    }

    // Prevent copying and assignment
    HMISystem(const HMISystem &) = delete;
    HMISystem &operator=(const HMISystem &) = delete;
};

// -------------------------- Factory Pattern --------------------------

class Control
{
public:
    virtual void display() const = 0;
    virtual ~Control() = default;
};

class Button : public Control
{
public:
    void display() const override
    {
        cout << "Displaying Button\n";
    }
};

class Slider : public Control
{
public:
    void display() const override
    {
        cout << "Displaying Slider\n";
    }
};

class ControlFactory
{
public:
    static unique_ptr<Control> createControl(const string &type)
    {
        if (type == "Button")
        {
            return make_unique<Button>();
        }
        else if (type == "Slider")
        {
            return make_unique<Slider>();
        }
        return nullptr;
    }
};

// -------------------------- Observer Pattern --------------------------

class Widget
{
public:
    virtual void update(const string &mode) = 0;
    virtual ~Widget() = default;
};

class Label : public Widget
{
public:
    void update(const string &mode) override
    {
        cout << "Label updated for " << mode << " mode\n";
    }
};

class Icon : public Widget
{
public:
    void update(const string &mode) override
    {
        cout << "Icon updated for " << mode << " mode\n";
    }
};

// -------------------------- Strategy Pattern --------------------------

class RenderStrategy
{
public:
    virtual void render() const = 0;
    virtual ~RenderStrategy() = default;
};

class Render2D : public RenderStrategy
{
public:
    void render() const override
    {
        cout << "Rendering in 2D\n";
    }
};

class Render3D : public RenderStrategy
{
public:
    void render() const override
    {
        cout << "Rendering in 3D\n";
    }
};

// Context class for strategy
class Renderer
{
public:
    Renderer(unique_ptr<RenderStrategy> strategy) : strategy(std::move(strategy)) {}

    void setRenderStrategy(unique_ptr<RenderStrategy> newStrategy)
    {
        strategy = move(newStrategy);
    }

    void render() const
    {
        strategy->render();
    }

private:
    unique_ptr<RenderStrategy> strategy;
};

// -------------------------- Main Program --------------------------

int main()
{
    // Singleton Example
    cout << "Singleton Pattern:\n";
    HMISystem &hmiSystem = HMISystem::getInstance();
    hmiSystem.addObserver([](const string &mode)
                          { cout << "System switched to " << mode << " mode\n"; });
    hmiSystem.changeMode("Night");

    // Factory Example
    cout << "\nFactory Pattern:\n";
    auto button = ControlFactory::createControl("Button");
    auto slider = ControlFactory::createControl("Slider");
    button->display();
    slider->display();

    // Observer Example
    cout << "\nObserver Pattern:\n";
    Label label;
    Icon icon;
    hmiSystem.addObserver([&label](const string &mode)
                          { label.update(mode); });
    hmiSystem.addObserver([&icon](const string &mode)
                          { icon.update(mode); });
    hmiSystem.changeMode("Day");

    // Strategy Example
    cout << "\nStrategy Pattern:\n";
    Renderer renderer(make_unique<Render2D>());
    renderer.render();

    renderer.setRenderStrategy(make_unique<Render3D>());
    renderer.render();

    return 0;
}
