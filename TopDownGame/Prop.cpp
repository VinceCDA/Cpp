#include "Prop.h"
#include "raymath.h"
Prop::Prop(Vector2 position, Texture2D* texture) : _texture(texture), _worldPosition(position)
{
}
void Prop::Render(Vector2 kngihtPosition)
{
    Vector2 screenPosition = Vector2Subtract(_worldPosition, kngihtPosition);
    DrawTextureEx(*_texture, screenPosition, 0.0f, _scale, WHITE);
}

Rectangle Prop::GetCollisionRectangle(Vector2 kngihtPosition)
{
    Vector2 screenPosition = Vector2Subtract(_worldPosition, kngihtPosition);
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        _texture->width * _scale,
        _texture->height * _scale};
}
