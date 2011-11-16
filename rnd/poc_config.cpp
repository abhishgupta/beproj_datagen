#include<iostream>
#include<map>
#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include <sstream>

enum ENUM_FORMAT{
 eINCREMENTAL,
 eRANDOMSTRING
};

struct struc_tabColumn{
 std::string sName;
 std::string sType;
 std::string sFormat;
};

const int ERR_FORMAT_ERROR = 201001;
const int ERR_INVALID_FORMAT = 201002;
const int SUCCESS = 0;
const int FAILURE = -1;
const int NO_OF_RECORDS=10;

int parse_line(std::string &_line,struc_tabColumn &_cols)
{
  std::string temp;

  size_t pos_name=0;
  int last_index = 0;

  std::string::iterator itr = _line.begin();
  for(int i=0; itr !=  _line.end(); itr++,i++)
  {
    if((*itr) == '=' && *(itr+1) == '>')
    {
      pos_name = i;
      _cols.sName = _line.substr(last_index,i-last_index);
      //std::cout<<"val="<<_cols.sName<<",pos="<<last_index<<",len="<<i-last_index<<std::endl;
      last_index = i+2;
    }
    if((*itr) == '=')
    {
      if(_line.substr(i-4,4) == std::string("type"))
      {
        size_t pos_type = _line.find(';',i);
        if(pos_type != std::string::npos)
        {
           _cols.sType =  _line.substr(i+1,pos_type-i-1);

        } 

      }
      else if(i > 6 && _line.substr(i-6,6) == std::string("format"))
      {
        _cols.sFormat =  _line.substr(i+1);
      }

    }
    else continue;
  }

  return SUCCESS;
}

void print_col_info(const std::vector<struc_tabColumn>& _vecAllColsInfo)
{
  std::vector<struc_tabColumn>::const_iterator itr = _vecAllColsInfo.begin();

  for(;itr != _vecAllColsInfo.end();itr++)
  {
    struc_tabColumn _cols = (*itr);
    std::cout<<"name="<<_cols.sName<<",type="<<_cols.sType<<",format="<<_cols.sFormat<<std::endl; 
  }
}

std::vector<std::string> getIncrementalValue(const int& _val=0,const int& _diff=1)
{
 int count=0;
 std::vector<std::string> _colData;
 std::stringstream ss;
 int int_val = _val;
 for(;count < NO_OF_RECORDS;count++)
 {
  int_val += _diff; 
  ss<<int_val;
  _colData.push_back(ss.str());
 }

 return _colData;
}

std::vector<std::string> getRandomValue(const int& _start,const int& _end)
{
 int count=0;
 std::string str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZA1B2C3D4R5F7G8H9I10";
 std::stringstream ss;
 srand(str.size());
 std::vector<std::string> _colData;

 for(;count < NO_OF_RECORDS;count++)
 {
   int len = 0;

   if(_end > _start)
       len = (rand()%(_end - _start))+_start;
   else
       len = _start;
   int index = rand()%(str.size() - len);
   _colData.push_back(str.substr(index,len));

 }

 return _colData;
}

int generateColValues(const std::vector<struc_tabColumn>& _vecAllColsInfo, std::map<int,std::vector<std::string> >& mapColValues)
{
  size_t pos_type = std::string::npos;
  std::vector<struc_tabColumn>::const_iterator itr = _vecAllColsInfo.begin();

  for(int col_index=1;itr != _vecAllColsInfo.end();itr++,col_index++)
  {
    struc_tabColumn _cols = (*itr);
    std::cout<<"name="<<_cols.sName<<",type="<<_cols.sType<<",format="<<_cols.sFormat<<std::endl; 

    
    pos_type = _cols.sFormat.find(std::string("incremental"));
    if(pos_type != std::string::npos)
    {
      size_t next_pos_1 = _cols.sFormat.find("(",pos_type);
      size_t next_pos_2 = _cols.sFormat.find(")",next_pos_1);
      int inc_val = atoi(_cols.sFormat.substr(next_pos_1+1,next_pos_2 - next_pos_1-1).c_str());

      std::cout<<"incremental found="<<inc_val<<std::endl;
      mapColValues.insert(make_pair(col_index,getIncrementalValue(0,inc_val)));

    }
    else if(std::string::npos != (pos_type = _cols.sFormat.find(std::string("randomstring"))))
    {
      size_t next_pos_1 = _cols.sFormat.find("(",pos_type);
      size_t next_pos_2 = _cols.sFormat.find(",",next_pos_1);
      int inc_val1 = atoi(_cols.sFormat.substr(next_pos_1+1,next_pos_2 - next_pos_1-1).c_str());

      next_pos_1 = _cols.sFormat.find(")",next_pos_2);
      int inc_val2 = atoi(_cols.sFormat.substr(next_pos_2+1,next_pos_1 - next_pos_2-1).c_str());

      std::cout<<"randomstring found val1="<<inc_val1<<",val2="<<inc_val2<<std::endl;
      mapColValues.insert(make_pair(col_index,getRandomValue(inc_val1,inc_val2)));

    }
    else
    {
     //no matches found
      std::cout<<"format error \n";

     return ERR_FORMAT_ERROR;

    }

   
  }
 return SUCCESS;
}

int print_values(std::vector<struc_tabColumn> _vecAllColsInfo,std::map<int,std::vector<std::string> > _mapColValues)
{
  size_t pos_type = std::string::npos;
  std::vector<struc_tabColumn>::iterator itr = _vecAllColsInfo.begin();
  for(int col_index=1;itr != _vecAllColsInfo.end();itr++,col_index++)
  {
    struc_tabColumn _cols = (*itr);
    std::cout<<"name="<<_cols.sName<<",type="<<_cols.sType<<",format="<<_cols.sFormat<<std::endl; 

    //std::map<int,std::vector<std::string> >::iterator itr;
    std::vector<std::string>  col_values = _mapColValues[col_index];
    std::vector<std::string>::iterator itr2 = col_values.begin();
    for(;itr2 != col_values.end();itr2++)
    {
     std::string str = (*itr2); 
     std::cout<<"value="<<str<<std::endl;
    }

  }


 return SUCCESS;
}

int main()
{
 std::ifstream _cfgFile;
 std::string _line;
 struc_tabColumn _cols;
 std::vector<struc_tabColumn> vecAllColsInfo;
 std::map<int,std::vector<std::string> > mapColValues;

 _cfgFile.open("./std.cfg");
 if(_cfgFile.is_open())
 {
   while(!_cfgFile.eof()){
       getline(_cfgFile,_line);
       parse_line(_line,_cols);
       vecAllColsInfo.push_back(_cols);
   }
 }

 generateColValues(vecAllColsInfo,mapColValues);
 print_values(vecAllColsInfo,mapColValues);

 return 0;
}

