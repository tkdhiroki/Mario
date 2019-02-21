#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
