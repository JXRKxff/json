Can't call this a library, this is simple header that contains a class to "easily" work with .json files, sharing some "fstream" vibes.
-

I tried to implement map-storage and operator[], but I'm not experienced right now, maybe later
The header is pretty self-explained, so... good luck to use/expand/break it! :)

Examples (it looks terrifying):
-

![image](https://github.com/JXRKxff/json/assets/150625469/9afdf9f5-23f7-48ac-8c70-d9889f4a1bfb)


![image](https://github.com/JXRKxff/json/assets/150625469/602559ef-7393-425b-8345-8a9550c16a6b)


Methods:
-

- void open(const string& path, const std::ios::openmode& flag)

        method to open file (same to fstream)

        common flags that I was using: std::ios::in, std::ios::out

- void close()

        calls JSON file to close()

- void find(const string& key, T& var)

        simple method that changes the "var" (of reference), if key was found in file

- void find_next(const string& key, T& var)
  
        continues search from last stream position and tries to find()

- T get<T>(const string& key)

        tries to return copy of T-type value, if it was found in file by key

- T get_next<T>(const string& key)

        same to get() but continues search from last stream position

- void write(const string& key, const T& var)

        writes line into json like this -> "key": "some_variable"

- void section_open()
  
        writes "{" to file with some rules (opens the section, wow!)

- void section_close()

        writes "}" to file with some rules (closes the seciton, wow!)

- string json_type(const T& object)
  
        converts the object to string that will be written to file
        for example, bool will be written: true / false; string will be written: "string"; int will be written: 10
