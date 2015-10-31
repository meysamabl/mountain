#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        /** Default constructor */
        Point();

        Point(double xval, double yval, double zval);
        /** Default destructor */
        virtual ~Point();

        bool operator== (const Point& rhs)
        {
            return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
        }
        /** Access x
         * \return The current value of x
         */
        double getX() const { return x; }
        /** Set x
         * \param val New value to set
         */
        void setX(double val) { x = val; }
        /** Access y
         * \return The current value of y
         */
        double getY() const { return y; }
        /** Set y
         * \param val New value to set
         */
        void setY(double val) { y = val; }
        /** Access z
         * \return The current value of z
         */
        double getZ() const { return z; }
        /** Set z
         * \param val New value to set
         */
        void setZ(double val) { z = val; }
    protected:
    private:
        double x; //!< Member variable "x"
        double y; //!< Member variable "y"
        double z; //!< Member variable "z"
};

#endif // Point_H
