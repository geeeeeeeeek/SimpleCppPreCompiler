#include <string>
#include <vector>
class BaseModel
{
public:
	int type;
	int TYPE_STMT, TYPE_BLOCK, TYPE_MACRO;
	std::string content;
	std::vector<BaseModel> ctx_vec;
	BaseModel()
	{
		TYPE_STMT = 0;
		TYPE_BLOCK = 1;
		TYPE_MACRO = 2;
	}
};

/*Statement*/
class Stmt :public BaseModel
{
public:


	Stmt(std::string s)
	{
		type = BaseModel().TYPE_STMT;
		content = s;
	}
};

/*Block*/
class Block: public BaseModel
{
public:
	

	Block(std::string s)
	{
		type = BaseModel().TYPE_BLOCK;
		content = s;
	}
};

/*Macro*/
class Macro:public BaseModel
{
public:
	Macro(std::string s)
	{
		type = BaseModel().TYPE_MACRO;
		content = s;
	}
};