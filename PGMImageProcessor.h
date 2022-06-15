
#include "ConnectedComponents.h"

#ifndef _PGMImageProcessor_h
#define _PGMImageProcessor_h

    namespace MKXTSH013{
        class PGMImageProcessor{
            private:

                // 5x3 array with colours
                unsigned char colours[5][3] = {
                    {255,0,0},//red
                    {0,255,0},//green
                    {0,0,255},//blue
                    {255,255,0},//yellow
                    {0,255,255} // magenta
                };
                int j;
                int minimum, maximum;// maximun = rows*columns and minimum =3
                unsigned char** image; // dynamicaly allocated array in 2D, stores input image
                unsigned char** visited; // an array to store visited when extracting components
                //std::set<std::shared_ptr<ConnectedComponents>> Components ;
                std::vector< std::shared_ptr<ConnectedComponents> > Components; // stores components
                std::set< std::shared_ptr<ConnectedComponents> > setComp;
                std::shared_ptr<ConnectedComponents> component;/////////////////////////////////////////////////////////
                int rows, columns; // dimensions of the image
                int lsize =0; // largest size
                int ssize; // smallest size
                std::string path; // image path
                int threshold;
                int width, height;
                int ID;
                int ss,ll;
            public:
                /*
                * CONSTRUcTOR AND DESTRUCTOR
                */
                PGMImageProcessor(); //default constructor
                ~PGMImageProcessor(); //DESTRUCTOR

                 /*
                 * METHODS
                 */

                 /* Read image */
                 bool readFile(std::string filename);

                 /* process the input image to extract all the connected components,
                 based on the supplied threshold (0...255) and excluding any components
                 of less than the minValidSize. The final number of components that
                 you store in your container (after discarding undersized one)
                 must be returned.
                 */
                 int extractComponents(unsigned char threshold, int minValidSize);

                 // do a bfs to fing connected neighbours
                 int getNeighbours(std::shared_ptr<ConnectedComponents> component, std::queue<std::pair<int, int> > Q, std::pair<int,int> currentPair, int threshold);

                 /* iterate - with an iterator - though your container of connected
                 components and filter out (remove) all the components which do not
                 obey the size criteria pass as arguments. The number remaining
                 after this operation should be returned.
                 */
                 int filterComponentsBySize(int minSize, int maxSize);

                 /* create a new PGM file which contains all current components
                 (255=component pixel, 0 otherwise) and write this to outFileName as a
                 valid PGM. the return value indicates success of operation
                 */
                 bool writeComponents(const std::string & outFileName);

                 // return number of components
                 int getComponentCount(void) const;

                 // return number of pixels in largest component
                 int getLargestSize(void) const;

                 // return number of pixels in smallest component
                 int getSmallestSize(void) const;

                 /* print the data for a component to std::cout
                 see ConnectedComponents class;
                 print out to std::cout: component ID, number of pixels
                 */
                 void printComponentData(const ConnectedComponents & theComponent) const;

                 //function so the component are ordered from smallest to largest by size
                 bool compareComponents (const ConnectedComponents & lhs, const ConnectedComponents & rhs);

                 //write out coloured components in a flie callled outFileName
                 bool ColouredComponents(const std::string &outFileName);

                 void f(int threshold, unsigned char** image,int rows, int columns);
                 // print the ID and numOfPixels
                 void printAll();


        };
    }

#endif