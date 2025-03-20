#ifndef TILE_H
#define TILE_H

class Tile {
private:
    int value;

public:
    Tile(int val = 0);

    int getValue() const;

    void setValue(int val);

    bool isEmpty() const;
};

#endif // TILE_H
