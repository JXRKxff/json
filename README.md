Can't call this a library, this is simple header that contains a class to "easily" work with .json files, sharing some "fstream" vibes.

I tried to implement map-storage and operator[], but I'm not experienced right now, maybe later
The header is pretty self-explained, so... good luck to use/expand/break it! :)

Methods:

void open(const string& path, const std::ios::openmode& flag)
.- method to open file (same to fstream)
.- common flags that I was using: std::ios::in, std::ios::out

void close()
.- calls JSON file to close()

void find(const string& key, T& var) 
.- simple method that changes the "var" (because of reference), if key was found in file

void find_next(const string& key, T& var) 
.- doesn't reset the stream pos (continues from last stream position) and tries to find() (like in previous method)

T get<T>(const string& key) 
.- tries to return copy of T-type value, if it was found in file by key

T get_next<T>(const string& key) 
.- same to get() but doesn't reset the stream pos before searching (continues from last stream position)

void write(const string& key, const T& var) 
.- writes line into json like this -> "key": "some_variable"

void section_open()
.- writes "{" to file with some rules (opens the section, wow!)

void section_close()
.- writes "}" to file with some rules (closes the seciton, wow!)

string json_type(const T& object)
.- converts the object to string that will be written to file
.- for example, bool will be written: true / false; string will be written: "string"; int will be written: 10
