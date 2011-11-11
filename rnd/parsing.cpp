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



string getrandomstring(const int l1, const int l2)
 {
    string temp;
	char s[50];

	static const char alphanum[] =
        //"0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < l2-l1; ++i) 
	{
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[i] = 0;
	temp=s;

	//cout<<temp;

	return temp;
}






int readconfig() // function to parse the the text file onfig.txt
{
	int pos=0,len=0,i,j,pos1,pos2,index,arg=1,NoOfRecords=2,count=0;;
	char buf[100],temp[100];
	string line;
	

	fstream fs;
	ofstream fp;
	ofstream ff;

	vector<column> v_col;
	//std::map<int, vector<string>> m_record;
	//std::map<int,vector<column>> m_record;
	//map <string, vector<int> > myMapOfVec;
	map <int, vector<string> > m_record;
	map <int, vector<string> >::iterator m_it;
	//typedef pair <int, vector<string> > m_pair;
	

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

	//cout<<m_record;


	fs.close();
	fp.close();


    int startlimit=15,endlimit=20;
	for (index=0; index<v_col.size();index++)
	{

                if(v_col[index].format.find("incremental"))

                {
					//find the argument passed to the function, ie value in parenthesis
					count=0;
					while(count<NoOfRecords)
					{
						itoa(arg,temp,10);//convert integer into string

						line=temp;
						//m_record[index].insert(line);
						
						m_record[index].insert(m_pair (count,temp));
						//m_record[index].insert(<int,string>(1,'a'));

						cout<<"\nVal of arg :"<<temp;

						arg++;//argument passed in incremental() function			
						count++;
					}
				}

				if(v_col[index].format.find("randomstring"))

                {
					//find the argument passed to the function, ie value in parenthesis                             


					count=0;
					while(count<NoOfRecords)
					{
						line=getrandomstring(startlimit,endlimit);//convert integer into string


						cout<<endl;

						cout<<line<<"\n";

				

						m_record[count].push_back(temp);                                           							
						count++;
					}
				}
	}




count=0;
string record="";
ff.open ("f:\\op.txt");




while(count<NoOfRecords)
{
	
		
	for(m_it=m_record.begin(); m_it!= m_record.end();m_it++)
	{
		//if(record!="")

		record="";
		
			//record.append(m_record[m_it].vector<string>);

			//cout<< (*m_it).second<<endl;

			//cout << (*m_it).first << "== " << (*m_it).second << endl;

			//ff<<(*m_it).first<<"== "<<(*m_it).second<<endl;

			record.append((m_it->second)[count]);//get the value from the vector
			record.append(",");      //column seperator
			cout<<record;
			ff<<record;

			
		
		count++;
		
		
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

