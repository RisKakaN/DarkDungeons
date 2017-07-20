//
// Created by Martin So on 2017-07-09.
//

#include <sstream>
#include <SDL.h>
#include <rectangle.h>
#include <cmath>
#include <iostream>
#include <enemyLevel1.h>

#include "room.h"
#include "tinyxml2.h"
#include "graphics.h"
#include "player.h"
#include "enemy.h"
#include "enemyLevel1.h"

using namespace tinyxml2;

Room::Room() {}

Room::Room(std::string roomName, std::string spawnPosition, Graphics &graphics) :
        roomName(roomName),
        spawnPosition(spawnPosition),
        size(Vector2(0, 0)) {
    this->loadMap(roomName, graphics);
}

Room::~Room() {}

void Room::loadMap(std::string mapName, Graphics &graphics) {
    //Parse the .tmx file
    XMLDocument doc;
    std::stringstream ss;
    ss << "content/maps/" << mapName << ".tmx"; //Pass in Map 1, we get maps/Map 1.tmx
    doc.LoadFile(ss.str().c_str());

    XMLElement *mapNode = doc.FirstChildElement("map");

    //Get the width and the height of the whole map.
    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    this->size = Vector2(width, height);

    //Get the width and the height of the tiles.
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    this->tileSize = Vector2(tileWidth, tileHeight);

    //Loading the tilesets
    XMLElement *pTileset = mapNode->FirstChildElement("tileset");
    if (pTileset != NULL) {
        while (pTileset) {
            int firstgid;
            const char *source = pTileset->FirstChildElement("image")->Attribute("source");
            std::stringstream ss;

            ss << "content/tilesets/" << source;
            pTileset->QueryIntAttribute("firstgid", &firstgid);
            SDL_Texture *tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
            this->tilesets.push_back(Tileset(tex, firstgid));

            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }

    //Loading the layers.
    // Layer structure:  layer -> data -> tile
    XMLElement *pLayer = mapNode->FirstChildElement("layer");
    if (pLayer != NULL) {
        while (pLayer) {
            //Loading the data element.
            XMLElement *pData = pLayer->FirstChildElement("data");
            if (pData != NULL) {
                while (pData) {
                    //Loading the tile element.
                    XMLElement *pTile = pData->FirstChildElement("tile");
                    if (pTile != NULL) {
                        int tileCounter = 0;
                        while (pTile) {
                            //Build each individual tile here.
                            //If gid is 0, no tile should be drawn. Continue loop.
                            if (pTile->IntAttribute("gid") == 0) {
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                } else {
                                    break;
                                }
                            }

                            //Get the tileset for this specific gid
                            int gid = pTile->IntAttribute("gid");
                            Tileset tls;
                            for (int i = 0; i < this->tilesets.size(); i++) {
                                if (this->tilesets[i].FirstGid <= gid) {
                                    //This is the tileset we want
                                    tls = this->tilesets.at(i);
                                    break;
                                }
                            }

                            if (tls.FirstGid == -1) {
                                //No tileset was found for this gid
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                } else {
                                    break;
                                }
                            }

                            //Get the position of the tile in the map.

                            // While tileCounter increases:
                            // xx goes from 0 to width.
                            // yy goes from 0 to height.

                            // Everytime tileCounter goes to width:
                            // xx resets to 0 with the help of %.
                            // yy increases by 1.
                            int xx = 0;
                            int yy = 0;
                            xx = tileCounter % width;
                            xx *= tileWidth;
                            yy += tileHeight * (tileCounter / width);
                            Vector2 finalTilePosition = Vector2(xx, yy);

                            //Calculate the position of the tile in the tileset
                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
                            int tsxx = gid % (tilesetWidth / tileWidth) - 1;
                            tsxx *= tileWidth;
                            int tsyy = 0;
                            int amt = (gid / (tilesetWidth / tileWidth));
                            tsyy = tileHeight * amt;
                            Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

                            //Build the actual tile and add it to the level's tile list
                            Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
                                      finalTilesetPosition, finalTilePosition);
                            this->tileList.push_back(tile);
                            tileCounter++;

                            pTile = pTile->NextSiblingElement("tile");
                        }
                    }

                    pData = pData->NextSiblingElement("data");
                }
            }

            pLayer = pLayer->NextSiblingElement("layer");
        }
    }
    // Parse out the collisions.
    XMLElement *pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if (pObjectGroup != NULL) {
        while (pObjectGroup) {
            const char *name = pObjectGroup->Attribute("name");
            std::stringstream ss;
            ss << name;
            if (ss.str() == "collision") {
                XMLElement *pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x, y, width, height;
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        width = pObject->FloatAttribute("width");
                        height = pObject->FloatAttribute("height");
                        this->collisionRects.push_back(Rectangle(
                                // ceil rounds up to closest int.
                                std::ceil(x) * game_constants::TILE_SCALE,
                                std::ceil(y) * game_constants::TILE_SCALE,
                                std::ceil(width) * game_constants::TILE_SCALE,
                                std::ceil(height) * game_constants::TILE_SCALE
                        ));

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
                // Other objectgroups.
            } else if (ss.str() == "spawnPoint") {
                XMLElement *pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        const char *name = pObject->Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if (ss.str() == "spawnPointStart") {
                            this->spawnPointStart = Vector2(std::ceil(x) * game_constants::TILE_SCALE,
                                                            std::ceil(y) * game_constants::TILE_SCALE);
                        } else if (ss.str() == "spawnPointNorth") {
                            this->spawnPointNorth = Vector2(std::ceil(x) * game_constants::TILE_SCALE,
                                                            std::ceil(y) * game_constants::TILE_SCALE);
                        } else if (ss.str() == "spawnPointSouth") {
                            this->spawnPointSouth = Vector2(std::ceil(x) * game_constants::TILE_SCALE,
                                                            std::ceil(y) * game_constants::TILE_SCALE);
                        } else if (ss.str() == "spawnPointWest") {
                            this->spawnPointWest = Vector2(std::ceil(x) * game_constants::TILE_SCALE,
                                                           std::ceil(y) * game_constants::TILE_SCALE);
                        } else if (ss.str() == "spawnPointEast") {
                            this->spawnPointEast = Vector2(std::ceil(x) * game_constants::TILE_SCALE,
                                                           std::ceil(y) * game_constants::TILE_SCALE);
                        }
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            } else if (ss.str() == "door") {
                XMLElement *pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        float w = pObject->FloatAttribute("width");
                        float h = pObject->FloatAttribute("height");
                        Rectangle rect = Rectangle(x, y, w, h);

                        XMLElement *pProperties = pObject->FirstChildElement("properties");
                        if (pProperties != NULL) {
                            while (pProperties) {
                                XMLElement *pProperty = pProperties->FirstChildElement("property");
                                if (pProperty != NULL) {
                                    while (pProperty) {
                                        const char *name = pProperty->Attribute("name");
                                        std::stringstream ss;
                                        std::stringstream ssDest;
                                        std::stringstream ssPos;
                                        ss << name;
                                        if (ss.str() == "destination") {
                                            const char *value = pProperty->Attribute("value");
                                            ssDest << value;
                                        }
                                        pProperty = pProperty->NextSiblingElement("property");
                                        const char *name1 = pProperty->Attribute("name");
                                        std::stringstream ss1;
                                        ss1 << name1;
                                        if (ss1.str() == "position") {
                                            const char *value = pProperty->Attribute("value");
                                            ssPos << value;
                                        }
                                        pProperty = pProperty->NextSiblingElement("property");
                                        Door door = Door(rect, ssDest.str(), ssPos.str());
                                        this->doorList.push_back(door);
                                    }
                                }

                                pProperties = pProperties->NextSiblingElement("properties");
                            }
                        }

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            } else if (ss.str() == "enemy") {
                float x, y;
                XMLElement *pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        const char *name = pObject->Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if (ss.str() == "enemyLevel1") {
                            this->enemies.push_back(std::make_shared<EnemyLevel1>(graphics, Vector2(std::floor(x) *
                                                                                                    game_constants::TILE_SCALE,
                                                                                                    +std::floor(y) *
                                                                                                    game_constants::TILE_SCALE)));
                        }

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }

            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}

void Room::update(float elapsedTime, Player &player) {
    for (int i = 0; i < this->enemies.size(); i++) {
        this->enemies.at(i)->update(elapsedTime, player);
    }
}

void Room::draw(Graphics &graphics) {
    for (int i = 0; i < this->tileList.size(); i++) {
        this->tileList.at(i).draw(graphics);
    }

    for (int i = 0; i < this->enemies.size(); i++) {
        this->enemies.at(i)->draw(graphics);
    }
}

std::vector<Rectangle> Room::checkTileCollisions(const Rectangle &other) {
    std::vector<Rectangle> others;
    for (int i = 0; i < this->collisionRects.size(); i++) {
        if (this->collisionRects.at(i).collidesWith(other)) {
            others.push_back((Rectangle) this->collisionRects.at(i));
        }
    }
    return others;
}

std::vector<Door> Room::checkDoorCollisions(const Rectangle &other) {
    std::vector<Door> others;
    for (int i = 0; i < this->doorList.size(); i++) {
        if (this->doorList.at(i).collidesWith(other)) {
            others.push_back((Door) this->doorList.at(i));
        }
    }
    return others;
}

const Vector2 Room::getPlayerSpawnPoint() const {
    return spawnPosition == "north" ? this->spawnPointSouth :
           spawnPosition == "south" ? this->spawnPointNorth :
           spawnPosition == "west" ? this->spawnPointEast :
           spawnPosition == "east" ? this->spawnPointWest :
           this->spawnPointStart;
}