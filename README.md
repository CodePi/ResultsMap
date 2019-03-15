# ResultsMap

Serializable hierarchical dynamic data structure.  

Compiles with C++11 compatible compilers. Tested with gcc 4.7-9.0 and Visual Studio 2012.

#### Example usage

ResultsMap is a dynamically buildable hierarchical map with string keys and a value (of any streamable type).

``` cpp
ResultsMap rMap;
rMap["teststring"] = "this is a string";
rMap["int value"] = 1
rMap["value"] = 1.3;
rMap("results")("left")["message"] = "hello";
rMap("results")("right")["message"] = "goodbye";

vector <int> v = {1,2,3,4,5};
rMap("results")("center")["vector results"] = v;

int& i =   rMap["int value"].getRef<int>();
double d = rMap["value"].to_f();
string s = rMap["value"].to_s();

cout << rMap << endl;
```

Use operator[string] for leaf nodes and operator(string) for non-leaves.

See [test/testResultsMap.cpp](test/testResultsMap.cpp) for more example usage.

#### To use in new project, just:
* Copy the 3 source files from [base directory](https://github.com/CodePi/ResultsMap)
* #include "[ResultsMap.h](ResultsMap.h)"
* Compile and link to [ResultsMap.cpp](ResultsMap.cpp).
