//#include "model.h"
#include "macrop.h"
#include <iostream>
#include <fstream>
//#include "serializer.h"

class stmtp
{
public:
	std::vector<BaseModel> process(std::vector<BaseModel> ctx_vec)
	{

		std::vector<BaseModel>::iterator it;

		for (it = ctx_vec.begin(); it < ctx_vec.end(); ++it)
		{
			if ((it->type) == BaseModel().TYPE_MACRO)
			{
				std::string macro =it->content;
				if (macro=="#if TRUE")
				{
					int a =1;
				}
				if (macro.find("#include")==0)
				{
					//get head name
					int beg = macro.find("\"");
					int end = macro.find("\"",beg+1);

					std::string path = macro.substr(beg+1,end-beg-1);

					//explictly ignore ios
					if (path=="iostream")
						continue;

					std::ifstream is(path);
					std::string linked_file;

					if (is.is_open()) {
						std::string line;
						while (getline(is,line))
							linked_file.append(line).append("\n");
					}
					else
						std::cout<<"WTF";
					is.close();

					//add linked file into a block
					Block linked_block("");
					linked_block.ctx_vec=serializer().serialize(linked_file);
					*it=linked_block;

					it->content = macrop().process(it->content);
					it->ctx_vec=stmtp().process(it->ctx_vec);
					
				}
				else if (macro.find("#define")==0)
				{
					//one param
					int key_pos = macro.find(" ");
					int value_pos = macro.find(" ",key_pos+1);
					int end_pos = macro.length();

					std::string key,value;
					if (value_pos==-1)
					{
						key=macro.substr(key_pos+1,end_pos-key_pos-1);
						value="";
					}
					else
					{
						key=macro.substr(key_pos+1,value_pos-key_pos-1);
						value=macro.substr(value_pos+1,end_pos-key_pos-1);
					}
					

					//if has param
					int left = key.find("(");
					int right = key.find(")");
					if (left!=-1 && right!=-1)
					{
						
						std::string arg=key.substr(left+1,right-left-1);
						key = key.substr(0,left);

						left = value.find("(");
						right = value.find(")");
						if (left!=-1 && right!=-1){
							value=value.substr(left+1,right-left-1);
						}

						int sharp  =value.find("#");
						if (sharp!=-1)
						{
							value=value.replace(sharp,1,"\"").append("\"");
						}
						value.replace(value.find(arg),arg.length(),"arg");
					}
					
					macrop().add_macro(key,value);
				}
				else if (macro.find("#ifdef")==0)
				{
					int key_pos = macro.find(" ");
					int end_pos = macro.length();

					std::string key=macro.substr(key_pos+1,end_pos-key_pos-1);

					std::vector<BaseModel>::iterator itt,itelse;
					bool has_else=false;
					for (itt = it+1; itt < ctx_vec.end(); ++itt)
					{
						if ((itt->type) == BaseModel().TYPE_MACRO)
						{
							if (itt->content.find("#endif")==0)
							{
								break;
							}
							if (itt->content.find("#else")==0)
							{
								has_else=true;
								itelse=itt;
							}
						}
					}
					if (def_trans_map.find(key)==def_trans_map.end())
					{
						if (has_else)
						{
							ctx_vec.erase(itt);
							it=ctx_vec.erase(it,itelse);
						}
						else
						{
							it=ctx_vec.erase(it,++itt);
						}
						
					}
					else
					{
						if (has_else)
						{
							ctx_vec.erase(itelse,++itt);
						}
						
					}

				}
				else if (macro.find("#ifndef")==0)
				{
					int key_pos = macro.find(" ");
					int end_pos = macro.length();

					std::string key=macro.substr(key_pos+1,end_pos-key_pos-1);

					std::vector<BaseModel>::iterator itt,itelse;
					bool has_else=false;
					for (itt = it+1; itt < ctx_vec.end(); ++itt)
					{
						if ((itt->type) == BaseModel().TYPE_MACRO)
						{
							if (itt->content.find("#endif")==0)
							{
								break;
							}
							if (itt->content.find("#else")==0)
							{
								has_else=true;
								itelse=itt;
							}
						}
					}
					if (def_trans_map.find(key)!=def_trans_map.end())
					{
						if (has_else)
						{
							ctx_vec.erase(itt);
							it=ctx_vec.erase(it,++itelse);
						}
						else
						{
							it=ctx_vec.erase(it,++itt);
						}
						
					}
					else
					{
						if (has_else)
						{
							ctx_vec.erase(itelse,++itt);
						}
						
					}
				}
				else if (macro.find("#undef")==0)
				{
					int key_pos = macro.find(" ");
					int end_pos = macro.length();

					std::string key=macro.substr(key_pos+1,end_pos-key_pos-1);
					if (def_trans_map.find(key)!=def_trans_map.end())
					{
						def_trans_map.erase(def_trans_map.find(key));
					}
//					it=ctx_vec.erase(it);

				}
				else if (macro.find("#if")==0)
				{
					int key_pos = macro.find(" ");
					int end_pos = macro.length();

					std::string key=macro.substr(key_pos+1,end_pos-key_pos-1);

					std::vector<BaseModel>::iterator itt,itelse,ittt;
					int has_else=0,has_if=1,has_end=0,elsed=0;
					for (itt = it+1; itt < ctx_vec.end(); ++itt)
					{
						if ((itt->type) == BaseModel().TYPE_MACRO)
						{
							if (itt->content.find("#endif")==0)
							{
								has_end+=1;
								if (has_if==has_end)
								{
									break;
								}
							}
							if (itt->content.find("#else")==0)
							{
								has_else+=1;
								if (has_if==has_else && !elsed){
									itelse=itt;
									elsed=1;
								}
							}
							if (itt->content.find("#if")==0)
							{
								has_if+=1;
								
							}
						}
					}

					if (key=="1" || (def_trans_map.find(key)!=def_trans_map.end() && def_trans_map.find(key)->second =="1"))
					{
						
						if (has_else)
						{
							ctx_vec.erase(itelse,++itt);
						}
					}
					else
					{
						
						if (has_else)
						{
							ctx_vec.erase(itt);
							it=ctx_vec.erase(it,++itelse)-2;
						}
						else
						{
							it=ctx_vec.erase(it,++itt) ;
						}
					}
				}
				
			}
			else if ((it->type) == BaseModel().TYPE_STMT)
			{
				it->content = macrop().process(it->content);
				//process
			}
			else if((it->type) == BaseModel().TYPE_BLOCK)
			{
				//process
				it->content = macrop().process(it->content);
				it->ctx_vec=stmtp().process(it->ctx_vec);
			}

		}

		return ctx_vec;
	}

};