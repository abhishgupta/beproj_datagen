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

int getIncrementalValue(const int& _val,std::vector<std::string>& _colData)
{
 int count=0;
 std::string str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZA1B2C3D4R5F7G8H9I10";
 std::stringstream ss;
 srand(str.size());
 for(;count < NO_OF_RECORDS;count++)
 {
   int index = rand()%(str.size() - _val);
   _colData.push_back(str.substr(index,_val));

 }

 return SUCCESS;
}

int getRandomValue(const int& _start,const int& _end,std::vector<std::string>& _colData)
{
 



 return SUCCESS;
}

int generateColValues(const std::vector<struc_tabColumn>& _vecAllColsInfo, std::map<int,std::vector<std::string> >& mapColValues)
{
  size_t pos_type = std::string::npos;
  std::vector<struc_tabColumn>::const_iterator itr = _vecAllColsInfo.begin();

  for(;itr != _vecAllColsInfo.end();itr++)
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

    }
    else if(std::string::npos != (pos_type = _cols.sFormat.find(std::string("randomstring"))))
    {
      size_t next_pos_1 = _cols.sFormat.find("(",pos_type);
      size_t next_pos_2 = _cols.sFormat.find(",",next_pos_1);
      int inc_val1 = atoi(_cols.sFormat.substr(next_pos_1+1,next_pos_2 - next_pos_1-1).c_str());

      next_pos_1 = _cols.sFormat.find(")",next_pos_2);
      int inc_val2 = atoi(_cols.sFormat.substr(next_pos_2+1,next_pos_1 - next_pos_2-1).c_str());

      std::cout<<"randomstring found val1="<<inc_val1<<",val2="<<inc_val2<<std::endl;

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
       //std::cout<<"line:"<<_line.c_str()<<std::endl;
       parse_line(_line,_cols);

       vecAllColsInfo.push_back(_cols);

   }
 }

 generateColValues(vecAllColsInfo,mapColValues);

 return 0;
}

