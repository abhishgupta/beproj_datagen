#pragma warning (disable : 4786)
#pragma warning (disable : 4305)
#pragma warning (disable : 4309)
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<utility>

using namespace std;

struct column

{
	string name;
	string type;
	string format;

};



int readconfig() // function to parse the the text file config.txt
{
	int pos=0,len=0,i,j,pos1,pos2,index,arg=1,NoOfRecords=10,count=0;;
	char buf[100],temp[100];
	string line;
	

	fstream fs;
	ofstream fp;
	ofstream ff;

	vector<column> v_col;
	

    fs.open ("f:\\student.cfg", fstream::in | fstream::out | fstream::app);
	fp.open ("f:\\output.txt");

	while(!fs.eof())
	{
		column clm;
		fs.getline(buf,100);  // reading one line from config.txt
		line=buf;
		pos=line.find('=>',0);   // find '=>' in the line so as to retrieve the data next to '=>'
		

		for(i=0;i<pos-1;i++)
		{
			temp[i]=buf[i];
		}
		temp[i]='\0';

		clm.name=temp;

		fp<<temp;
		fp<<",";

		pos1=line.find('=',pos);
		pos2=line.find(';',pos1);



		for(i=pos1+1,j=0;i<pos2;i++,j++)
		{
			temp[j]=buf[i];
		}

		temp[j]='\0';

		

		clm.type=temp;

		fp<<temp;
		fp<<",";

		pos1=line.find('=',pos2);
		
		i=pos1+1;
		j=0;
		pos=strlen(buf);
		while(i<pos)
		{
			temp[j]=buf[i];
			j++;
			i++;
		}
		temp[j]='\0';


		clm.format=temp;

		fp<<temp;
		fp<<endl;

		
		
		v_col.push_back(clm); 		
		   	
		
	}

	


	fs.close();
	fp.close();


    int startlimit,endlimit,posi,k,col_index=1,val1,val2;
	std::map<int,std::vector<std::string> > m_record;
	std::map<int,std::vector<std::string> > ::iterator itr;
	//std::vector<std::string> ::iterator it;
	std::vector<std::string> col1;
	std::vector<std::string> col2;

	for (index=0; index<v_col.size();index++)
	{

		cout<<v_col[index].name;
		cout<<endl;
		cout<<v_col[index].type;
		cout<<endl;
		cout<<v_col[index].format;
		cout<<endl;
	
		
		posi=v_col[index].format.find("incremental");
		
                if(posi!=-1)

                {
					startlimit=v_col[index].format.find("(",posi);
					endlimit=v_col[index].format.find(")",startlimit);

					

					//find the argument passed to the function, ie value in parenthesis
				
					count=0;
					k=0;
										    
					int val=atoi(v_col[index].format.substr(startlimit+1,endlimit-startlimit).c_str());//convert integer into string  c_str:converts string into character array
					                 
                                while(count<NoOfRecords)
                                {
									k=k+val;
									itoa(k,temp,10);
									col1.push_back(temp);
									count++;
								}

								m_record.insert(make_pair(col_index,col1));
								cout<<"\nMAP VALUES::";

								
								 
								
						
				}
				

			    else 
					//if(posi=v_col[index].format.find("randomstring"))

                {
					//find the argument passed to the function, ie value in parenthesis 
					posi=v_col[index].format.find("randomstring");
					startlimit=v_col[index].format.find("(",posi);
					pos1 = v_col[index].format.find(",",startlimit);
					val1 = atoi(v_col[index].format.substr(startlimit+1,pos1-startlimit).c_str());
					pos2 = v_col[index].format.find(")",pos1);
					val2 = atoi(v_col[index].format.substr(pos1+1,pos2).c_str());


				
					string alphanum =
						"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
					
					for(count=0;count<NoOfRecords;count++)
					{
						int len = 0;
						if(val2>val1)
							len = (rand()%(val2-val1))+val1;
						else
							len =val1;
						int index = rand()%(alphanum.size() - len);
						
						col2.push_back(alphanum.substr(index,len));
					}

					
					col_index=2;
					m_record.insert(make_pair(col_index,col2));

				}


				
			}



ff.open ("f:\\op.txt");

for(col_index=1,itr=m_record.begin();itr!=m_record.end();itr++,col_index++)
{
	std::vector<std::string> col = m_record[col_index];
    std::vector<std::string>::iterator it= col.begin();
	for (it=col.begin();it!=col.end();it++)
	{
		std::string str = (*it);
		std::cout<<"value="<<str<<endl;
		ff<<str<<endl;
	}
}





ff.close(); 

    return true;
}




void main()
{
	//parser
	readconfig();
	
}

