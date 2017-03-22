
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
#include<windows.h>
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

//             for(j=0;j<floatValues.size();++j){
//                 cout<<yValues[j]<<endl;
//             }








        }
        vector<float> yValues;
        vector<float> xValues;


};

class BoxPlot{

    public:
        void plot_values(vector <vector<string> > dataBlock,int col)
        {
            int i=0,j=0;

            vector<float> floatValues;

            for(j=0;j<dataBlock[col].size();++j)
            {

                floatValues.push_back(atof(dataBlock[col][j].c_str()));
                yValues.push_back(floatValues[j]);

            }

            sort(yValues.begin(),yValues.end());


            for(i=0;i<yValues.size();++i){
                yValues[i]=yValues[i]/ (yValues[yValues.size()-1]);
            }
            float sum=0;
            for(i=0;i<yValues.size();++i){
                sum+=yValues[i];

            }
            average_value=sum/(yValues.size());
            min_value =yValues[0];
            max_value=yValues[yValues.size()-1];


//             for(j=0;j<floatValues.size();++j){
//                 cout<<yValues[j]<<endl;
//             }








        }
        vector<float> yValues;
        float average_value;
        float min_value,max_value;

//        vector<float> xValues;


};


ScatterPlot sp;
BoxPlot bp;


void ScatterPlotDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    int i=0;
    for (i=0;i<sp.yValues.size();i++){
        GLfloat x=(sp.xValues[i]);
        GLfloat y=(sp.yValues[i])*100;
//        cout<<y<<endl;
        glVertex2f(x,y);
        glColor3f(1,0,0);
    }

    glEnd();
    glFlush();

}

void BoxPlotDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);

    int i=0;
    GLfloat ymax=bp.max_value*100;
    GLfloat ymin=bp.min_value*100;
    GLfloat yavg=bp.average_value*100;
    glBegin(GL_POLYGON);
    GLfloat xmin=10;
    GLfloat xmax=30;
    glColor3f(1,0,1);
    glVertex2f(xmin,ymin);
    glVertex2f(xmin,ymax);
    glVertex2f(xmax,ymax);
    glVertex2f(xmax,ymin);
    glEnd();
    glBegin(GL_LINE);
    glVertex2f(xmin,yavg);
    glVertex2f(xmax,yavg);
    glEnd();
    glFlush();





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
    gluOrtho2D(0.0,499.0,0.0,100.0);
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

//    	cout<<"hi";
    	dataBlock=rows.readRows(fin,ColumnCount);

    // for (i=0;i<ColumnCount;++i){
//	for (j=0;j<dataBlock[2].size();j++){
//		cout<<dataBlock[2][j]<<"-";
//	}cout<<endl;
	// }

    sp.plot_values(dataBlock,3);
    bp.plot_values(dataBlock,3);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(250,250);
    glutInitWindowPosition(0,0);
	glutCreateWindow("INFERENZ");
//    glutDisplayFunc(ScatterPlotDisplay);
    glutDisplayFunc(BoxPlotDisplay);


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





//#include <GL/glut.h>
//#include<string.h>
////#include<GL/freeglut.h>
//
//void init2D(float r,float g,float b)
//{
// glClearColor(r,g,b,0.0);
// glMatrixMode(GL_PROJECTION);
// gluOrtho2D(0.0,600.0,0.0,600.0);
//}
//void text()
//{
//
// glColor3f(0,.5,.5);
// glMatrixMode(GL_PROJECTION);
// glPushMatrix();
// glLoadIdentity();
// gluOrtho2D(0,600,0,600);
// glMatrixMode(GL_MODELVIEW);
// glPushMatrix();
// glLoadIdentity();
// char* i;
//
// glRasterPos2i(230,500);
// char *a="CG PROJECT";
// for (i=a;(*i)!='\0';i++)
// glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,(*i));
//
//// glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*));
//
// glRasterPos2i(230,450);
//
// glColor3f(0.0,0.0,1.0);
// char a1[]="TITLE :  INFERENZ";
// for (i=a1;*i!='\0';i++)
// glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(*i));
//
// glRasterPos2i(450,120);
// char a2[]="M. NITHYA LAXMI";
// for (i=a2;*i!='\0';i++)
// glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,(*i));
//
//// glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"M. NITHYA LAXMI");
//
// glRasterPos2i(450,90);
// char a3[]="1PE14CS066";
// for (i=a3;*i!='\0';i++)
// glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,(*i));
//// glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"1PE14CS066");
//
// glRasterPos2i(450,60);
// char a4[]="MADGULA KRISHNA CHAITANYA";
// for (i=a4;*i!='\0';i++)
// glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,(*i));
//// glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"MADGULA KRISHNA CHAITANYA");
//
// glRasterPos2i(450,30);
// char a5[]="1PE14CS067";
// for (i=a5;*i!='\0';i++)
// glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,(*i));
//// glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"1PE14CS067");
//
// glPopMatrix();
// glMatrixMode(GL_PROJECTION);
// glPopMatrix();
// glMatrixMode(GL_MODELVIEW);
//}
//void display()
//{
// glClear(GL_COLOR_BUFFER_BIT);
// glColor3f(0.0,0.0,0.0);
// text();
// glFlush();
//}
//int main(int argc,char** argv)
//{
// glutInit(&argc,argv);
// glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
// glutInitWindowPosition(0,0);
// glutInitWindowSize(1000,1000);
// glutCreateWindow("CG Mini Project");
// glutDisplayFunc(display);
// init2D(1.0,1.0,1.0);
// glutMainLoop();
// return 0;
//}
////main.cpp
////Open with Drive Notepad
////Displaying main.cpp.
//
//
//
//
//
//
