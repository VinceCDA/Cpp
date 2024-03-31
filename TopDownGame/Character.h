#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"
class Character : public BaseCharacter
{
private:
    Texture2D *_weaponTexture{};
    int _windowWidth{};
    int _windowHeight{};
    Rectangle _weaponCollisionRectangle{};
    float _health{100.0f};

public:
    Character(Texture2D *idleTexture, Texture2D *runTexture, Texture2D *weaponTexture, int windowWidth, int windowHeight);
    virtual void Tick(float deltaTime) override;
    virtual Vector2 GetScreenPosition() override;
    Rectangle GetWeaponCollisionRectangle();
    float GetHealth() const;
    void TakeDamage(float damage);
};
#endif