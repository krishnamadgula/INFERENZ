
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
vector <string> ColumnNames;

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


        void plot_relationship_values(vector<vector<string> > dataBlock,int colx,int coly)
        {
            int j=0;
            vector<float> floatValues;

            for(j=0;j<dataBlock[coly].size();++j)
            {
                // floatValues[j].push_back(j+1);
                floatValues.push_back(atof(dataBlock[colx][j].c_str()));
                yValues_relationship.push_back(floatValues[j]);

            }

            floatValues.clear();
            for(j=0;j<dataBlock[colx].size();++j)
            {
                // floatValues[j].push_back(j+1);
                floatValues.push_back(atof(dataBlock[coly][j].c_str()));
                xValues_relationship.push_back(floatValues[j]);

            }
            vector<float> sortedXvalues(xValues_relationship);
            vector<float> sortedYvalues(yValues_relationship);
            sort(sortedXvalues.begin(),sortedXvalues.end());
            sort(sortedYvalues.begin(),sortedYvalues.end());
            for (j=0;j<dataBlock[colx].size();++j){
                xValues_relationship[j]=xValues_relationship[j]/sortedXvalues[sortedXvalues.size()-1];
                yValues_relationship[j]=yValues_relationship[j]/sortedYvalues[sortedYvalues.size()-1];

            }


        }

        vector<float> yValues;
        vector<float> xValues;
        vector<float> yValues_relationship;
        vector<float> xValues_relationship;

};

class BoxPlot{

    public:
        void plot_values(vector <vector<string> > dataBlock,vector<int> col)
        {
            int i=0,j=0;
            int k=0;
            columnsForBoxPLot=col;
            vector<float> floatValues;
            for(k=0;k<col.size();++k){
                floatValues.clear();


                for(j=0;j<dataBlock[col[k]].size();++j)
                {

                    floatValues.push_back(atof(dataBlock[col[k]][j].c_str()));


                }

                sort(floatValues.begin(),floatValues.end());


                for(i=0;i<floatValues.size();++i){
                    floatValues[i]=floatValues[i]/ (floatValues[floatValues.size()-1]);
                }
                float sum=0;
                for(i=0;i<floatValues.size();++i){
                    sum+=floatValues[i];
//                    cout<<floatValues[i]<<endl;

                }

                average_value.push_back(sum/(floatValues.size()));
                min_value.push_back(floatValues[0]);
                firstQuartile.push_back(floatValues[(floatValues.size()/4)-1]);
                thirdQuartile.push_back( floatValues[((floatValues.size()/4)*3)-1]);

    //            cout<<min_value<<endl;
                max_value.push_back(floatValues[floatValues.size()-1]);
                yValues.push_back(floatValues);

            }

        }
        vector<vector<float> > yValues;
        vector<float >average_value;
        vector<float >min_value,max_value;
        vector<float >firstQuartile,thirdQuartile;
        vector<int>columnsForBoxPLot;



//        vector<float> xValues;


};


ScatterPlot sp;
BoxPlot bp;


void ScatterPlotDisplay(){
//    cout<<"enter arguments for scatter plot"<<endl<<"1:RelationShip Plot"<<"2:Continuity Plot";
	char*sc_args="1";
//	cin>>sc_args;
    glClear(GL_COLOR_BUFFER_BIT);

    int i=0;
    glPointSize(2);
    if(strcmp(sc_args,"1")==0){
        glBegin(GL_POINTS);
        for (i=0;i<sp.yValues_relationship.size();i++){
//            cout<<(sp.xValues_relationship[i])*500<<(sp.yValues_relationship[i])*500;

            GLfloat x1=((sp.xValues_relationship[i])*300)+50;
            GLfloat y1=((sp.yValues_relationship[i])*300)+50;
            glVertex2f(x1,y1);
            glColor3f(0,0,1);

        }
        glEnd();
        glFlush();

    }
    else{

        glBegin(GL_POINTS);
        for (i=0;i<sp.yValues.size();i++){
            GLfloat x=(sp.xValues[i]);
            GLfloat y=(sp.yValues[i])*500;
    //        cout<<y<<endl;
            glVertex2f(x,y);
            glColor3f(1,0,0);
        }

        glEnd();
        glFlush();
    }
}

void BoxPlotDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    int cols=0;
    GLfloat xmin=10;
    GLfloat xmax=15;
    int offset=(500/(bp.yValues.size()*3));
    for (cols=0;cols<bp.yValues.size();cols++){
    //    int i=0;
        cout <<bp.firstQuartile[cols]<<"is ymin"<<bp.thirdQuartile[cols]<<"is ymax";
        GLfloat ymin=(bp.min_value[cols]*100)+100;
        GLfloat ymax=(bp.max_value[cols]*100)+100;
        xmin=xmax+offset;
        xmax=xmin+offset;
        GLfloat ythird=(bp.thirdQuartile[cols]*100)+100;
        GLfloat yfirst=(bp.firstQuartile[cols]*100)+100;

//        cout<<ymin<<" "<<ymax;
        GLfloat yavg=(bp.average_value[cols]*100)+100;
    //    char*i=ColumnNames[2];
        char i;
        int m=0;
        glRasterPos2i((xmin),0);
        glColor3f(1,0,1);

        for (i=0;m!=strlen(ColumnNames[bp.columnsForBoxPLot[cols]].c_str());++m)
        {
            cout<<ColumnNames[bp.columnsForBoxPLot[cols]][m];
            //COLUMN NAMES PLOTTING
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,ColumnNames[bp.columnsForBoxPLot[cols]][m]);
        }
    //    char str_col[]=ColumnNames[3].c_str();

        // char *a2=ColumnNames[3].c_str();
    //    for (i=str_col;*i!='\0';i++)
    //    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,(i));
        glColor3f(1,0,1);

        glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,yfirst);
        glVertex2f(xmin,ythird);
        glVertex2f(xmax,ythird);
        glVertex2f(xmax,yfirst);
        glEnd();

        glColor3f(1,0,1);
        glBegin(GL_LINES);
        glVertex2f(xmin,yavg);
        glVertex2f(xmax,yavg);

        glEnd();
        glColor3f(1,0,0);
        glBegin(GL_LINES);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glEnd();

        glColor3f(1,0,0);
        glBegin(GL_LINES);
        glVertex2f(xmin,ymax);
        glVertex2f(xmax,ymax);
        glEnd();


    }
    glFlush();


}

void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,500.0,0.0,300.0);
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
	string cell;
	istringstream lineStream(row_data);
	while(getline(lineStream,cell,',')){
        ColumnNames.push_back(cell);
	}
	cout<<row_data;
	int count=0;
	int ColumnCount=0;
	cin>>ColumnCount;
	vector<string> column;
	vector<int> c;
	c.push_back(0);
	c.push_back(3);
    dataBlock=rows.readRows(fin,ColumnCount);

//    sp.plot_values(dataBlock,3);
//    sp.plot_relationship_values(dataBlock,6,7);
    bp.plot_values(dataBlock,c);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
	glutCreateWindow("INFERENZ");
//    glutDisplayFunc(ScatterPlotDisplay);
    glutDisplayFunc(BoxPlotDisplay);


    myinit();
    glutMainLoop();
    return 0;




}




//FRONT PAGE
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
