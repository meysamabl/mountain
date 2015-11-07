#ifndef NODE_H
#define NODE_H

#include <map>
using namespace std;

class Node
{
    public:
        /** Default constructor */
        Node();
        Node(int name);
        /** Default destructor */
        virtual ~Node();

        void addPath(int ch, double dest);

        bool operator== (const Node& rhs) {
            return this->name == rhs.name;
        }

        /** Access myPath
         * \return The current value of myPath
         */
        const multimap<int,double>& GetmyPath() const { return myPath; }
        /** Set myPath
         * \param val New value to set
         */
        void SetmyPath(multimap<int,double> val) { myPath = val; }
        /** Access name
         * \return The current value of name
         */
        int Getname() const { return name; }
        /** Set name
         * \param val New value to set
         */
        void Setname(int val) { name = val; }
    protected:
    private:
        multimap<int,double> myPath; //!< Member variable "myPath"
        int name; //!< Member variable "name"
};

#endif // NODE_H
