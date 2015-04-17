###Simple C++ Pre Compiler
A lab belonging to the OOP course. Don't ever think of using it for complex preprocessor directives.

#PART 1. Preprocessor Directives
###MACROS - USAGE - SCENCRIO
 **#INCLUDE**	Tells the preprocessor to treat the contents of a specified file as if they appear in the source program at the point where the directive appears.	

     #include   "path-spec" 
     #include   < path-spec >

 **#DEFINE**	The #define creates a macro, which is the association of an identifier or parameterized identifier with a token string. After the macro is defined, the compiler can substitute the token string for each occurrence of the identifier in the source file.	

     #define identifier token-stringopt

 
 **#UNDEF**	Removes (undefines) a name previously created with #define.	

     #undef identifier

 **#IFDEF** **#IFNDEF	**	 The #ifdef and #ifndef directives perform the same task as the #if directive when it is used with defined( identifier ).

     #ifdef identifier
     #ifndef identifier

 **#IF** **#ELSE**	**#ENDIF** **#ELIF** The #if directive, with the #elif, #else, and #endif directives, controls compilation of portions of a source file. If the expression you write (after the #if) has a nonzero value, the line group immediately following the #if directive is retained in the translation unit.	

    #if defined(CREDIT)
        credit();
    #elif defined(DEBIT)
        debit();
    #else
        printerror();
    #endif
		

#PART 2. Implementation
###My project is a Visual Studio solution.
 
1. The PreCompiler (PreCompiler.cpp) first takes in a streamed code file, preprocessed by Serializer (serializer.h) into a structurized model. 
 
 ![enter image description here](https://lh3.googleusercontent.com/-AviWVaa9a6Q/VTEByQzShbI/AAAAAAAABsA/_vPd88WU9iU/s0/2.png "2.png")
 
2. Code fragments are abstracted into three types – **MACRO**, **STATEMENT** and **BLOCK**. They are all inherited from BASEMODEL (model.h). 

	>	**STMT** Statements ended with “;”.

	>	**MACRO** Preprocessor directives starting with “#”.

	>	**BLOCK** The file can be viewed as a BLOCK. if-else, functions, classes are also interpreted into a BLOCK. A BLOCK has two fields – content (optional, if-else conditions, function params) and context vector (STMTs, MACROs, BLOCKs embedded in the block).


3. The serialized code is then processed by a Processor (stmtp.h) one after another. There is a def_trans_map in macrop.h, which records macro definitions already met.  macrop.add_macro takes in mcro string and converts it into structured key-value pair. macrop.process process each statement and replace embedded macro identifiers. Other complex directives are handled by stmtp.process.

4. After the code cleaned up, a Streamlizer (streamlizer.h) turns the structured document back to a streamed file with a nice format. And the PreCompiler writes it back into the disk. 

#PART 3. Examples
The given demo.cpp and outputted out.cpp.
  ![enter image description here](https://lh3.googleusercontent.com/-8nCTiONmE2Q/VTEB8VLnw6I/AAAAAAAABsM/_8tfIKbDS-Q/s0/1.png "1.png")
