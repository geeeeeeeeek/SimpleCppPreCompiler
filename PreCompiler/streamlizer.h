#include <string>
#include <vector>
//#include "model.h"

static std::string spacing;
class streamlizer
{
	
public:
	std::string straemlize(std::vector<BaseModel> ctx_vec)
	{
		std::string content;
		std::vector<BaseModel>::iterator it;

		for (it = ctx_vec.begin(); it < ctx_vec.end(); ++it)
		{
			if ((it->type) == BaseModel().TYPE_STMT)
			{
				content.append(spacing).append(it->content).append("\n");
			}else if ((it->type) == BaseModel().TYPE_MACRO)
			{
				if (it->content=="#include \"iostream\"")
				{
					content.append(it->content).append("\n");
				}
			}
			else if((it->type) == BaseModel().TYPE_BLOCK)
			{
				content.append(spacing).append(it->content);
				if(it->content!="")
					content.append("{\n");
				spacing.append("\t");
				std::string inner_content = straemlize(it->ctx_vec);
				spacing.replace(0,1,"");
				content.append(inner_content).append(spacing);
				if(it->content!="")
					content.append("}\n");
				
			}
		}
		
		return content;
	}
};