//
// Created by Ivan Galakhov on 2019-02-06.
//

#include "drawer.h"

// draws a rectangle with diagonals
void Drawer::draw_rectangle(int x, int y, int w, int h) {
    draw_line(x, y, x + w, y);
    draw_line(x, y, x, y + h);
    draw_line(x + w, y, x + w, y + h);
    draw_line(x, y + h, x + w, y + h);
    if (random() % 2 == 1)
        draw_line(x, y, x+w, y+h);
    if (random() % 2 == 1)
        draw_line(x, y+h, x+w, y);
}

void Drawer::draw_line(int x1, int y1, int x2, int y2) {
    // make sure x1 <= x2
    if (x1 > x2){
        draw_line(x2, y2, x1, y1);
        return;
    }

    // draws a line from (x1, x2) to (y1, y2)

    // make sure values are correct
    assert(x1 >= 0 and x1 < IMAGE_WIDTH);
    assert(x2 >= 0 and x2 < IMAGE_WIDTH);
    assert(y1 >= 0 and y1 < IMAGE_HEIGHT);
    assert(y2 >= 0 and y2 < IMAGE_HEIGHT);

    // get constants
    int dy = y2 - y1;
    int dx = x2 - x1;
    int a = dy;
    int b = -1*dx;

    //printf("dy: %d, dx: %d, a: %d, b: %d\n", dy, dx, a, b);

    // figure out the octet (amazing code right there)
    char octet = -1;
    if(dy == 0) octet = 1;
    else if(dx == 0)
        if(y2 > y1) octet = 2;
        else octet = 7;
    else if(dy > 0)
        if(dy > dx) octet = 2;
        else octet = 1;
    else
        if(abs(dy) > dx) octet = 7;
        else octet = 8;

    assert(octet != -1); // octet should be set

    // more values
    int x = x1;
    int y = y1;
    int d = 2*a + b;

    switch(octet){
        case 1:
            while(x <= x2){
                set(x, y);
                if(d > 0){
                    y++;
                    d += 2*b;
                }
                x++;
                d += 2*a;
            }
            break;
        case 2:
            while(y <= y2){
                set(x, y);
                if(d < 0){
                    x++;
                    d += 2*a;
                }
                y++;
                d += 2*b;
            }
            break;
        case 8:
            while(x <= x2){
                set(x, y);
                if(d < 0){
                    y--;
                    d -= 2*b;
                }
                x++;
                d += 2*a;
            }
            break;
        case 7:
            while(y >= y2){
                set(x, y);
                if(d > 0){
                    x++;
                    d += 2*a;
                }
                y--;
                d -= 2*b;
            }
            break;
    }

}

void Drawer::set(int x, int y){
    assert(x < IMAGE_WIDTH and y < IMAGE_HEIGHT);

    Display::set(x, y, &cur_color);
}

void Drawer::change_color(unsigned char r, unsigned char g, unsigned char b){
    cur_color.r = r;
    cur_color.g = g;
    cur_color.b = b;
}

Drawer::Drawer() {
    cur_color.r = 0;
    cur_color.g = 0;
    cur_color.b = 0;
}

