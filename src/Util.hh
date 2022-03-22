#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <raylib.h>

/**
 * Utilities for you to vibe with.
 */
namespace Util {
    /**
     * 2d Vector using integers.
     */
    struct Vec {
        int32_t x = 0;
        int32_t y = 0;

        /**
         * Default constructor creates a vector that is (0, 0).
         */
        Vec() = default;

        /**
         * Constructor where both dimensions are the same.
         * @param x is the value to give to all dimensinos.
         */
        Vec(int32_t x);

        /**
         * Does as you would expect.
         * @param x is the x component of the vector.
         */
        Vec(int32_t x, int32_t y);

        /**
         * Addition operator.
         * @param other is the vector to add.
         * @return a new added vector.
         */
        Vec operator+(Vec const &other) const;

        /**
         * Subtaction operator.
         * @param other is the other vec.
         * @return a new subtracted vec.
         */
        Vec operator-(Vec const &other) const;

        /**
         * Multiplication operator for other vecs.
         * @param other is the other vec.
         * @return a new vec.
         */
        Vec operator*(Vec const &other) const;

        /**
         * Multiplication with an int.
         * @param other is the int.
         * @return the multiplied version.
         */
        Vec operator*(int other) const;

        /**
         * Division operator.
         * @param other is the other vec.
         * @return a new vector that is divded.
         */
        Vec operator/(Vec const &other) const;

        /**
         * Division by an int.
         * @param other is the diovisor.
         * @return the divided vec.
         */
        Vec operator/(int other) const;

        /**
         * Adds a vector to this one.
         * @param other is the vector to add.
         * @return this.
         */
        Vec &operator+=(Vec const &other);

        /**
         * Tells you if this vector is equal to another.
         * @param other is the other vector to check against.
         * @return true iff they are equal.
         */
        bool operator==(Vec const &other) const;

        /**
         * Gives you a version of this vec where every value above 0 becomes
         * 1 and every value below 0 becomes -1.
         * @return the sign version of this vector.
         */
        Vec sign() const;

        /**
         * Gives the vector as absolute values.
         * @return new vector with absolute values of this vector.
         */
        Vec abs() const;

        /**
         * Calculates the lowest of the vectors values.
         * @return the lower value.
         */
        int32_t min() const;

        /**
         * Calculates the hightes of the vector's values.
         * @return the higher value.
         */
        int32_t max() const;

        /**
         * Returns a raylib vector version of this vector.
         * @return raylib vector.
         */
        Vector2 toVector2() const;
    };

    /**
     * 2d rectangle using integers.
     */
    struct Rect {
        int32_t x = 0;
        int32_t y = 0;
        int32_t width = 0;
        int32_t height = 0;

        /**
         * Default constructor makes the rect have a position of (0, 0) and no
         * size.
         */
        Rect() = default;

        /**
         * Does what you would expect.
         * @param x is the x component of the rect.
         * @param y is the y component of the rect.
         * @param width is the width of the rect.
         * @param height is the height of the rect.
         */
        Rect(int32_t x, int32_t y, int32_t width, int32_t height);

        /**
         * Multiplies the rect by a vec and gives you the result.
         * @param vec the vector to multiply by.
         * @return the new multip[lied version.
         */
        Rect operator*(Vec const &vec) const;

        /**
         * Gives you the raylib version of the rectangle.
         * @return the raylib version.
         */
        Rectangle toRectangle() const;
    };

    /**
     * Stream output operator so you can print them nicely for debug and
     * stuff.
     * @param output is the output stream to write to.
     * @param v is the vector to write.
     * @return the output stream.
     */
    std::ostream &operator<<(std::ostream &output, Vec const &v);

    /**
     * Stream output operator so you can print them nicely for debug and
     * stuff.
     * @param output is the output stream to write to.
     * @param r is the rectangle to describe.
     * @return the output stream.
     */
    std::ostream &operator<<(std::ostream &output, Rect const &r);

    /**
     * Gives you the rectangle that takes up the most space within the given
     * bounds while maintaining it's aspect ratio, and also it's centred.
     * @param width is the width of the conceptual shape.
     * @param height is the height of the conceptual shape.
     * @param bounds is the rectangle to fit the shape within.
     * @return a rectangle with the same aspect ratio of width and height but
     *         centred inside bounds taking the max amount of space possible.
     */
    Rectangle fit(int width, int height, Rectangle bounds);

    /**
     * Sign function turns values above 0 to 1 and values below 0 to -1.
     * @param x the value to apply to.
     * @return the sign version.
     */
    int sign(int x);
};

/**
 * Hashing thingy for vecs.
 */
template<> struct std::hash<Util::Vec> {
    /**
     * Executor.
     * @param v is the vec to hash.
     * @return the hashed version.
     */
    std::size_t operator()(Util::Vec const &v) const noexcept {
        return v.x ^ (v.y << 4);
    }
};


#endif
