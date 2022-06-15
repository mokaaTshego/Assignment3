#include "PGMImageProcessor.h"


/*
* CONSTRUCTORS AND DESTRUCTOR
*/

namespace MKXTSH013{
PGMImageProcessor::PGMImageProcessor():
    rows(0),
    columns(0),
    ID(0),
    threshold(128),
    minimum(3),
    ss(-1),
    ll(6){
    component = nullptr;
}

 PGMImageProcessor::~PGMImageProcessor(){
    for(int i =0; i<rows; ++i){
        delete [] image[i];
        delete [] visited[i];
    }
    delete [] image;
    delete [] visited;
}
/*
* METHODS
*/

// reading the pgm
// can you do unit test for me?
//create small pgm files then maybe 50 x 50
//emial me the code so i do mistery work aside
//okay
bool PGMImageProcessor :: readFile(std::string filename){
    unsigned char * rawImage;
    std::string header;

    // read image from file
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);

    if(!ifs){ //file not opened
        return false;
    }
    else{ // file Opened

        std::getline(ifs, header);
        std::getline(ifs, header);

        // Check if line is a comment
        while(header[0] == '#'){
        std::getline(ifs, header);
        }

        rows = std::stoi( header.substr( 0, header.find(" ") ) );
        columns = std::stoi( header.substr( header.find(" ") + 1 ) );
        maximum = rows*columns;

        std::getline(ifs, header); // 255

        rawImage = new unsigned char[columns * rows];

        // read temporary as char
        char * temp = new char [columns * rows];
        ifs.read(temp, columns*rows);
        rawImage = reinterpret_cast<unsigned char *>(temp);

        image = new unsigned char * [rows];
        for (int i = 0; i < rows; ++i){
            image[i] = new unsigned char [columns];
            for (int j = 0; j < columns; ++j){
                image[i][j] = rawImage[i*columns + j];
            }
        }

        return true;
        delete [] rawImage; // delete raw image
    }
    return true;
}




int  PGMImageProcessor :: getNeighbours(std::shared_ptr<ConnectedComponents> component, std::queue<std::pair<int, int> > Q, std::pair<int,int> currentPair, int threshold){
    while (!Q.empty()){
        // Extrating front pair
        std::pair<int, int> coord = Q.front();
        int y = coord.first;
        int x = coord.second;

        Q.pop();
        if((y > 0) && (x > 0) && (x != (columns - 1)) && (y != (rows - 1))){
            if (image[y][x] >= threshold && visited[y][x]){
                Q.push(std::move(std::make_pair(y-1,x)));
                Q.push(std::move(std::make_pair(y,x-1)));
                Q.push(std::move(std::make_pair(y,x+1)));
                Q.push(std::move(std::make_pair(y+1,x)));
                visited[y][x] = 0;
                component->AddPixels(coord);
            }
        }
        else{
            component->AddBoundryPixel(coord);
        }
        //

    }
    return component->getNumOfPixels();
}

/* process the input image to extract all the connected components,
based on the supplied threshold (0...255) and excluding any components
of less than the minValidSize. The final number of components that
you store in your container (after discarding undersized one)
must be returned.
*/
int  PGMImageProcessor :: extractComponents(unsigned char threshold, int minValidSize){
    f(threshold, image,rows,columns);

    // Set Q to the empty queue
   // std::queue<std::pair<int, int> > Q;
    int IDD=0;
    int comp = 0; // number of components

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < columns; ++j){

            if (visited[i][j] && image[i][j]==255){
                std::vector< std::pair<int,int> > pp;// = {{}};
                //std::cout << image[i][j]
                std::queue<std::pair<int, int> > Q;

                // Pushing pair of {x, y}
                Q.push({ i, j });

                // Marking {x, y} as visited
                //visited[i][j] = 0;

                // Untill queue is emppty
                while (!Q.empty())
                {
                    // Extrating front pair
                	std::pair<int, int> coord = Q.front();
                	int x = coord.first;
                	int y = coord.second;

                    if (image[x][y]==255){pp.push_back(coord);}

                    // Pop front pair of queue
                	Q.pop();
                    //MKXTSH013 :: ConnectedComponents ConnectedComponents(ID);
                    std::vector< std::pair<int,int> > pairss = {{}};
                    pairss.push_back(coord);
                    visited[x][y] = 0;

                	// For South Pixel
                	if (x+1 < rows && visited[x + 1][y] != 0 && image[x + 1][y] == 255){//>= threshold){
                        Q.push({x+1,y});
                	    visited[x + 1][y] = 0;
                	    std::pair<int,int> p = {x+1,y};
                	    pairss.push_back(p);
                	    pp.push_back(p);

                	}

                	// For North Pixel
                	if (x-1 >= 0 && visited[x - 1][y] != 0 && image[x - 1][y] == 255){//>= threshold){
                	    Q.push({ x - 1, y });
                	    visited[x - 1][y] = 0;
                	    std::pair<int,int> p = {x-1,y};
                	    pairss.push_back(p);
                	    pp.push_back(p);
                	}

                	// For East Pixel
                	if (y + 1 < columns && visited[x][y + 1] != 0 && image[x][y + 1] == 255){//>= threshold){
                        Q.push({ x, y + 1 });
                        visited[x][y + 1] = 0;
                	    std::pair<int,int> p = {x,y+1};
                	    pairss.push_back(p);
                	    pp.push_back(p);
                	}

                    // For West Pixel
                    if (y - 1 >= 0 && visited[x][y - 1] != 0 && image[x][y - 1] == 255){//>= threshold){
                        Q.push({ x, y - 1 });
                        visited[x][y - 1] = 0;
                	    std::pair<int,int> p = {x,y-1};
                	    pairss.push_back(p);
                	    pp.push_back(p);
                    }

                    int pix = pairss.size();
                	if (pix > 1 &&  pix >= minValidSize){
                	    ID++;
                        if (pix < minimum){minimum = pix;}
                        if (pix > maximum){maximum = pix;}
                        //pairss.push_back(coord); //add component at current position
                        component = std::make_shared<ConnectedComponents>(ID, pairss, pix);
                        component->AddBoundryPixel(coord);
                        //boundaryPixels.push_back(coord);
                        ///////////////////////////////////////////
                        Components.push_back(component);
                        comp++;
                	}
                }

                std::shared_ptr<ConnectedComponents> tt;// =
                int pi = pp.size();

                if (pi > 0 &&  pi >= 4000){//minValidSize){
                    IDD++;
                    tt=std::make_shared<ConnectedComponents>(IDD, pp, pi);
                    //std::cout<<IDD<<std::endl;
                    //std::cout << pi << std::endl;
                }

            }

        }
    }
    //std :: cout << IDD<<std::endl;// - comp<<std::endl;
    return comp;
}


void  PGMImageProcessor :: f(int threshold, unsigned char** image,int rows, int columns){
    visited = new unsigned char * [rows];
    for (int i = 0; i < rows; ++i){
        visited[i] = new unsigned char [columns];
        for (int j = 0; j < columns; ++j){
            if (image[i][j] >= threshold){
                image[i][j] = 255;
            }
            else{
                image[i][j] = 0;
            }
            visited[i][j] = 1;
        }
    }
}
/* iterate - with an iterator - though your container of connected
components and filter out (remove) all the components which do not
obey the size criteria pass as arguments. The number remaining
after this operation should be returned.
*/
int  PGMImageProcessor :: filterComponentsBySize(int minSize, int maxSize){
    int count =  component->getID();
    int sizee = Components.size();
    std::vector< std::shared_ptr<ConnectedComponents> > newComponents;
    for (int i = 0; i < sizee; i++){
        if (Components[i]->getNumOfPixels() >= minSize && Components[i]->getNumOfPixels() <= maxSize){
            newComponents.push_back(Components[i]);
        }
    }
    Components = std::move(newComponents);
    return Components.size();
}

/* create a new PGM file which contains all current components
(255=component pixel, 0 otherwise) and write this to outFileName as a
valid PGM. the return value indicates success of operation
*/
bool  PGMImageProcessor :: writeComponents(const std::string & outFileName){
    unsigned char** temp = new unsigned char * [rows];
    for (int k = 0; k < rows; ++k){
        temp[k] = new unsigned char [columns];
        for (int f = 0; f < columns; ++f){
            temp[k][f]=0;
        }
    }
    for (int i = 0; i < Components.size(); i++){
        int pix = Components[i]->getNumOfPixels();
        std::vector< std::pair<int,int> > pixs = Components[i]->getPixels();
        for (int j = 0; j < pix; j++){
            std::pair<int,int> p = pixs[j];
            int row = p.first;
            int col = p.second;
            temp[row][col] = 255;
        }
    }
    std::ofstream out(outFileName.c_str(), std::ios::out | std::ios::binary); //create and open file
    if(!out){
    	std::cout << "Could not open : " << outFileName << std::endl; // trace statement if file isn't open
        for(int i =0; i<rows; ++i){
            delete [] temp[i];
        }
        delete [] temp;
    	return false;
    }
    else if(out.is_open()){
        out << "P5\n" <<rows << " " << columns << "\n" << 255 << std::endl;
    	for (int d = 0; d < rows; ++d){
    	    for (int v = 0; v < columns; ++v){
    	        out << temp[d][v];
    	    }
    	}
    	/**for(int a=0; a<rows;++a){
    	out.write(reinterpret_cast<char*>(temp[a]), columns*rows);
        }**/
        out.close();
        for(int i =0; i<rows; ++i){
            delete [] temp[i];
        }
        delete [] temp;
    }

    return true;
}

// return number of components
int  PGMImageProcessor :: getComponentCount(void) const{
    return Components.size();
}

// return number of pixels in largest component
int PGMImageProcessor :: getLargestSize(void) const{
    return maximum;
}

// return number of pixels in smallest component
int  PGMImageProcessor :: getSmallestSize(void) const{
    return minimum;
}

/* print the data for a component to std::cout
see ConnectedComponents class;
print out to std::cout: component ID, number of pixels
*/
void  PGMImageProcessor :: printComponentData(const ConnectedComponents & theComponent) const{
    std::cout << "Component ID: " << theComponent.getID() << "  Number of pixels: " << theComponent.getNumOfPixels() <<"    Number of boundary pixels:    "<<theComponent.getNumOfBoundayPixels()<< std::endl;
}

void  PGMImageProcessor :: printAll(){
    //std::cout << "There are " << component_count << " components." << std::endl;
    for (int i = 0; i < Components.size(); ++i){
        //PGMimageProcessor::
        printComponentData(*(Components[i]));
    }
    std::cout << "smallest size: " << minimum<< std::endl;
    std::cout << "largest size: " << maximum << std::endl;
}

// write out outFileName in diffrent colours
bool  PGMImageProcessor :: ColouredComponents(const std::string &outFileName){

unsigned char*** temp = new unsigned char ** [rows]; //3D array
    for (int k = 0; k < rows; ++k){
        temp[k] = new unsigned char *[columns];
        for (int f = 0; f < columns; ++f){
            temp[k][f] = new unsigned char[3];
            for(int a =0 ; a< 3 ; ++a )
                temp[k][f][a]=0;
        }
    }
    unsigned char * color={}; //accessing the colours
    for (int i = 0; i < Components.size(); i++){
        int pix = Components[i]->getNumOfPixels();
        std::vector< std::pair<int,int> > pixs = Components[i]->getPixels();
        int random = rand()%5; // random numbers between 0 and 5
        color= colours[random]; // randomly selecting colours
        for (int j = 0; j < pix; j++){
            std::pair<int,int> p = pixs[j];
            int row = p.first;
            int col = p.second;
            //std::cout << row;
            temp[row][col] = color;
        }
    }
    //writing to file
    std::ofstream out(outFileName.c_str(), std::ios::out | std::ios::binary); //create and open file
    if(!out){ //new file can't be opened
    	std::cout << "Could not open " << outFileName << std::endl; // trace statement if file isn't open
        for(int i =0; i<rows; ++i){
            delete [] temp[i];
        }
        delete [] temp;
    	return false;
    }
    else if(out.is_open()){ //file opened
        out << "P5\n" <<rows * 3<< " " << columns<< "\n" << 255 << std::endl;
    	for (int d = 0; d < rows; ++d){
    	    for (int v = 0; v < columns; ++v){
    	        for(int w =0; w<3 ;++w ){
    	            out << temp[d][v][w];
    	        }

    	    }

    	}
        out.close();
        for(int i =0; i<rows; ++i){
            delete [] temp[i];
        }
        delete [] temp;

    }
    return true;
}

// define an appropriate comparison/ordering function so the component are ordered from smallest to largest by size
bool  PGMImageProcessor :: compareComponents (const ConnectedComponents & lhs,
const ConnectedComponents & rhs)
{
return true;
// return true if lhs < rhs (based on size );
}
}