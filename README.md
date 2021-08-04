### Fork info
This is a heavily modified, stripped down copy for use with Loton, here: https://github.com/loganmcbroom/Loton

### Build
Have Qt installed.
```
git clone https://github.com/loganmcbroom/nodeeditor
cd nodeeditor
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target install --config Release 
```
The "-DCMAKE_BUILD_TYPE=Release" is for single-config generators, while "--config Release" is for multi-config generators.
NodeEditor also exports the build tree, so "--target install" isn't needed if the build will remain where it was built.

### Credit
Dmitry Pinaev et al, Qt5 Node Editor, (2017), GitHub repository, https://github.com/paceholder/nodeeditor

