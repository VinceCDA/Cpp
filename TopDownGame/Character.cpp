#include "Character.h"
#include "raymath.h"
Character::Character(Texture2D *idleTexture, Texture2D *runTexture, Texture2D *weaponTexture, int windowWidth, int windowHeight) : _windowWidth(windowWidth), _windowHeight(windowHeight)
{
    _texture = idleTexture;
    _idleTexture = idleTexture;
    _runTexture = runTexture;
    _weaponTexture = weaponTexture;
    _width = _texture->width / _maxFrames;
    _height = _texture->height;
}
void Character::Tick(float deltaTime)
{
    if (!GetAlive())
    {
        return;
    }

    if (IsKeyDown(KEY_A))
        _velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        _velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        _velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        _velocity.y += 1.0;

    BaseCharacter::Tick(deltaTime);
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (_rightLeft > 0.0f)
    {
        origin = {0.0f, _weaponTexture->height * _scale};
        offset = {35.0f, 55.0f};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.0f : 0.0f;
        _weaponCollisionRectangle = {GetScreenPosition().x + offset.x,
                                     GetScreenPosition().y + offset.y - _weaponTexture->height * _scale,
                                     _weaponTexture->width * _scale,
                                     _weaponTexture->height * _scale};
    }
    else
    {
        origin = {_weaponTexture->width * _scale, _weaponTexture->height * _scale};
        offset = {25.0f, 55.0f};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.0f : 0.0f;
        _weaponCollisionRectangle = {GetScreenPosition().x + offset.x - _weaponTexture->width * _scale,
                                     GetScreenPosition().y + offset.y - _weaponTexture->height * _scale,
                                     _weaponTexture->width * _scale,
                                     _weaponTexture->height * _scale};
    }

    // draw sword
    Rectangle source{0.0f, 0.0f, static_cast<float>(_weaponTexture->width) * _rightLeft, static_cast<float>(_weaponTexture->height)};
    Rectangle destination{GetScreenPosition().x + offset.x, GetScreenPosition().y + offset.y, _weaponTexture->width * _scale, _weaponTexture->height * _scale};
    DrawTexturePro(*_weaponTexture, source, destination, origin, rotation, WHITE);
    //DrawRectangleLines(_weaponCollisionRectangle.x, _weaponCollisionRectangle.y, _weaponCollisionRectangle.width, _weaponCollisionRectangle.height, RED);
}

Vector2 Character::GetScreenPosition()
{
    return Vector2{static_cast<float>(_windowWidth) / 2.0f - _scale * (0.5f * _width), static_cast<float>(_windowHeight) / 2.0f - _scale * (0.5f * _height)};
}

Rectangle Character::GetWeaponCollisionRectangle()
{
    return _weaponCollisionRectangle;
}

float Character::GetHealth() const
{
    return _health;
}

void Character::TakeDamage(float damage)
{
    _health -= damage;
    if (_health <= 0.0f)
    {
        SetAlive(false);
    }
}
