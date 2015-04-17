#include <string>
#include <vector>
//#include "model.h"
class serializer
{
public:
	std::vector<BaseModel> serialize(std::string context)
	{
		std::vector<BaseModel> ctx_vec;

		while (context.find_first_not_of(" \n\t")!=-1)
		{
			int macro_beg = context.find("#");
			int macro_end = context.find("\n",macro_beg);

			int stmt_beg=context.find_first_not_of(" \n\t");
			int stmt_end=context.find(";",stmt_beg);
			
			int block_beg=context.find_first_not_of(" \n\t");
			int block_end=context.find("{",block_beg);

			/*determine model type*/
			if (macro_beg<=stmt_beg && macro_beg!=-1)
			{
				//typeof macro
				Macro model(context.substr(macro_beg,macro_end-macro_beg));

				context.erase(0,macro_end + 1);
				ctx_vec.push_back(model);
			}
			else if(stmt_end<block_end || block_end==-1)
			{
				//typeof stmt
				Stmt model(context.substr(stmt_beg,stmt_end-stmt_beg+1));
				context.erase(0,stmt_end + 1);
				ctx_vec.push_back(model);
			}else
			{
				int left_brace = block_end+1,right_brace=block_end+1;
				while (left_brace<=right_brace)
				{
					left_brace = context.find("{",left_brace+1);
					right_brace = context.find("}",right_brace+1);
					
					if (left_brace==-1)
						break;
				}


				//typeof block
				Block model(context.substr(stmt_beg,block_end-stmt_beg));
				std::vector<BaseModel> vex_model = serialize(context.substr(block_end+1,right_brace-block_end-1));
				model.ctx_vec=vex_model;

				context.erase(0,right_brace + 1);
				ctx_vec.push_back(model);
			}
			
		}
		return ctx_vec;
	}
};