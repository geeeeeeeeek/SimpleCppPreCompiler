#include <iostream>
#include <fstream>
#include <string>
#include "model.h"

#include "streamlizer.h"
#include "serializer.h"
#include "stmtp.h"
using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        cout << "WTF";
        return -1;
    }

    ifstream is(argv[1]);
    
	string file;

    if (is.is_open()) {
		string line;
	    while (getline(is,line))
		    file.append(line).append("\n");
    }
    else{
	    cout<<"WTF";
		return -1;
    }
	is.close();
	
	vector<BaseModel> serialized = serializer().serialize(file);
	string stream= streamlizer().straemlize(stmtp().process(serialized));
	
    ofstream os(argv[2]);
	os.write(&stream[0u],stream.length());
	return 0;
}