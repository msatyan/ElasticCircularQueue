
## Elastic Circular Queue
This is an implementation of **Elastic Circular Queue** data structure where it provides facility to **Read** or **Writer** element to the queue. A typical Circular Queue may have fixed capacity, where as the Elastic Circular Queue has an automatic queue expansion facility, so application can keep add or remove elements to the queue, until the system resources run out. FYI: the current implementation has no queue shrinking or thread safety consideration. The lock/unlock can be adeed without much effort to make it thread safe.


### Build
It can be build by using one of the following options.
- CMake build
- Visual Studio IDE 2019


### CMake Build
```bash
# cd to the <project root dir> first
# CMake options
cmake -S<sourcedir> -B<builddir> ....<all tother options>

# eg:
cmake -S. -Bbuild  -G "Visual Studio 16 2019" -A x64

# Then
cmake --build build --config Release
cmake --build build --config Debug

```

### Alternatively
```bash
# cd to the <project root dir> first
rm -rf build
mkdir build

cd build
cmake ..  -G "Visual Studio 16 2019" -A x64
cmake --build ./
```


### Sample usage
```C++
int InitialQueueSize = 256;
int qExpansionUnits = 32;
ElasticCircularQ ecq(InitialQueueSize, qExpansionUnits);

const char *msg = "Hello World";
ecq.Write(msg);
-- -- -- -- --
-- -- -- -- --
msg = ecq.Read();
-- -- -- -- --
-- -- -- -- --
// Optional: Explicitly tell the Q that you are don, then it may free the
// Q resource instead of waiting for C++ class object destructor to do the job.
ecq.Release();
```
