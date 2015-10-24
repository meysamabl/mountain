#ifndef NODE_H
#define NODE_H

#include <map>
using namespace std;

class Node
{
    public:
        /** Default constructor */
        Node();
        Node(char name);
        /** Default destructor */
        virtual ~Node();

        void addPath(char ch, int dest);

        bool operator== (const Node& rhs) {
            return this->name == rhs.name;
        }

        /** Access myPath
         * \return The current value of myPath
         */
        const multimap<char,int>& GetmyPath() const { return myPath; }
        /** Set myPath
         * \param val New value to set
         */
        void SetmyPath(multimap<char,int> val) { myPath = val; }
        /** Access name
         * \return The current value of name
         */
        char Getname() const { return name; }
        /** Set name
         * \param val New value to set
         */
        void Setname(char val) { name = val; }
    protected:
    private:
        multimap<char,int> myPath; //!< Member variable "myPath"
        char name; //!< Member variable "name"
};

#endif // NODE_H
