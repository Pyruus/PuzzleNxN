#ifndef TILE_H
#define TILE_H

class Tile {
private:
    int value;
    int x;
    int y;

public:
    Tile();
    Tile(int value, int x, int y);
    int getValue() const;
    int getX() const;
    int getY() const;
    void setValue(int value);
    void setX(int x);
    void setY(int y);
    bool operator==(const Tile& other) const;
    bool operator!=(const Tile& other) const;
    bool operator<(const Tile& other) const;
};

#endif // TILE_H
