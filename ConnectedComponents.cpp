
#include "ConnectedComponents.h"

/*
* CONSTRUCTORS AND DESTRUCTOR
*/
namespace MKXTSH013{

        // default constructor
         ConnectedComponents :: ConnectedComponents() : j(0) {}
        //custom constructor
         ConnectedComponents::ConnectedComponents(int ID):  ComponentID(ID), numOfPixels(0),numOfBoundryPixels(0){}

        //copy constructor
         ConnectedComponents::ConnectedComponents(int ComponentID, std::vector< std::pair<int,int> > pixels,int numOfPixels):
        ComponentID(ComponentID),
        numOfPixels(numOfPixels),
        pixels(pixels){}

        // move constructor
         ConnectedComponents::ConnectedComponents(ConnectedComponents && rhs): ComponentID(rhs.getID()), numOfPixels(rhs.getNumOfPixels()){
                pixels = std::move(rhs.pixels);
        }
         ConnectedComponents::ConnectedComponents(const ConnectedComponents & rhs) : ComponentID(rhs.getID()),numOfPixels(rhs.getNumOfPixels()),pixels(rhs.pixels){}

        //destructor
         ConnectedComponents::~ConnectedComponents() { pixels.clear(); }

        /*
        * METHODS
        */

        // add boundary pixels
        void  ConnectedComponents::Add(int row, int column){
            pixels.push_back(std::make_pair(row,column));
            numOfPixels += 1;
        }

        // displays the details about the pixels
        void  ConnectedComponents::Display() const{
            std::cout<< "Component" << ComponentID <<" contains "<< numOfPixels << " pixels. " << std::endl;
        }
        // returns component Identifier
        int  ConnectedComponents::getID() const{
            return ComponentID;
        }
        //get the number of pixels
        int  ConnectedComponents::getNumOfPixels() const {
            return this->numOfPixels;
        }

        //get the number of pixels
        int ConnectedComponents::getNumOfBoundayPixels() const {
            return this->numOfPixels;
        }

        //add pixels
        void ConnectedComponents::AddPixels(std::pair<int, int> p){
            pixels.push_back(p);
            numOfPixels += 1;
        }
        // Add component boundary pixels
        void  ConnectedComponents::AddBoundryPixel(std::pair<int,int> boundayPixel){
            boundaryPixels.push_back(boundayPixel);
            numOfBoundryPixels++;
        }

        //return pixels
        std::vector< std::pair<int,int> > ConnectedComponents::getPixels() const{
            return std::move(pixels);
        }
        // return component boundaries
        std::vector< std::pair<int,int> >  ConnectedComponents :: getBoundaryPixels(){
            return std::move(boundaryPixels);

        }
        /*
        * Following defines appropriate comparison/ordering function so the component are ordered from smallest to largest by size*/
        bool Compare :: operator () ( ConnectedComponents & a,ConnectedComponents & b) {
            return b < a;
        }

        bool  operator < (const  ConnectedComponents & a, const ConnectedComponents & b) {
            return a.getID() < b.getID();
        }

}
