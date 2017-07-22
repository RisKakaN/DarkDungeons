//
// Created by Martin So on 2017-07-21.
//

#include <cmath>
#include "hud.h"
#include "graphics.h"

Hud::Hud() {}

Hud::Hud(Graphics &graphics, Player &player) {
    this->player = player;
    // Health.
    this->healthBackgroundBarSprite = Sprite(graphics, "content/sprites/ui.png", 0, 48, 52, 12,
                                             10 * game_constants::SPRITE_SCALE -2, 3);
    this->healthBarSprite = Sprite(graphics, "content/sprites/ui.png", 0, 0, 50, 10, 20, 5);

    // Mana.
    this->manaBackgroundBarSprite = Sprite(graphics, "content/sprites/ui.png", 0, 48, 52, 12,
                                           90 * game_constants::SPRITE_SCALE -2, 3);
    this->manaBarSprite = Sprite(graphics, "content/sprites/ui.png", 0, 18, 50, 10, 90 * game_constants::SPRITE_SCALE,
                                 5);

    // Exp.
    this->expBackgroundBarSprite = Sprite(graphics, "content/sprites/ui.png", 0, 48, 52, 12,
                                          170 * game_constants::SPRITE_SCALE -2, 3);
    this->expBarSprite = Sprite(graphics, "content/sprites/ui.png", 0, 34, 50, 10, 170 * game_constants::SPRITE_SCALE,
                                5);
}

void Hud::update(float elapsedTime) {
    // Width of bars: 50px
    float healthAmount = (float) this->player.getCurrentHealth() / this->player.getMaxHealth();
    this->healthBarSprite.setSourceRectW(std::floor(healthAmount * 50));

    float manaAmount = (float) this->player.getCurrentMana() / this->player.getMaxMana();
    this->manaBarSprite.setSourceRectW(std::floor(manaAmount * 50));

    float expAmount = (float) this->player.getCurrentExp() / this->player.getMaxExp();
    this->expBarSprite.setSourceRectW(std::floor(expAmount* 50));
}

void Hud::draw(Graphics &graphics) {
    this->healthBackgroundBarSprite.draw(graphics, this->healthBackgroundBarSprite.getX(),
                                         this->healthBackgroundBarSprite.getY());
    this->healthBarSprite.draw(graphics, this->healthBarSprite.getX(), this->healthBarSprite.getY());

    this->manaBackgroundBarSprite.draw(graphics, this->manaBackgroundBarSprite.getX(),
                                       this->manaBackgroundBarSprite.getY());
    this->manaBarSprite.draw(graphics, this->manaBarSprite.getX(), this->manaBarSprite.getY());

    this->expBackgroundBarSprite.draw(graphics, this->expBackgroundBarSprite.getX(),
                                      this->expBackgroundBarSprite.getY());
    this->expBarSprite.draw(graphics, this->expBarSprite.getX(), this->expBarSprite.getY());

}