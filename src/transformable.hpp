#ifndef DEF_TRANSFORMABLE
#define DEF_TRANSFORMABLE

class Transformable{
    public:
        Transformable();

        /*
           Moves the transformable according to the offsets.
         */
        virtual void move(float offsetX, float offsetY) = 0;

        /*
           Sets the x and y coordinate of the transformable and change
           its direction according to them.
         */
        virtual void setPosition(float x, float y) = 0;

        /*
           Scroll the transformable according to its parameters.
         */
        virtual void scroll(int scrollX, int scrollY);

        /*
           Update the position of the sprite's transformable.
         */
        virtual void updatePosition() = 0;

        /*
           Returns the x absolute coordinate of the transformable.
         */
        virtual float getX() const;

        /*
           Returns the y absolute coordinate of the transformable.
         */
        virtual float getY() const;


    protected:
        float _x;
        float _y;
        int _scrollX;
        int _scrollY;
};

#endif
