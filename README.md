# cocohttp

🚧🛠️

## How to build
This project uses CMake and vcpkg for a reasonable build with reasonable dependency management:
1. `CMakeLists.txt` contains a project definition and `vcpkg` integration bits.
2. `vcpkg.json` is a manifest file that defines a list of project dependencies.
3. `vcpkg` itself is checked-out as a submodule, so don't forget to run:
   1. `git submodule update --init`.
   2. `vcpkg/bootstrap-vcpkg.sh`.

* How to set up the build: `cmake -S . -B <build_dir> -DCMAKE_BUILD_TYPE=<Debug|Release> [-G Ninja]`
* How to build the binary: `cmake --build <build_dir>`
* How to run the built binary: run `<build_dir>/<binary_path>`

The top-level `Makefile` defines a number of phony targets that act as shortcuts for specific cmake invocations:
* `bootstrap` sets up `vcpkg`
* `configure/reconfigure` prepare cmake build
* `build` to compile the code
* `run*` to run various executables
* `clean`