
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <sstream>
//#include <GL/glut.h>


// #include <cstdio>
// struct rows
// struct dataBlock{
// 	vector
// };
using namespace std;
// vector <vector<string> > dataBlock;

class CSV_Row_Data{
	public:

		vector <vector<string> > readRows(std::istream& str,int ColumnCount)
	        {
	            std::string line;
	            // std::getline(str, line);
	            int count=0;

	            // std::istringstream   lineStream ((string) line);
	            std::string         cell;
	            vector<string> column;
		    	vector<float>::size_type i;

	            dataBlock.clear();

	            for(i=0;i<ColumnCount;++i){
					vector<string> column;
					dataBlock.push_back(column);

				}



		    	// string field;
			    while(getline(str,line))
			    {
			    	count=0;
			    	istringstream lineStream(line);
			    	while(getline(lineStream,cell,',')){
			    		dataBlock[count].push_back(cell);
			       		count=(count+1)%ColumnCount;
			       		cout<<count;
			    	}

			    	// vector<float>::size_type i;




		            // while(std::getline(lineStream, cell, ','))
		            // {
		            //     dataBlock.push_back(cell);
		            // }
		            // This checks for a trailing comma with no data after it.
		            cout<<"here1";
		            if (!lineStream && cell.empty())
		            {
		                // If there was a trailing comma then add an empty element.

		                dataBlock[count].push_back("");
		                count=(count+1)%ColumnCount;
		            }
		            cout<<"here2";

		        }
		        return dataBlock;
	        }


        vector <vector<string> > dataBlock;
};

// int main(){
//  	char name[255];
//  	int i,j,k,l;
// 	cout<<"enter the name of the csv file";
// 	gets (name);
// 	ifstream fin(name);
//     if (!fin)
//     {
//         cout << "File not open\n";
//         return 1;
//     }
//     vector<string> row_data_vec;
//     vector <vector<string> > dataBlock;
//     string row_data;
//     std::string delimiter = ",";
// 	size_t pos=0;
// 	string token;
// 	float token_float;
// 	CSV_Row_Data rows;

// 	cout<<"specify no of columns";

// 	getline(fin,row_data);
// 	cout<<row_data;
// 	int count=0;
// 	int ColumnCount=0;
// 	cin>>ColumnCount;
// 	vector<string> column;

// 	// for(i=0;i<ColumnCount;++i){

// 	// 	dataBlock.push_back(column);

// 	// }





//     // while(getline(fin,row_data))
//     // {
//     // 	count=0;
//     // 	istringstream s(row_data);
//     // 	string field;

//     // 	while(getline(s,field,',')){
//     // 		dataBlock[count].push_back(field);
//     //    		count=(count+1)%ColumnCount;
//     // 	}



//     // }
//     // vector<float>::size_type i;
//     dataBlock=rows.readRows(fin,ColumnCount);
//     	cout<<"hi";

//     // for (i=0;i<ColumnCount;++i){
// 	for (j=0;j<dataBlock[2].size();j++){
// 		cout<<dataBlock[2][j]<<"-";
// 	}cout<<endl;
// 	// }

// }
