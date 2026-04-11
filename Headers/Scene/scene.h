#pragma once

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void Load() {}
    virtual void Init() {}
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Shutdown() {}
};