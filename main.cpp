
#include "createVectors.h"


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <sstream>
#include<algorithm>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
//#include<windows.h>
#include <GL/glut.h>
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

using namespace std;

class ScatterPlot{

    public:
        void plot_values(vector <vector<string> > dataBlock,int col)
        {
            int i=0,j=0;
//            vector <vector<float> > floatValues;
//            vector<float> value_row;
            vector<float> floatValues;

            // for (i=0;i<dataBlock[col].size();i++)
            //     floatValues.push_back(value_row);

//            flag[i]=0;
            for(j=0;j<dataBlock[col].size();++j)
            {
                // floatValues[j].push_back(j+1);
                floatValues.push_back(atof(dataBlock[col][j].c_str()));
                yValues.push_back(floatValues[j]);

            }
            // yValues=floatValues;
            sort(yValues.begin(),yValues.end());

            for(i=0;i<yValues.size();++i){
                xValues.push_back(i+1);

            }
//            cout<<"HI HERE"<<yValues[yValues.size()-1]<<endl;
            for(i=0;i<yValues.size();++i){
                yValues[i]=yValues[i]/ (yValues[yValues.size()-1]);
            }

             for(j=0;j<floatValues.size();++j){
                 cout<<yValues[j]<<endl;
             }








        }
        vector<float> yValues;
        vector<float> xValues;


};
ScatterPlot sp;

void ScatterPlotDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    int i=0;
    for (i=0;i<sp.yValues.size();i++){
            GLfloat x=(sp.xValues[i]);
            cout<<"this is x"<<x;
            GLfloat y=(sp.yValues[i])*100;
        glVertex2f(x,y);
        glColor3f(1,0,0);
    }

    glEnd();
    glFlush();

}
void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}

int main(int argc ,char**argv){
 	char name[255];
 	int i,j,k,l;
	cout<<"enter the name of the csv file";
	gets (name);
	ifstream fin(name);
    if (!fin)
    {
        cout << "File not open\n";
        return -1;
    }
    vector<string> row_data_vec;
    vector <vector<string> > dataBlock;
    string row_data;
    std::string delimiter = ",";
	size_t pos=0;
	string token;
	float token_float;
	CSV_Row_Data rows;

	cout<<"specify no of columns";

	getline(fin,row_data);
	cout<<row_data;
	int count=0;
	int ColumnCount=0;
	cin>>ColumnCount;
	vector<string> column;

	// for(i=0;i<ColumnCount;++i){
	// 	dataBlock.push_back(column);
	// }
    // while(getline(fin,row_data))
    // {
    // 	count=0;
    // 	istringstream s(row_data);
    // 	string field;
    // 	while(getline(s,field,',')){
    // 		dataBlock[count].push_back(field);
    //    		count=(count+1)%ColumnCount;
    // 	}
    // }
    // vector<float>::size_type i;

    	cout<<"hi";
    	dataBlock=rows.readRows(fin,ColumnCount);

    // for (i=0;i<ColumnCount;++i){
	for (j=0;j<dataBlock[2].size();j++){
		cout<<dataBlock[2][j]<<"-";
	}cout<<endl;
	// }

    sp.plot_values(dataBlock,2);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
	glutCreateWindow("INFERENZ");
    glutDisplayFunc(ScatterPlotDisplay);
    myinit();
    glutMainLoop();
    return 0;


//	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
//	glutInitWindowSize(500,500);
//	glutCreateWindow("INFERENZ");
////	glutReshapeFunc(myReshape);
//
//	glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0,100,0,100);
//    glMatrixMode(GL_MODELVIEW);
//    glClearColor(0.0f,0.0f,0.0f,0.0f);
//    glutDisplayFunc(ScatterPlotDisplay);
////	glutMouseFunc(mouse);
////	glutKeyboardFunc(keys);
//	glEnable(GL_DEPTH_TEST);
//	glutMainLoop();

}
