#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <set>
#include <bits/stdc++.h>
#ifndef _ConnectedComponents_h
#define _ConnectedComponents_h

    namespace MKXTSH013{
        class ConnectedComponents{
            //friend class ConnectedComponents;
            private:
                int j;
                int ComponentID;
                int numOfPixels;
                int numOfBoundryPixels;
                std::vector< std::pair<int,int> > pixels; // store our pixesl
                std::vector< std::pair<int,int> > boundaryPixels; // store boundry pixesl
            public:

                /*
                * CONSTRUCTORS AND DESTRUCTOR
                */
                ConnectedComponents();
                ConnectedComponents(int ComponentID);
                ConnectedComponents(int ComponentID, std::vector< std::pair<int,int> > pixels, int numOfPixels);
                ConnectedComponents(const ConnectedComponents & rhs);
                ConnectedComponents(ConnectedComponents && rhs);
                ~ConnectedComponents();

                /*
                * METHODS
                */
                void Add(int row, int column);
                void Display() const; // displays the details about the pixels
                void AddPixels(std::pair<int,int> pixel);
                void AddBoundryPixel(std::pair<int,int> boundayPixel);
                int getID() const; // returns the identifier
                int getNumOfPixels() const;
                int getNumOfBoundayPixels() const;
                std::vector< std::pair<int,int> > getPixels() const;
                std::vector< std::pair<int,int> > getBoundaryPixels();
        };

	/**************************************************Defines operator to compare values*************************************/
	class Compare {
        public:
            bool operator () (ConnectedComponents & a, ConnectedComponents & b);
    };

    bool operator < (const ConnectedComponents & a, const ConnectedComponents & b);
    }

#endif