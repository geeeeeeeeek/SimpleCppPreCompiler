#include <string>
#include <map>
//#include "model.h"
//#include "model.h"

static std::vector<Macro> macros;
static std::map<std::string, std::string> def_trans_map;
class macrop
{
public:
	

	std::string process(std::string context)
	{
		//process def
		std::map<std::string, std::string>::iterator it;
		for (it=def_trans_map.begin(); it!=def_trans_map.end(); ++it)
		{
			int pos = context.find(it->first);
			if(pos!=-1)
			{
				int len = it->first.length();

				//if has param
				int left = context.find("(");
				int right = context.find(")");
				if (left!=-1 && right!=-1)
				{
					std::string expr = it->second;
					std::string arg=context.substr(left+1,right-left-1);
					expr.replace(expr.find("arg"),3,arg);
					context.replace(pos,right-pos+1,expr);
				}
				else
				{
					left = context.find("\"");
					right = context.find("\"",left+1);
					if (left==-1 || pos<left || pos>right)
					{
						context.replace(pos,len,it->second);
					}
					
				}
				
			}
		}

		
		return context;
	}

	void add_macro(std::string key, std::string value)
	{
		std::map<std::string, std::string>::iterator it = def_trans_map.find(value);

		if (it!=def_trans_map.end())
			value = it->second;
		def_trans_map.insert(std::pair<std::string, std::string>(key,value));
	}

private:

};