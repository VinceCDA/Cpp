#include "raylib.h"
class Prop
{
private:
    Texture2D* _texture{};
    Vector2 _worldPosition{};
    float _scale{4.0f};

public:
    Prop(Vector2 position, Texture2D* texture);
    void Render(Vector2 kngihtPosition);
    Rectangle GetCollisionRectangle(Vector2 kngihtPosition);
};
