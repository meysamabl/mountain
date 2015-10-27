#ifndef LOCATION_H
#define LOCATION_H


class Location
{
    public:
        /** Default constructor */
        Location();

        Location(double xval, double yval, double zval);
        /** Default destructor */
        virtual ~Location();

        bool operator== (const Location& rhs)
        {
            return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
        }
        /** Access x
         * \return The current value of x
         */
        double Getx() { return x; }
        /** Set x
         * \param val New value to set
         */
        void Setx(double val) { x = val; }
        /** Access y
         * \return The current value of y
         */
        double Gety() { return y; }
        /** Set y
         * \param val New value to set
         */
        void Sety(double val) { y = val; }
        /** Access z
         * \return The current value of z
         */
        double Getz() { return z; }
        /** Set z
         * \param val New value to set
         */
        void Setz(double val) { z = val; }
    protected:
    private:
        double x; //!< Member variable "x"
        double y; //!< Member variable "y"
        double z; //!< Member variable "z"
};

#endif // LOCATION_H
